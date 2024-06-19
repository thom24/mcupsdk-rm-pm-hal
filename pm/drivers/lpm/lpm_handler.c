/*
 * Device Manager - LPM interface
 *
 * Handlers for Low Power Mode implementation
 *
 * Copyright (C) 2021-2024, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <lib/ioremap.h>
#include <types/errno.h>
#include <string.h>
#include <tisci/lpm/tisci_lpm.h>
#include <osal/osal_clock_user.h>
#include <osal_hwi.h>
#include <osal_dm.h>
#include "gtc.h"
#include "lpm_handler.h"
#include "padcfg.h"
#include "device.h"
#include "device_pm.h"
#include "devices.h"
#include "sec_proxy.h"
#include "clk.h"
#include "soc_ctrl_mmr.h"
#include "ctrlmmr_raw.h"
#include "ctrl_mmr.h"
#include "rm_lpm.h"
#include "device_prepare.h"
#include <soc/host_idx_mapping.h>
#include <lib/trace.h>

/* Count of 1us delay for 10ms */
#define TIMEOUT_10MS                    10000U

/* Number of bits required to perform one word shift */
#define WORD_SHIFT                      32U

#define LPM_SUSPEND_POWERMASTER                 BIT(0)
#define LPM_DEVICE_DEINIT                       BIT(1)
#define LPM_DISABLE_LPSC                        BIT(2)
#define LPM_SAVE_MAIN_PADCONFIG                 BIT(3)
#define LPM_SUSPEND_GTC                         BIT(4)
#define LPM_CLOCK_SUSPEND                       BIT(5)
#define LPM_SUSPEND_DM                          BIT(6)
#define LPM_SAVE_MMR_LOCK                       BIT(7)
#define LPM_SAVE_MCU_PADCONFIG                  BIT(8)

#define LPM_WKUP_LATENCY_VALID_FLAG             BIT(16)

/* Deep sleep and MCU Only latency values */
#define LPM_DEEP_SLEEP_WKUP_LAT_MIN             101U
#define LPM_DEEP_SLEEP_WKUP_LAT_MAX             200U
#define LPM_MCU_ONLY_WKUP_LAT_MIN               10U
#define LPM_MCU_ONLY_WKUP_LAT_MAX               100U

extern s32 _stub_start(void);
extern u32 lpm_get_wake_up_source(void);
extern void lpm_populate_prepare_sleep_data(struct tisci_msg_prepare_sleep_req *p);
extern void lpm_clear_all_wakeup_interrupt(void);
extern u8 lpm_get_selected_sleep_mode(void);

u32 key;
volatile u32 enter_sleep_status = 0;

/* Each bit represents whether that host has set constraints or not */
#if HOST_ID_CNT <= 16U
static u16 dev_cons[SOC_DEVICES_RANGE_ID_MAX] = { 0U };
#elif HOST_ID_CNT <= 32U
static u32 dev_cons[SOC_DEVICES_RANGE_ID_MAX] = { 0U };
#else
static u64 dev_cons[SOC_DEVICES_RANGE_ID_MAX] = { 0U };
#endif

static u32 latency[HOST_ID_CNT] = { 0U };
static sbool lpm_locked = SFALSE;
extern u64 __FS_CTXT_START;

static u8 lpm_select_shallowest_mode(u8 req_mode, u8 curr_mode)
{
	u8 mode;

	if ((curr_mode == TISCI_MSG_VALUE_SLEEP_MODE_MCU_ONLY) || (req_mode == TISCI_MSG_VALUE_SLEEP_MODE_MCU_ONLY)) {
		mode = TISCI_MSG_VALUE_SLEEP_MODE_MCU_ONLY;
	} else if ((curr_mode == TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP) || (req_mode == TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP)) {
		mode = TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP;
	} else {
		mode = DEEPEST_LOW_POWER_MODE;
	}

	return mode;
}

static void lpm_hang_abort(void)
{
	volatile u32 a = 0x12341234;

	while (a != 0U) {
	}
}

