/*
 * DMSC firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2019-2020, Texas Instruments Incorporated
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

#include <sleep.h>
#include <types/array_size.h>
#include <dmsc.h>
#include <soc/j7200/devices.h>
#include <lib/ioremap.h>
#include <sys-reset.h>
#include <device_pm.h>
#include <lib/trace.h>
#include <osal/osal_clock.h>
#include <clk.h>
#include <soc_domgrps.h>
#include <soc_devgrps.h>
#include <rm.h>

#define WKUP_CTRL_BASE  0x43000000

#define CTRLMMR_WKUP_MAIN_WARM_RST_CTRL                 0x18174
#define CTRLMMR_WKUP_RST_STAT                           0x18178
#define CTRLMMR_WKUP_MCU_WARM_RST_CTRL                  0x1817c

#define WARM_RST_CTRL_VAL                               0x60000
#define MCU_RST_DONE_MASK                               (0x1U << 16U)
#define MAIN_RST_DONE_MASK                              (0x1U << 0U)
#define RESET_WAIT_TIMEOUT                              100
#define RESET_DELAY_PER_ITERATION_US                    1U

static const struct sleep_mode j7200_sleep_modes[] = {
	{
		.name = (char *) "WFI",
	},
};

static u8 j7200_sleep_block[ARRAY_SIZE(j7200_sleep_modes)];

static s32 wait_reset_done_with_timeout(domgrp_t domain)
{
	u8 timeout = RESET_WAIT_TIMEOUT;
	s32 ret = SUCCESS;
	u32 reg = 0U;
	u32 mask;

	if (domain == SOC_DOMGRP_J7200_MAIN) {
		mask = MAIN_RST_DONE_MASK;
	} else {
		mask = MCU_RST_DONE_MASK;
	}

	/* Wait for reset to complete: */
	do {
		reg = readl(WKUP_CTRL_BASE + CTRLMMR_WKUP_RST_STAT);
		reg &= mask;

		if (reg != 0U) {
			osal_delay(RESET_DELAY_PER_ITERATION_US);
		}
		timeout--;
	} while ((timeout != 0U) && (reg != 0U));

	if (timeout == 0U) {
		ret = -ETIMEDOUT;
	}

	return ret;
}

static s32 j7200_sys_reset_handler(domgrp_t domain)
{
	struct device *dev;
	s32 ret = SUCCESS;
	u32 reset_reg_offset;
	u8 trace_action = TRACE_PM_ACTION_SYSRESET;
	u32 trace_val = TRACE_PM_ACTION_SYSRESET_ERR_VAL_SUCCESS;

	/* PSC0: Disable MAIN2WKUPMCU bridge */
	dev = device_lookup(J7200_DEV_MAIN2WKUPMCU_VD);
	soc_device_ret_enable(dev);
	soc_device_disable(dev, SFALSE);

	/* WKUP_PSC0: Disable WKUPMCU2MAIN bridge */
	dev = device_lookup(J7200_DEV_WKUPMCU2MAIN_VD);
	soc_device_ret_enable(dev);
	soc_device_disable(dev, SFALSE);

	switch (domain) {
	/* SOC_DOMGRP_J7200_SYSTEM is for backward compatibility.
	   It behaves the same as SOC_DOMGRP_J7200_MCU */
	case SOC_DOMGRP_J7200_SYSTEM:
		reset_reg_offset = CTRLMMR_WKUP_MCU_WARM_RST_CTRL;
		break;
	case SOC_DOMGRP_J7200_MCU:
		reset_reg_offset = CTRLMMR_WKUP_MCU_WARM_RST_CTRL;
		break;
	case SOC_DOMGRP_J7200_MAIN:
		reset_reg_offset = CTRLMMR_WKUP_MAIN_WARM_RST_CTRL;

		/* power management de-initialization
		 * PM_DEVGRP_01 belongs to the MAIN domain in J7200
		 */
		ret = devices_deinit(PM_DEVGRP_01);
		if (ret == SUCCESS) {
			ret = clk_deinit_pm_devgrp(PM_DEVGRP_01);
		}

		/* resource management de-initialization */
		if (ret == SUCCESS) {
			ret = rm_deinit(SOC_DEVGRP_J7200_MAIN);
		}

		if (ret != SUCCESS) {
			trace_val |= TRACE_PM_ACTION_SYSRESET_ERR_VAL_DEINIT_FAIL;
		}
		break;
	default:
		trace_val |= TRACE_PM_ACTION_SYSRESET_ERR_VAL_INVALID_ARG;
		ret = -EINVAL;
		break;
	}

	if (ret == SUCCESS) {
		/* Issue chosen domain warm reset. */
		writel(WARM_RST_CTRL_VAL, WKUP_CTRL_BASE + reset_reg_offset);

		ret = wait_reset_done_with_timeout(domain);
		if (ret != SUCCESS) {
			trace_val |= TRACE_PM_ACTION_SYSRESET_ERR_VAL_TIMEOUT;
		}
	} else {
		trace_action |= TRACE_PM_ACTION_FAIL;
	}

	pm_trace(trace_action,
		 ((domain << TRACE_PM_ACTION_SYSRESET_DOMAIN_SHIFT) &
		  TRACE_PM_ACTION_SYSRESET_DOMAIN_MASK) | trace_val);

	return ret;
}

s32 dmsc_init(void)
{
	sys_reset_handler_register(j7200_sys_reset_handler);

	return sleep_modes_register(j7200_sleep_modes, j7200_sleep_block,
				    ARRAY_SIZE(j7200_sleep_modes));
}
