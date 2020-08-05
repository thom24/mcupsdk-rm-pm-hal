/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <soc/j721e_legacy/clk_soc_hfosc0.h>
#include <types/array_size.h>
#include <lib/ioremap.h>
#include <compiler.h>

#define J7_WKUP_CTRL_MMR        0x43000000UL
#define J7_WKUP_DEVSTAT         0x30UL
#define J7_WKUP_BOOTCFG         0x34UL

/*
 * System Oscillator enable control
 * HF Oscillator 0
 * 19.2, 20, 24, 25, 26, 27MHz
 */
static u32 clk_soc_hfosc0_get_freq(struct clk *clk UNUSED)
{
	const u32 freq_table[] = {
		FREQ_MHZ(19.2),
		FREQ_MHZ(20.0),
		FREQ_MHZ(24.0),
		FREQ_MHZ(25.0),
		FREQ_MHZ(26.0),
		FREQ_MHZ(27.0),
	};
	u32 ret = 0;
	u32 v;

	v = readl(J7_WKUP_CTRL_MMR + J7_WKUP_DEVSTAT) & 0x7UL;
	if (v < ARRAY_SIZE(freq_table)) {
		ret = freq_table[v];
	}

	return ret;
}

static u32 clk_soc_hfosc0_get_state(struct clk *clk UNUSED)
{
	return CLK_HW_STATE_ENABLED;
}

const struct clk_drv clk_drv_soc_hfosc0 = {
	.get_freq	= clk_soc_hfosc0_get_freq,
	.get_state	= clk_soc_hfosc0_get_state,
};
