/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef CLK_DIV_H
#define CLK_DIV_H

#include <clk.h>

struct clk_data_div {
	struct clk_drv_data	data;
	u16			n;
	u16			default_div;
};

struct clk_data_div_reg {
	u32			reg;
	struct clk_data_div	data_div;
	u8			bit : 7;
	u8			start_at_1 : 1;
};

struct clk_data_div_reg_go {
	u32			reg;
	struct clk_data_div	data_div;
	u8			bit : 7;
	u8			start_at_1 : 1;
	u8			go;
};

struct clk_drv_div {
	struct clk_drv	drv;
	sbool		(*set_div)(struct clk *clkp, u32 d);
	u32		(*get_div)(struct clk *clkp);
	sbool		(*valid_div)(struct clk *clkp, u32 d);
};

extern const struct clk_drv_div clk_drv_div_reg;
extern const struct clk_drv_div clk_drv_div_reg_ro;
extern const struct clk_drv_div clk_drv_div_reg_go;
extern const struct clk_drv_div clk_drv_div_fixed;

sbool clk_div_notify_freq(struct clk *clkp, u32 parent_freq_hz, sbool query);
u32 clk_div_set_freq(struct clk *clkp, u32 target_hz, u32 min_hz, u32 max_hz, sbool query, sbool *changed);
u32 clk_div_get_freq(struct clk *clkp);

u32 clk_div_reg_go_get_div(struct clk *clkp);
sbool clk_div_reg_go_set_div(struct clk *clkp, u32 d);
u32 clk_div_reg_get_div(struct clk *clkp);
sbool clk_div_reg_set_div(struct clk *clkp, u32 d);

u32 clk_get_div(struct clk *clkp);
sbool clk_set_div(struct clk *clkp, u32 d);
s32 clk_div_init(struct clk *clkp);

#endif