static s32 lpm_sleep_wait_for_tifs_wfi(void)
{
	u32 reg;
	u32 i = 0;
	s32 ret = -ETIMEDOUT;

	do {
		reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_WFI_STATUS);
		if ((reg & SMS_CPU0_WFI_MASK) == SMS_CPU0_WFI_MASK) {
			ret = SUCCESS;
			break;
		}
		osal_delay(1);
	} while (i++ < TIMEOUT_10MS);

	return ret;
}

static s32 lpm_sleep_disable_sec_lpsc(void)
{
	/* Disable security LPSCs */
	return SUCCESS;
}

static s32 lpm_sleep_disable_misc_lpsc(void)
{
	/* Disable non-critical LPSCs */
	return SUCCESS;
}

static s32 lpm_resume_enable_lpsc(void)
{
	/* enable LPSCs as needed for cores to resume */
	return SUCCESS;
}

static s32 lpm_resume_disable_DM_reset_isolation(void)
{
	/* Clear WKUP_CTRL_DS_DM_RESET.mask to stop
	* isolation of DM from MAIN domain
	*/
	writel(DS_DM_RESET_UNMASK, WKUP_CTRL_BASE + WKUP_CTRL_DS_DM_RESET);
	return SUCCESS;
}

static s32 lpm_resume_restore_RM_context(void)
{
	/* Restore IR configurations */
	s32 ret = -EFAIL;

	ret = lpm_resume_restore_ir_config();

	return ret;
}

static s32 lpm_resume_send_core_resume_message(void)
{
	/* Send core resume message */
	s32 ret = 0;

	struct tisci_msg_core_resume_req req = {
		.hdr		= {
			.type	= TISCI_MSG_CORE_RESUME,
			.flags	= TISCI_MSG_FLAG_AOP,
			.host	= HOST_ID_DM2TIFS
		}
	};

	ret = sproxy_send_msg_dm2dmsc_fw(&req, sizeof(req));

	if (ret == 0) {
		struct tisci_msg_core_resume_resp resp;
		memset(&resp, 0, sizeof(resp));

		ret = sproxy_receive_msg_dm2dmsc_fw(&resp, sizeof(resp));
		if (ret == 0) {
			if ((resp.hdr.type != TISCI_MSG_CORE_RESUME) || ((resp.hdr.flags & TISCI_MSG_FLAG_ACK) != TISCI_MSG_FLAG_ACK)) {
				ret = -EINVAL;
			}
		}
	}

	return ret;
}

static s32 lpm_resume_send_enter_sleep_abort_message(void)
{
	/* Send abort enter sleep message */
	s32 ret = 0;

	struct tisci_msg_abort_enter_sleep_req req = {
		.hdr		= {
			.type	= TISCI_MSG_ABORT_ENTER_SLEEP,
			.flags	= 0,
			.host	= HOST_ID_DM2TIFS
		}
	};

	ret = sproxy_send_msg_dm2dmsc_fw(&req, sizeof(req));

	return ret;
}

static s32 lpm_suspend_power_master(void)
{
	/* Release reset of power master */
	struct device *dev;

	dev = device_lookup(DEV_GTC);
	soc_device_ret_disable(dev);
	soc_device_disable(dev, SFALSE);

	dev = device_lookup(POWER_MASTER);
	soc_device_ret_disable(dev);
	soc_device_disable(dev, SFALSE);

	dev = device_lookup(POWER_MASTER_CLUSTER);
	soc_device_ret_disable(dev);
	soc_device_disable(dev, SFALSE);

	return SUCCESS;
}

static s32 lpm_resume_release_reset_of_power_master(void)
{
	/* Release reset of power master */
	struct device *dev;

	dev = device_lookup(POWER_MASTER_CLUSTER);
	soc_device_enable(dev);

	dev = device_lookup(POWER_MASTER);
	soc_device_enable(dev);

	dev = device_lookup(DEV_GTC);
	soc_device_enable(dev);

	return SUCCESS;
}

