/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <clk_pllctrl.h>
#include <lib/container_of.h>
#include <lib/ioremap.h>

#define PLLCTRL_PLLCTRL 		0x100U
#define PLLCTRL_PLLCTRL_PLLEN		BIT(0)
#define PLLCTRL_PLLCTRL_PLLENSRC	BIT(5)

#define PLLCTRL_PLLSTAT			0x13cU
#define PLLCTRL_PLLSTAT_LOCK		BIT(1)

static const struct clk_parent *clk_pllctrl_mux_get_parent(struct clk *clk)
{
	const struct clk_data *clk_data = clk_get_data(clk);
	const struct clk_data_mux *mux;
	const struct clk_data_mux_reg *reg;
	const struct clk_parent *parent = NULL;
	u32 v;

	mux = container_of(clk_data->data, const struct clk_data_mux, data);
	reg = container_of(mux, const struct clk_data_mux_reg, data_mux);

	v = readl(reg->reg + PLLCTRL_PLLCTRL);
	if ((v & PLLCTRL_PLLCTRL_PLLENSRC) != 0U) {
		/* When set, mux is controlled by lock state of PLL */
		v = readl(reg->reg + PLLCTRL_PLLSTAT);
		if ((v & PLLCTRL_PLLSTAT_LOCK) != 0U) {
			/* PLL is locked */
			parent = &mux->parents[1];
		} else {
			/* PLL is in bypass */
			parent = &mux->parents[0];
		}
	} else {
		/* When cleaned, mux is controlled by PLLEN bit */
		if ((v & PLLCTRL_PLLCTRL_PLLEN) != 0U) {
			/* Use pll clock */
			parent = &mux->parents[1];
		} else {
			/* Use bypass clock */
			parent = &mux->parents[0];
		}
	}

	/* If div is 0, parent clock is not connected */
	if ((parent != NULL) && (parent->div == 0U)) {
		parent = NULL;
	}

	return parent;
}

const struct clk_drv_mux clk_drv_pllctrl_mux_reg_ro = {
	.get_parent	= clk_pllctrl_mux_get_parent,
};
