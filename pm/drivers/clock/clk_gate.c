/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <clk_gate.h>
#include <clk_mux.h>
#include <lib/container_of.h>
#include <lib/ioremap.h>

static sbool clk_gate_set_state(struct clk *clk, sbool enable)
{
	const struct clk_data *clk_data = clk_get_data(clk);
	const struct clk_data_reg *reg;
	u32 v;
	s32 err;
	sbool ret = STRUE;

	reg = container_of(clk_data->data, const struct clk_data_reg, data);

	v = readl(reg->reg);
	if (enable) {
		v |= BIT(reg->bit);
	} else {
		v &= ~BIT(reg->bit);
	}
	err = pm_writel_verified(v, reg->reg);
	if (err != SUCCESS) {
		ret = SFALSE;
	}

	return ret;
}

static u32 clk_gate_get_state(struct clk *clk)
{
	const struct clk_data *clk_data = clk_get_data(clk);
	const struct clk_parent *p;
	struct clk *clk_parent = NULL;
	s32 ret = CLK_HW_STATE_ENABLED;

	p = clk_get_parent(clk);
	if (p) {
		clk_parent = clk_lookup((clk_idx_t) p->clk);
	}

	if (clk_parent) {
		ret = clk_get_state(clk_parent);
	} else {
		/* No parent...cannot function */
		ret = CLK_HW_STATE_DISABLED;
	}

	if (ret == CLK_HW_STATE_ENABLED) {
		const struct clk_data_reg *reg;

		/* Parent is enabled, are we gating it? */
		reg = container_of(clk_data->data, const struct clk_data_reg,
				   data);
		if (!(readl(reg->reg) & BIT(reg->bit))) {
			ret = CLK_HW_STATE_DISABLED;
		}
	}

	return ret;
}

const struct clk_drv clk_gate_drv_reg = {
	.set_state	= clk_gate_set_state,
	.get_state	= clk_gate_get_state,
};
