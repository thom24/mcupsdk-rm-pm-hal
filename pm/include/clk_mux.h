/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef CLK_MUX_H
#define CLK_MUX_H

#include <clk.h>

struct clk_data_mux {
	struct clk_drv_data	data;
	u32			n;
	const struct clk_parent *parents;
};

struct clk_data_mux_reg {
	struct clk_data_mux	data_mux;
	u32			reg;
	u8			bit;
};

struct clk_drv_mux {
	struct clk_drv		drv;
	sbool			(*set_parent)(struct clk *, u8);
	const struct clk_parent * (*get_parent)(struct clk *);
};

extern const struct clk_drv_mux clk_drv_mux_reg_ro;
extern const struct clk_drv_mux clk_drv_mux_reg;

const struct clk_parent *clk_get_parent(struct clk *clk);
sbool clk_set_parent(struct clk *clk, u8 new_parent);

#endif