static s32 lpm_sleep_suspend_dm(void)
{
	/* Suspend DM OS */
	osal_dm_disable_interrupt();    /* Disable sciserver interrupt */
	osal_suspend_dm();              /* Suspend DM task scheduler */
	key = osal_hwip_disable();      /* Disable Global interrupt */
	return SUCCESS;
}

static s32 lpm_resume_dm(void)
{
	/* Resume DM OS */
	osal_dm_enable_interrupt();     /* Enable sciserver interrupts */
	osal_resume_dm();               /* Resume DM task scheduler */
	osal_hwip_restore(key);         /* Enable Global interrupts */
	return SUCCESS;
}

static s32 lpm_sleep_jump_to_dm_Stub(void)
{
	/* Jump to DM stub */
	return _stub_start();
}

static s32 lpm_select_sleep_mode(u8 *mode)
{
	u8 lpsc;
	u16 devgrp;
	u8 i = 0U;
	s32 ret = SUCCESS;
	sbool mode_selected = SFALSE;
	sbool main_padcfg_wkup_en = SFALSE;
	sbool mcu_padcfg_wkup_en = SFALSE;

	*mode = DEEPEST_LOW_POWER_MODE;

	/* Device constraint based selection */
	for (i = 0; i < soc_device_count; i++) {
		if (dev_cons[i] != 0U) {
			/* Get devgrp and LPSC info from device_id */
			ret = device_id_lookup_devgroup_and_lpsc(i, &devgrp, &lpsc);
			if (ret != SUCCESS) {
				ret = -EFAIL;
				break;
			}

			/**
			 * If device having constraints belongs to MAIN DEVGRP, then no lpm is possible
			 * Exceptions: USB0 and USB1
			 */
			if (devgrp == MAIN_DEVGRP) {
				if ((i == USB0_DEV_ID) || (i == USB1_DEV_ID)) {
					*mode = lpm_select_shallowest_mode(TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP, *mode);
				} else {
					ret = -EFAIL;
					break;
				}
			} else {
				/* If device is in ALWAYS ON domain in MCU_WAKEUP devgrp, then select Deep sleep */
				if (lpsc == ALWAYS_ON_LPSC_ID) {
					*mode = lpm_select_shallowest_mode(TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP, *mode);
					/* Otherwise, the device belongs to MCU Domain, select MCU only mode */
				} else {
					*mode = TISCI_MSG_VALUE_SLEEP_MODE_MCU_ONLY;
					mode_selected = STRUE;
					/* Return as this mode is shallowest of all */
					break;
				}
			}
		}
	}

	/* Latency based selection */
	if (ret == SUCCESS) {
		for (i = 0; i < HOST_ID_CNT; i++) {
			if ((latency[i] & LPM_WKUP_LATENCY_VALID_FLAG) != 0U) {
				/* If the latency value lie in deep sleep mode wakeup latency range, select deep sleep */
				if (((u16) latency[i] >= LPM_DEEP_SLEEP_WKUP_LAT_MIN) & ((u16) latency[i] <= LPM_DEEP_SLEEP_WKUP_LAT_MAX)) {
					*mode = lpm_select_shallowest_mode(TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP, *mode);
					/* If the latency value lie in mcu only mode wakeup latency range, select mcu only */
				} else if (((u16) latency[i] >= LPM_MCU_ONLY_WKUP_LAT_MIN) & ((u16) latency[i] <= LPM_MCU_ONLY_WKUP_LAT_MAX)) {
					*mode = TISCI_MSG_VALUE_SLEEP_MODE_MCU_ONLY;
					mode_selected = STRUE;
					break;
					/* If the latency value is out of wakeup latency range values, no lpm is possible */
				} else {
					ret = -EFAIL;
					break;
				}
			}
		}
	}

	/* Scan and save the padconfig values */
	if (ret == SUCCESS) {
		ret = lpm_sleep_save_main_padconf(&main_padcfg_wkup_en);
	}

	if (ret == SUCCESS) {
		ret = lpm_sleep_save_mcu_padconf(&mcu_padcfg_wkup_en);
	}

	if (ret == SUCCESS) {
		/* Wakeup source based selection (Padconfig) - Skipped if shallowest mode is already selected */
		if (((main_padcfg_wkup_en == STRUE) || (mcu_padcfg_wkup_en == STRUE)) && (mode_selected == SFALSE)) {
			/* Deepest mode is selected unless explicit constraint is there */
			*mode = lpm_select_shallowest_mode(TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP, *mode);
		}
	} else {
		/* Update the selected mode to invalid in response */
		*mode = TISCI_MSG_VALUE_SLEEP_MODE_INVALID;
	}

	return ret;
}

