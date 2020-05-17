/*
 * DMSC PM firmware
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef CLK_PLL_16FFT_H
#define CLK_PLL_16FFT_H

#include <clk_pll.h>

struct clk_data_pll_16fft {
	struct clk_data_pll	data_pll;
	u32			base;
	u8			idx;
};

extern const struct clk_drv clk_drv_pll_16fft;
extern const struct clk_drv_div clk_drv_div_pll_16fft_postdiv;
extern const struct clk_drv_div clk_drv_div_pll_16fft_hsdiv;

#endif
