/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef CLK_RPLL028_H
#define CLK_RPLL028_H

#include <clk_pll.h>

struct clk_data_pll_rpll028 {
	struct clk_data_pll	data_pll;
	u32			base;
	u32			stat_reg;
	u32			eval_reg;
	u8			bit;
};

extern const struct clk_drv clk_drv_rpll028;

#endif