static void lpm_enter_partial_io_mode(void)
{
	u32 reg = 0;
	u32 timeout = TIMEOUT_10MS;

	/* Unlock wkup_ctrl_mmr region 6 */
	ctrlmmr_unlock(WKUP_CTRL_BASE, 6);

	/* Set global wuen for WKUP IOs */
	reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0);
	reg = reg & WKUP_CTRL_PMCTRL_IO_0_WRITE_MASK;
	reg = reg | WKUP_CTRL_PMCTRL_IO_0_GLOBAL_WUEN;
	writel(reg, (WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0));

	/* Set global isoin for wakeup IOs */
	reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0);
	reg = reg & WKUP_CTRL_PMCTRL_IO_0_WRITE_MASK;
	reg = reg | WKUP_CTRL_PMCTRL_IO_0_IO_ISO_CTRL;
	writel(reg, (WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0));

	/* Wait for wu clock state to be 1 */
	while ((timeout > 0U) && (((readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0)) & WKUP_CTRL_PMCTRL_IO_0_IO_ISO_STATUS) != WKUP_CTRL_PMCTRL_IO_0_IO_ISO_STATUS)) {
		--timeout;
	}
	if (timeout == 0U) {
		lpm_hang_abort();
	}

	/* Enable wakeup from CAN IO */
	writel(WKUP0_EN_CANUART_IO_DAISY_CHAIN, (WKUP_CTRL_BASE + WKUP0_EN));

	/* Ensure that PMIC EN control from SOC is selected */
	writel((WKUP0_PMCTRL_SYS_LPM_EN_PMIC | WKUP0_LPM_PMIC_OUT_EN), (WKUP_CTRL_BASE + WKUP0_PMCTRL_SYS));

	/* Program magic word */
	reg = WKUP_CANUART_MAGIC_WRD;
	writel(reg, WKUP_CTRL_BASE + WKUP_CANUART_CTRL);

	/* Set enable bit */
	reg |= WKUP_CANUART_MAGIC_WRD_LD_EN;
	writel(reg, WKUP_CTRL_BASE + WKUP_CANUART_CTRL);

	/* Wait for CAN_ONLY_IO signal to be 1 */
	while ((timeout > 0U) && ((readl(WKUP_CTRL_BASE + WKUP_CANUART_WAKE_STAT1)) != WKUP_CANUART_IO_MODE_ACTIVE)) {
		--timeout;
	}
	if (timeout == 0U) {
		lpm_hang_abort();
	}

	/* Enter Partial IO mode */
	writel((WKUP0_PMCTRL_SYS_LPM_EN_PMIC | WKUP0_LPM_PMIC_OUT_DIS), WKUP_CTRL_BASE + WKUP0_PMCTRL_SYS);

	/* If PMIC fails to suspend the system, hang abort */
	lpm_hang_abort();
}

