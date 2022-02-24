/*
 * DM Stub Firmware
 *
 * DM Stub main low power functionality
 *
 * Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <lib/bitops.h>
#include <string.h>
#include <tisci/lpm/tisci_lpm.h>
#include <types/errno.h>
#include <baseaddress.h>
#include <mcu_ctrl_mmr.h>
#include <wkup_ctrl_mmr.h>

#include "lpm_io.h"
#include "ctrlmmr_raw.h"
#include "ddr.h"
#include "pll_16fft_raw.h"
#include "psc_raw.h"
#include "sec_proxy.h"

enum lpm_mode {
	LPM_DEEPSLEEP,
	LPM_MCU_ONLY,
	LPM_STANDBY,
};

struct main_pd_lpsc {
	u8 pd;
	u8 lpsc;
};

static enum lpm_mode g_lpm_mode;

/* FIXME IO_ISO_TIMEOUT should be about 10us */
#define IO_ISO_TIMEOUT	10000
#define PLLOFFSET(idx) (0x1000 * (idx))

static struct pll_raw_data mcu_pll = { .base = MCU_PLL_MMR_BASE, };
static struct pll_raw_data main_pll1 =
		{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(1), };
static struct pll_raw_data main_pll2 =
		{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(2), };
static struct pll_raw_data main_pll8 =
		{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(8), };
static struct pll_raw_data main_pll12 =
		{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(12), };
static struct pll_raw_data main_pll16 =
		{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(16), };
static struct pll_raw_data main_pll17 =
		{ .base = MAIN_PLL_MMR_BASE + PLLOFFSET(17), };

/* MAIN LPSCs to be disabled during Deepsleep phase 1 */
/* FIXME am62x specific, move to soc specific place */
static struct main_pd_lpsc main_lpscs_phase1[] = {
	{ PD_A53_0,		LPSC_A53_0 },
	{ PD_A53_CLUSTER_0,	LPSC_A53_CLUSTER_0 },
	/* FIXME disabling LPSC_MAIN_IP causes problem on vlab, skip it for now */
/*	{ PD_MAIN_IP,		LPSC_MAIN_IP },*/
	{ PD_GP_CORE_CTL,	LPSC_MAIN_TEST },
	{ PD_SMS,		LPSC_HSM },
	{ PD_SMS,		LPSC_TIFS },
	{ PD_SMS,		LPSC_SA3UL },
	{ PD_SMS,		LPSC_SMS_COMMON }
};

/* MAIN LPSCs to be disabled during Deepsleep phase 2 */
/* FIXME am62x specific, move to soc specific place */
static struct main_pd_lpsc main_lpscs_phase2[] = {
	/* FIXME this times out, so skip it for now */
/*	{ PD_DEBUG,		LPSC_DEBUGSS },*/
};

/* MCU LPSCs to be disabled during Deepsleep */
/* FIXME am62x specific, move to soc specific place */
static int mcu_lpscs[] = {
	LPSC_MCU_TEST,
	LPSC_MCU_COMMON
};

static void abort()
{
	while (1) { }
}

static enum lpm_mode get_lpm_mode()
{
	return LPM_DEEPSLEEP;
}

static void set_ddr_reset_isolation() { }
static void release_ddr_reset_isolation() {}
static void set_usb_reset_isolation() { }
static void release_usb_reset_isolation() {}

static s32 disable_main_lpsc(struct main_pd_lpsc *lpscs, u32 n_lpscs)
{
	u32 i;
	int ret;

	for (i = 0; i < n_lpscs; i++) {
		psc_raw_lpsc_set_state(MAIN_PSC_BASE, lpscs[i].lpsc,
				MDCTL_STATE_DISABLE, 0);
		psc_raw_pd_initiate(MAIN_PSC_BASE, lpscs[i].pd);
		ret = psc_raw_pd_wait(MAIN_PSC_BASE, lpscs[i].pd);
		if (ret)
			return ret;
	}
	return 0;
}

