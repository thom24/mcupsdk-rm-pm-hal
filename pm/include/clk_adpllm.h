/*
 * DMSC PM firmware
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef CLK_ADPLLM_H
#define CLK_ADPLLM_H

#include <clk_pll.h>
#include <clk_div.h>
#include <types/sbool.h>

struct clk_data_pll_adpllm {
	struct clk_data_pll	data_pll;
	u32			base;
	sbool			hsdiv;
	sbool			ljm;
	u8			idx;
};

extern const struct clk_drv clk_drv_adpllm;
extern const struct clk_drv_mux clk_drv_adpllm_bypass_mux;

struct clk_data_hsdiv {
	struct clk_data_div_reg data_div_reg;
	u8			go_bit : 5;
	u8			idx : 3;
	u32			go_reg;
};

extern const struct clk_drv_div clk_drv_div_hsdiv;
extern const struct clk_drv_div clk_drv_div_hsdiv4;

#endif