s32 dm_prepare_sleep_handler(u32 *msg_recv)
{
	struct tisci_msg_prepare_sleep_req *req =
		(struct tisci_msg_prepare_sleep_req *) msg_recv;

	s32 ret = SUCCESS;
	u8 mode;

	/* Skip mode selection if mode is partial IO or context address value is valid (indicating old kernel) */
	if ((req->mode == TISCI_MSG_VALUE_SLEEP_MODE_PARTIAL_IO) || ((req->ctx_lo != 0U) || (req->ctx_hi != 0U))) {
		mode = req->mode;

		/* Scan and save the padconfig values */
		if (ret == SUCCESS) {
			ret = lpm_sleep_save_main_padconf(NULL);
		}

		if ((mode == TISCI_MSG_VALUE_SLEEP_MODE_IO_ONLY_PLUS_DDR) && (ret == SUCCESS)) {
			ret = lpm_sleep_save_mcu_padconf(NULL);
		}
		/* Select low power mode only if mode is not locked yet */
	} else if (lpm_locked == SFALSE) {
		if (lpm_select_sleep_mode(&mode) == SUCCESS) {
			lpm_locked = STRUE;
			req->mode = mode;

			/* Update the context address */
			req->ctx_lo = (u32) &__FS_CTXT_START;
			req->ctx_hi = (u32) (((u64) (&__FS_CTXT_START)) >> WORD_SHIFT);
		}
	} else {
		ret = -EFAIL;
	}

	if (ret == SUCCESS) {
		switch (mode) {
		case TISCI_MSG_VALUE_SLEEP_MODE_IO_ONLY_PLUS_DDR:
			/* Return failure if the device does not support IO only plus DDR mode */
			if (mode != DEEPEST_LOW_POWER_MODE) {
				ret = -EFAIL;
				break;
			}
		case TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP:
		case TISCI_MSG_VALUE_SLEEP_MODE_MCU_ONLY:
			/* Parse and store the mode info and ctx address in the prepare sleep message */
			lpm_populate_prepare_sleep_data(req);

			/*
			 * Clearing all wakeup interrupts from VIM. Even if we are cleaning interrupts
			 * from VIM, if the wakeup interrupt is still active it will be able to wake
			 * the soc from LPM. This will only clear any unwanted pending wakeup interrupts
			 */
			lpm_clear_all_wakeup_interrupt();
			break;
		case TISCI_MSG_VALUE_SLEEP_MODE_PARTIAL_IO:
			/* Suspend DM so that in case of failure, idle hook is not executed */
			ret = lpm_sleep_suspend_dm();

			if (ret == SUCCESS) {
				/*
				 * Wait for tifs to reach WFI in both the failed and successful case.
				 * but update the ret value only if it was SUCCESS previously
				 */
				ret = lpm_sleep_wait_for_tifs_wfi();
			}

			if (ret == SUCCESS) {
				/* Enable CANUART IO daisy chain and enter partial io mode */
				lpm_enter_partial_io_mode();
			} else {
				lpm_hang_abort();
			}
			break;
		default: ret = -EFAIL;
			break;
		}
	}

	return ret;
}