static void bypass_main_pll()
{
	/* disable all HSDIV in MAIN_PLLCTRL, bypass all MAIN PLL
	 * except clock for Debug, PLL0, PLL15
	 */
	pll_save(&main_pll1);
	pll_save(&main_pll2);
	pll_save(&main_pll8);
	pll_save(&main_pll12);
	pll_save(&main_pll16);
	pll_save(&main_pll17);

	pll_disable(&main_pll1, 0xFFFF);
	pll_disable(&main_pll2, 0xFFFF);
	pll_disable(&main_pll8, 0xFFFF);
	pll_disable(&main_pll12, 0xFFFF);
	pll_disable(&main_pll16, 0xFFFF);
	pll_disable(&main_pll17, 0xFFFF);
}


static void wait_for_debug(void)
{
	volatile unsigned long x = 0x12341234;
	/* TODO retrieve the DEBUG flag */
	int debug_flag = 0x0;

	if (!debug_flag)
		return;

	while (x) {
	}
}

static void config_wake_sources() { }

static int enable_main_io_isolation()
{
	return 0;
}

static int disable_main_io_isolation()
{
	return 0;
}

static void config_clk_muxes()
{
	/* config gpio/wdt/32k clk muxes */
}

static void disable_main_remain_pll()
{
	/* disable remaining HSDIV & PLL in MAIN */
	return;
}

static int enable_main_remain_pll()
{
	/* config additional MAIN PLLs and PSCs for EMIF */
	return ret;
}

static s32 disable_mcu_domain()
{
	u32 i;
	s32 ret;

	for (i = 0; i < sizeof(mcu_lpscs)/sizeof(int); i++)
		psc_raw_lpsc_set_state(MCU_PSC_BASE, mcu_lpscs[i],
				MDCTL_STATE_DISABLE, 0);

	psc_raw_pd_set_state(MCU_PSC_BASE, PD_GP_CORE_CTL_MCU,
			PDCTL_STATE_OFF, 0);
	psc_raw_pd_initiate(MCU_PSC_BASE, PD_GP_CORE_CTL_MCU);
	ret = psc_raw_pd_wait(MCU_PSC_BASE, PD_GP_CORE_CTL_MCU);
	if (ret)
		return ret;

	psc_raw_pd_set_state(MCU_PSC_BASE, PD_MCU_M4F, PDCTL_STATE_OFF, 0);
	psc_raw_pd_initiate(MCU_PSC_BASE, PD_MCU_M4F);
	ret = psc_raw_pd_wait(MCU_PSC_BASE, PD_MCU_M4F);
	if (ret)
		return ret;
	return 0;
}

static void enable_mcu_remain_pll() { }

static void disable_mcu_io_isolation()
{
	/* disable WKUP IO Daisy Chain & IO isolation */
}

/* Send TISCI ROM Boot image message containing location
 * and boot address to load FS stub from SPS Memory
 */
#ifndef CONFIG_LPM_DM_STUB_STANDALONE
static s32 send_tisci_msg_firmware_load()
{
	s32 ret = 0;
	struct tisci_msg_firmware_load_resp resp;
	struct tisci_msg_firmware_load_req req = {
		.hdr = {
			.type = TISCI_MSG_FIRMWARE_LOAD,
		},
		/* TODO  fill the addr and size */
		.image_addr = 0,
		.image_size = 0,
	};

	ret = sproxy_send_msg(&req, sizeof(req));
	if(ret)
		return ret;

	memset(&resp, 0, sizeof(resp));
	ret = sproxy_receive_msg(&resp, sizeof(resp));

	if (ret)
		return ret;

	if (resp.hdr.type != MSG_FIRMWARE_LOAD_RESULT ||
			resp.hdr.flags != MSG_FLAG_CERT_AUTH_PASS ||
			!(resp.hdr.flags & TISCI_MSG_FLAG_ACK))
		ret = -EINVAL;

	return ret;
}

static s32 receive_tisci_msg_continue_resume()
{
	struct tisci_msg_continue_resume_req req;
	s32 ret = 0;

	memset(&req, 0, sizeof(req));
	ret = sproxy_receive_msg(&req, sizeof(req));

	if (ret)
		return ret;

	if (req.hdr.type != TISCI_MSG_CONTINUE_RESUME)
		ret = -EINVAL;

	return ret;
}

static s32 send_tisci_msg_continue_resume()
{
	s32 ret = 0;
	struct tisci_msg_continue_resume_resp resp = {
		.hdr = {
			.type = TISCI_MSG_CONTINUE_RESUME,
			.flags = TISCI_MSG_FLAG_ACK,

		},
		/* TODO  fill the ctx address */
		.ctx_lo = 0,
		.ctx_hi = 0,
	};

	ret = sproxy_send_msg(&resp, sizeof(resp));
	if(ret)
		return ret;

	return ret;
}

static s32 receive_tisci_msg_sync_resume()
{
	struct tisci_msg_sync_resume_resp resp;
	s32 ret = 0;

	memset(&resp, 0, sizeof(resp));
	ret = sproxy_receive_msg(&resp, sizeof(resp));

	if (ret)
		return ret;

	if ((resp.hdr.type != TISCI_MSG_CONTINUE_RESUME) ||
			!(resp.hdr.flags & TISCI_MSG_FLAG_ACK))
		ret = -EINVAL;

	return ret;
}
#else
static s32 send_tisci_msg_firmware_load() { return 0; }
static s32 receive_tisci_msg_continue_resume() { return 0; }
static s32 send_tisci_msg_continue_resume() { return 0; }
static s32 receive_tisci_msg_sync_resume() { return 0; }
#endif

static void send_msg_bypass_sms_pll() {}
static void send_msg_restore_sms_pll() {}

static void wait_for_reset_statz() {}
static void wait_for_tifs_ready() {}
static void enable_pll_standby() {}
static void goto_sysfw() {}