s32 dm_enter_sleep_handler(u32 *msg_recv)
{
	struct tisci_msg_enter_sleep_req *req =
		(struct tisci_msg_enter_sleep_req *) msg_recv;

	s32 ret = SUCCESS;
	u8 mode = req->mode;
	u32 i;
	u32 temp_sleep_status = 0;

	enter_sleep_status = 0;

	/* Check if this req mode matches with DM selected mode */
	if (lpm_get_selected_sleep_mode() != mode) {
		ret = -EINVAL;
	}

	/*
	 * Wait for tifs to reach WFI in both the failed and successful case.
	 * but update the ret value only if it was SUCCESS previously
	 */
	if (ret == SUCCESS) {
		ret = lpm_sleep_wait_for_tifs_wfi();
	} else {
		lpm_sleep_wait_for_tifs_wfi();
	}

	/*
	 * Since, once power master reaches WFI, power master is only recoverable
	 * by reseting the  power master. Only update the ret value only if it was
	 * SUCCESS previously
	 */
	if (ret == SUCCESS) {
		ret = lpm_suspend_power_master();
		enter_sleep_status |= LPM_SUSPEND_POWERMASTER;
	} else {
		lpm_suspend_power_master();
		enter_sleep_status |= LPM_SUSPEND_POWERMASTER;
	}

	if (ret == SUCCESS) {
		ret = devices_deinit_flags();
		enter_sleep_status |= LPM_DEVICE_DEINIT;
	} else {
		devices_deinit_flags();
		enter_sleep_status |= LPM_DEVICE_DEINIT;
	}

	if (ret == SUCCESS) {
		ret = lpm_sleep_disable_sec_lpsc();
		enter_sleep_status |= LPM_DISABLE_LPSC;
	}

	if (ret == SUCCESS) {
		ret = lpm_sleep_disable_misc_lpsc();
		enter_sleep_status |= LPM_DISABLE_LPSC;
	}

	if (ret == SUCCESS) {
		/* As PADCFGs have already been saved, set the flag */
		enter_sleep_status |= LPM_SAVE_MAIN_PADCONFIG;

		/* MCU PADCFGs values is lost only during IO DDR mode */
		if (mode == TISCI_MSG_VALUE_SLEEP_MODE_IO_ONLY_PLUS_DDR) {
			enter_sleep_status |= LPM_SAVE_MCU_PADCONFIG;
		}
	}

	if (ret == SUCCESS) {
		ret = lpm_save_mmr_lock();
		enter_sleep_status |= LPM_SAVE_MMR_LOCK;
	}

	if (ret == SUCCESS) {
		ret = lpm_sleep_suspend_gtc();
		enter_sleep_status |= LPM_SUSPEND_GTC;
	}

	if (ret == SUCCESS) {
		ret = clks_suspend();
		enter_sleep_status |= LPM_CLOCK_SUSPEND;
	}

	if (ret == SUCCESS) {
		ret = lpm_sleep_suspend_dm();
		enter_sleep_status |= LPM_SUSPEND_DM;
	}

	if (ret == SUCCESS) {
		ret = lpm_sleep_jump_to_dm_Stub();
	}

	/* If there is any failure, inform TIFS using abort message */
	if (ret != SUCCESS) {
		if (lpm_resume_send_enter_sleep_abort_message() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	temp_sleep_status = enter_sleep_status;
	if ((ret == SUCCESS) || ((temp_sleep_status & LPM_DISABLE_LPSC) == LPM_DISABLE_LPSC)) {
		if (lpm_resume_enable_lpsc() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	if (ret == SUCCESS) {
		if (lpm_resume_disable_DM_reset_isolation() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	if ((ret == SUCCESS) || ((temp_sleep_status & LPM_SUSPEND_GTC) == LPM_SUSPEND_GTC)) {
		if (lpm_resume_gtc() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	if (((temp_sleep_status & LPM_SAVE_MCU_PADCONFIG) == LPM_SAVE_MCU_PADCONFIG) && (ret == SUCCESS)) {
		if (lpm_resume_restore_mcu_padconf() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	if ((ret == SUCCESS) || ((temp_sleep_status & LPM_SUSPEND_DM) == LPM_SUSPEND_DM)) {
		if (lpm_resume_dm() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	if ((ret == SUCCESS) || ((temp_sleep_status & LPM_SAVE_MMR_LOCK) == LPM_SAVE_MMR_LOCK)) {
		if (lpm_restore_mmr_lock() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	if ((ret == SUCCESS) || ((temp_sleep_status & LPM_CLOCK_SUSPEND) == LPM_CLOCK_SUSPEND)) {
		if (clks_resume() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	if (ret == SUCCESS) {
		if (lpm_resume_restore_RM_context() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	if ((ret == SUCCESS) || ((temp_sleep_status & LPM_SUSPEND_POWERMASTER) == LPM_SUSPEND_POWERMASTER)) {
		if (lpm_resume_send_core_resume_message() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	if ((ret == SUCCESS) || ((temp_sleep_status & LPM_DEVICE_DEINIT) == LPM_DEVICE_DEINIT)) {
		if (devices_init() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	for (i = 0; i < TIMEOUT_10MS; i++) {
		osal_delay(1);
	}

	if ((ret == SUCCESS) || ((temp_sleep_status & LPM_SUSPEND_POWERMASTER) == LPM_SUSPEND_POWERMASTER)) {
		if (lpm_resume_release_reset_of_power_master() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	if ((ret == SUCCESS) || ((temp_sleep_status & LPM_SAVE_MAIN_PADCONFIG) == LPM_SAVE_MAIN_PADCONFIG)) {
		if (lpm_resume_restore_main_padconf() != SUCCESS) {
			lpm_hang_abort();
		}
	}

	/* Open the mode selection lock */
	lpm_locked = SFALSE;

	return ret;
}

s32 dm_lpm_wake_reason_handler(u32 *msg_recv)
{
	struct tisci_msg_lpm_wake_reason_resp *resp =
		(struct tisci_msg_lpm_wake_reason_resp *) msg_recv;
	s32 ret = SUCCESS;

	resp->hdr.flags = 0U;
	resp->wake_source = lpm_get_wake_up_source();
	/* Write 0 to the timestamp value as the support to get time in sleep has not been added yet */
	resp->wake_timestamp = 0;

	return ret;
}

s32 dm_set_io_isolation_handler(u32 *msg_recv)
{
	struct tisci_msg_set_io_isolation_req *req =
		(struct tisci_msg_set_io_isolation_req *) msg_recv;
	s32 ret = EFAIL;
	u32 reg;
	u32 i = 0;

	/* Unlock partition 6 of wakeup ctrl mmr */
	ctrlmmr_unlock(WKUP_CTRL_BASE, 6);
	if (req->state == TISCI_MSG_VALUE_IO_ENABLE) {
		writel(WKUP_CTRL_DEEPSLEEP_CTRL_ENABLE_IO, (WKUP_CTRL_BASE + WKUP_CTRL_DEEPSLEEP_CTRL));
		writel(WKUP_CTRL_PMCTRL_IO_GLB_ENABLE_IO, (WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_GLB));

		/* Set global wuen */
		reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0);
		reg = reg & WKUP_CTRL_PMCTRL_IO_0_WRITE_MASK;
		reg = reg | WKUP_CTRL_PMCTRL_IO_0_GLOBAL_WUEN;
		writel(reg, WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0);

		reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_1);
		reg = reg & WKUP_CTRL_PMCTRL_IO_0_WRITE_MASK;
		reg = reg | WKUP_CTRL_PMCTRL_IO_0_GLOBAL_WUEN;
		writel(reg, WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_1);

		/* Set global isoin */
		reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0);
		reg = reg & WKUP_CTRL_PMCTRL_IO_0_WRITE_MASK;
		reg = reg | WKUP_CTRL_PMCTRL_IO_0_IO_ISO_CTRL;
		writel(reg, WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0);

		reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_1);
		reg = reg & WKUP_CTRL_PMCTRL_IO_0_WRITE_MASK;
		reg = reg | WKUP_CTRL_PMCTRL_IO_0_IO_ISO_CTRL;
		writel(reg, WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_1);

		/* Wait for wu clock state to be 1*/
		i = 0;
		do {
			ret = ETIMEDOUT;
			reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0);
			if ((reg & WKUP_CTRL_PMCTRL_IO_0_IO_ISO_STATUS) == WKUP_CTRL_PMCTRL_IO_0_IO_ISO_STATUS) {
				ret = SUCCESS;
				break;
			}
			osal_delay(1);
		} while (i++ < TIMEOUT_10MS);
		i = 0;
		do {
			ret = ETIMEDOUT;
			reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_1);
			if ((reg & WKUP_CTRL_PMCTRL_IO_0_IO_ISO_STATUS) == WKUP_CTRL_PMCTRL_IO_0_IO_ISO_STATUS) {
				ret = SUCCESS;
				break;
			}
			osal_delay(1);
		} while (i++ < TIMEOUT_10MS);
	} else if (req->state == TISCI_MSG_VALUE_IO_DISABLE) {
		/* Clear global wuen */
		reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0);
		reg = reg & WKUP_CTRL_PMCTRL_IO_0_WRITE_MASK;
		reg = reg & (~WKUP_CTRL_PMCTRL_IO_0_GLOBAL_WUEN);
		writel(reg, WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0);

		reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_1);
		reg = reg & WKUP_CTRL_PMCTRL_IO_0_WRITE_MASK;
		reg = reg & (~WKUP_CTRL_PMCTRL_IO_0_GLOBAL_WUEN);
		writel(reg, WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_1);

		/* Clear global isoin */
		reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0);
		reg = reg & WKUP_CTRL_PMCTRL_IO_0_WRITE_MASK;
		reg = reg & (~WKUP_CTRL_PMCTRL_IO_0_IO_ISO_CTRL);
		writel(reg, WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_0);

		reg = readl(WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_1);
		reg = reg & WKUP_CTRL_PMCTRL_IO_0_WRITE_MASK;
		reg = reg & (~WKUP_CTRL_PMCTRL_IO_0_IO_ISO_CTRL);
		writel(reg, WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_1);

		writel(WKUP_CTRL_DEEPSLEEP_CTRL_DISABLE_IO, (WKUP_CTRL_BASE + WKUP_CTRL_DEEPSLEEP_CTRL));
		writel(WKUP_CTRL_PMCTRL_IO_GLB_DISABLE_IO, (WKUP_CTRL_BASE + WKUP_CTRL_PMCTRL_IO_GLB));

		ret = SUCCESS;
	} else {
		/* Do Nothing */
	}
	return ret;
}

s32 dm_lpm_set_device_constraint(u32 *msg_recv)
{
	s32 ret = SUCCESS;
	struct tisci_msg_lpm_set_device_constraint_req *req =
		(struct tisci_msg_lpm_set_device_constraint_req *) msg_recv;
	struct tisci_msg_lpm_set_device_constraint_resp *resp =
		(struct tisci_msg_lpm_set_device_constraint_resp *) msg_recv;
	struct device *dev = NULL;
	u8 id = req->id;
	sbool state = (sbool) req->state;
	u8 host_id = req->hdr.host;
	u8 host_idx;

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_LPM_SET_DEVICE_CONSTRAINT);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID, id);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_VAL, state);

	resp->hdr.flags = 0U;

	if (state == STRUE) {
		/* Prepare the host and device for setting constraints - Exclusive rights valued */
		ret = device_prepare_exclusive(host_id, id, &host_idx, &dev);
		if (ret == SUCCESS) {
			/* Set constraint */
			dev_cons[id] |= (1U << host_idx);
		}
	} else {
		/* Prepare the host and device for clearing constraints - Can be cleared irrespective of exclusive rights */
		ret = device_prepare_nonexclusive(host_id, id, &host_idx, &dev);
		if (ret == SUCCESS) {
			/* Clear constraint */
			dev_cons[id] &= ~(1U << host_idx);
		}
	}

	return ret;
}

s32 dm_lpm_set_latency_constraint(u32 *msg_recv)
{
	s32 ret = SUCCESS;
	struct tisci_msg_lpm_set_latency_constraint_req *req =
		(struct tisci_msg_lpm_set_latency_constraint_req *) msg_recv;
	struct tisci_msg_lpm_set_latency_constraint_resp *resp =
		(struct tisci_msg_lpm_set_latency_constraint_resp *) msg_recv;
	u16 wkup_latency = req->wkup_latency;
	sbool state = (sbool) req->state;
	u8 host_id = req->hdr.host;
	u8 host_idx;

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_LPM_SET_LATENCY_CONSTRAINT);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_LATENCY, wkup_latency);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_VAL, state);

	resp->hdr.flags = 0U;

	/* Check if current host is valid and get lookup host ID */
	host_idx = host_idx_lookup(host_id);
	if (host_idx == HOST_IDX_NONE) {
		ret = -EFAIL;
	}

	if (ret == SUCCESS) {
		if (state == STRUE) {
			/* Set latency constraint */
			latency[host_idx] = (LPM_WKUP_LATENCY_VALID_FLAG | wkup_latency);
		} else {
			/* Clear latency constraint */
			latency[host_idx] = 0U;
		}
	}

	return ret;
}