void dm_stub_entry(void)
{
	u32 reg;
	u32 n_lpscs;

	g_lpm_mode = get_lpm_mode();

	/* unlock wkup_ctrl_mmr region 2 & 6 */
	ctrlmmr_unlock(WKUP_CTRL_MMR_BASE, 2);
	ctrlmmr_unlock(WKUP_CTRL_MMR_BASE, 6);

	/* unlock mcu_ctrl_mmr region 2 */
	ctrlmmr_unlock(MCU_CTRL_MMR_BASE, 2);

	ddr_enter_self_refesh();

	if (g_lpm_mode == LPM_DEEPSLEEP || g_lpm_mode == LPM_MCU_ONLY) {
		set_ddr_reset_isolation();
		set_usb_reset_isolation();

		/* Disable all LPSCs in MAIN except Debug, Always ON */
		n_lpscs = sizeof(main_lpscs_phase1)/sizeof(struct main_pd_lpsc);
		if (disable_main_lpsc(main_lpscs_phase1, n_lpscs))
			abort();

		/* Disable all HSDIVs in MAIN_PLL, bypass all MAIN PLLs,
		 * except clock for debug, PLL0_HSDIV0, PLL15
		 */
		bypass_main_pll();
	}

	wait_for_debug();

	if (g_lpm_mode == LPM_DEEPSLEEP || g_lpm_mode == LPM_MCU_ONLY) {
		/* Configure selected wake sources
		 * with writes to WKUP0_EN IN WKUP_CTRL
		 */
		config_wake_sources();

		if (enable_main_io_isolation())
			abort();

		/* Disable remaining MAIN LPSCs for debug */
		n_lpscs = sizeof(main_lpscs_phase2)/sizeof(struct main_pd_lpsc);
		if (disable_main_lpsc(main_lpscs_phase2, n_lpscs))
			abort();

		/* Modify WKUP_CLKSEL in WKUP_CTRL
		 * to use MCU_PLL instead of MAIN PLL
		 */
		writel(WKUP_CLKSEL_MCU, WKUP_CTRL_MMR_BASE + WKUP_CLKSEL);

		/* Configure GPIO/WDT/32k Clock muxes */
		config_clk_muxes();

		/* Disable remaining MAIN HSDIVs and PLLs */
		disable_main_remain_pll();

		/* Set WKUP_CTRL DS_DM_RESET.mask to isolate DM
		 * from MAIN domain reset
		 */
		writel(DS_DM_RESET_MASK, WKUP_CTRL_MMR_BASE + DS_DM_RESET);

		/* Write to WKUP_CTRL DS_MAIN.por_pdoff bits to
		 * place Main domain in reset, gate PD_SMS and PD_DEBUG
		 */
		writel(DS_MAIN_OFF, WKUP_CTRL_MMR_BASE + DS_MAIN);
	}

	if (g_lpm_mode == LPM_DEEPSLEEP) {
		/* Disable MCU Domain LPSCs, PDs */
		if (disable_mcu_domain())
			abort();
	}

	if (g_lpm_mode == LPM_DEEPSLEEP || g_lpm_mode == LPM_MCU_ONLY) {
		/* Set WKUP_CTRL.RST_CTRL.main_reset_iso_done_z to 1 to
		 * mask main reset in case of RESET_REQz wakeup
		 */
		reg = readl(WKUP_CTRL_MMR_BASE + RST_CTRL);
		reg |= RST_CTRL_MAIN_RST_ISO_DONE_Z;
		writel(reg, WKUP_CTRL_MMR_BASE + RST_CTRL);
	} else {
		/* Send TISCI message to bypass SMS PLL */
		send_msg_bypass_sms_pll();
	}

	/* Use WKUP_CTRL.WKUP_WWD0_CTRL to gate clock to RTI */
	writel(WWD_STOP, WKUP_CTRL_MMR_BASE + WKUP_WWD0_CTRL);

	if (g_lpm_mode == LPM_DEEPSLEEP) {
		pll_save(&mcu_pll);
		pll_bypass(&mcu_pll);

		/* set MCU_MMR.MCU_PLL_CLKSEL.clkloss_switch_en to 0
		 *     to avoid clk switch
		 */
		reg = readl(MCU_CTRL_MMR_BASE + MCU_PLL_CLKSEL);
		reg &= ~MCU_PLL_CLKSEL_CLKLOSS_SWTCH_EN;
		writel(reg, MCU_CTRL_MMR_BASE + MCU_PLL_CLKSEL);

		/* set MCU_MMR.HFOSC0_CTRL.pd_c to power off of HFOSC PD */
		reg = readl(MCU_CTRL_MMR_BASE + HFOSC0_CTRL);
		reg |= HFOSC0_CTRL_PD_C;
		writel(reg, MCU_CTRL_MMR_BASE + HFOSC0_CTRL);

		/* set OSC_CG_ON_WFI bit in WKUP_CTRL.PMCTRL_MOSC */
		reg = readl(WKUP_CTRL_MMR_BASE + PMCTRL_MOSC);
		reg |= PMCTRL_MOSC_OSC_CG_ON_WFI;
		writel(reg, WKUP_CTRL_MMR_BASE + PMCTRL_MOSC);
	}

	/* enter WFI */
	__asm volatile ("\tWFI");

	/* start resume */
	if (g_lpm_mode == LPM_DEEPSLEEP) {
		/* clear OSC_CG_ON_WFI bit in WKUP_CTRL.PMCTRL_MOSC */
		reg = readl(WKUP_CTRL_MMR_BASE + PMCTRL_MOSC);
		reg &= ~PMCTRL_MOSC_OSC_CG_ON_WFI;
		writel(reg, WKUP_CTRL_MMR_BASE + PMCTRL_MOSC);

		/* clear MCU_MMR.HFOSC0_CTRL.pd_c and
		 * set MCU_MMR.MCU_PLL_CLKSEL.clkloss_switch_en
		 */
		reg = readl(MCU_CTRL_MMR_BASE + HFOSC0_CTRL);
		reg &= ~HFOSC0_CTRL_PD_C;
		writel(reg, MCU_CTRL_MMR_BASE + HFOSC0_CTRL);

		reg = readl(MCU_CTRL_MMR_BASE + MCU_PLL_CLKSEL);
		reg |= MCU_PLL_CLKSEL_CLKLOSS_SWTCH_EN;
		writel(reg, MCU_CTRL_MMR_BASE + MCU_PLL_CLKSEL);

		if (pll_restore(&mcu_pll))
			abort();
	}

	/* Use WKUP_CTRL.WKUP_WWD0_CTRL to ungate clock to RTI */
	writel(WWD_RUN, WKUP_CTRL_MMR_BASE + WKUP_WWD0_CTRL);

	if (g_lpm_mode == LPM_DEEPSLEEP || g_lpm_mode == LPM_MCU_ONLY) {
		/* Disable WKUP IO Daisy Chain and IO Isolation */
		disable_mcu_io_isolation();

		/* Write 0xdee51ee5 to WKUP DS_MAGIC_WORD to
		 * indicate resume is required to TIFS ROM
		 */
		writel(DS_MAGIC_WORD_RESUME_TIFS,
				WKUP_CTRL_MMR_BASE + DS_MAGIC_WORD);

		/* Write to WKUP_CTRL DS_MAIN.por_pdoff
		 * bits to release Main domain reset
		 */
		writel(DS_MAIN_ON, WKUP_CTRL_MMR_BASE + DS_MAIN);

		/* FIXME unmask WKUP_CTRL.DS_DM_REST? it is set in suspend */
	}

	wait_for_debug();

	if (g_lpm_mode == LPM_DEEPSLEEP || g_lpm_mode == LPM_MCU_ONLY) {
		/* Wait for RESET_STATZ */
		wait_for_reset_statz();

		/* Modify WKUP_CLKSEL in WKUP_CTRL
		 * to use SMS_PLL instead of MCU PLL
		 */
		writel(WKUP_CLKSEL_MAIN, WKUP_CTRL_MMR_BASE + WKUP_CLKSEL);

		/* Configure additional MCU PLLs and PSCs to return to
		 * pre-DeepSleep state
		 */
		enable_mcu_remain_pll();

		/* Poll on WKUP DS_MAGIC_WORD for 0x00d5d02e that indicates
		 * TIFS ROM has completed and execution can continue.
		 * Clear WKUP DS_MAGIC_WORD
		 */
		wait_for_tifs_ready();

		/* Send TISCI ROM Boot image message containing location
		 * and boot address to load FS stub from SPS Memory
		 * TISCI_MSG_FIRMWARE_LOAD
		 */
		if (send_tisci_msg_firmware_load())
			abort();

		/* Wait for TISCI Message to indicate DDR restore can resume */
		/* TISCI_MSG_CONTINUE_RESUME */
		if (receive_tisci_msg_continue_resume())
			abort();

		/* Disable MAIN IO Daisy Chain and IO Isolation */
		if (disable_main_io_isolation())
			abort();

		/* Configure additional MAIN PLLs and PSCs for EMIF operation */
		if (enable_main_remain_pll())
			abort();

		/* Follow procedure to take DDR out of reset isolation
		 * from AM62x_Reset_uArch_v0.81
		 * Possible DDR re-training sequence, pending feedback
		 * from Cadence
		 */
		release_ddr_reset_isolation();
	} else {
		/* Send TISCI message to restore SMS PLL */
		send_msg_restore_sms_pll();

		/* Relock all PLLs as described in Copy of
		 * PSC_PLL_config_LPM_0p5_ch.xlsx
		 */
		enable_pll_standby();
	}

	ddr_exit_self_refresh();

	if (g_lpm_mode == LPM_DEEPSLEEP || g_lpm_mode == LPM_MCU_ONLY) {
		release_usb_reset_isolation();

		/* Send TISCI Message to TIFS to indicate DDR is active and
		 * resume can proceed, include address of TIFS context
		 */
		if (send_tisci_msg_continue_resume())
			abort();

		/* Wait for TISCI_MSG_SYNC_RESUME msg */
		if(receive_tisci_msg_sync_resume())
			abort();
	}

	/* Jump to standard firmware in DDR */
	goto_sysfw();

	/* TODO enter WFI */
}
