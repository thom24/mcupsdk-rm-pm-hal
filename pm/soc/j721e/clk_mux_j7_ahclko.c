/*
 * DMSC firmware
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <soc/j721e/clk_mux_j7_ahclko.h>
#include <lib/container_of.h>
#include <ilog.h>
#include <lib/ioremap.h>
#include <lib/io.h>
#include <clk_mux.h>
#include <compiler.h>
#include <lib/trace.h>

#define J7ES_AUDIO_REFCLKN_CTRL_MUX_MASK        0x1FUL
#define J7ES_AUDIO_REFCLKN_CTRL_DIR_BIT         BIT(15)

static const struct clk_parent *clk_mux_j7_ahclko_get_parent(struct clk *clk)
{
	const struct clk_data *clk_data = clk_get_data(clk);
	const struct clk_data_mux *mux;
	const struct clk_data_mux_reg *reg;
	u32 v;
	u32 mux_select;
	sbool pin_output;
	u32 parent;
	const struct clk_parent *ret;

	mux = container_of(clk_data->data, const struct clk_data_mux, data);
	reg = container_of(mux, const struct clk_data_mux_reg, data_mux);

	v = readl(reg->reg);
	mux_select = v & J7ES_AUDIO_REFCLKN_CTRL_MUX_MASK;
	pin_output = (v & J7ES_AUDIO_REFCLKN_CTRL_DIR_BIT) != 0UL;

	if (pin_output) {
		parent = mux_select;
	} else {
		parent = 32UL;
	}

	if (parent < mux->n && mux->parents[parent].div != 0UL) {
		ret = mux->parents + parent;
	} else {
		ret = NULL;
	}

	return ret;
}

static sbool clk_mux_j7_ahclko_set_parent(struct clk *clk, u8 new_parent)
{
	const struct clk_data *clk_data = clk_get_data(clk);
	const struct clk_data_mux *mux;
	const struct clk_data_mux_reg *reg;
	u32 v;
	sbool ret = STRUE;
	sbool change = SFALSE;
	u32 mux_select;
	sbool pin_output;
	s32 err;

	mux = container_of(clk_data->data, const struct clk_data_mux, data);
	reg = container_of(mux, const struct clk_data_mux_reg, data_mux);

	v = readl(reg->reg);
	mux_select = v & J7ES_AUDIO_REFCLKN_CTRL_MUX_MASK;
	pin_output = (v & J7ES_AUDIO_REFCLKN_CTRL_DIR_BIT) != 0UL;

	v &= ~J7ES_AUDIO_REFCLKN_CTRL_MUX_MASK;

	if (new_parent == 32U) {
		change = pin_output == STRUE || 31UL != mux_select;
		v &= ~J7ES_AUDIO_REFCLKN_CTRL_DIR_BIT;
		v |= 31UL;
	} else if (new_parent < 32U) {
		change = pin_output == SFALSE || new_parent != mux_select;
		v |= J7ES_AUDIO_REFCLKN_CTRL_DIR_BIT;
		v |= new_parent;
	} else {
		ret = SFALSE;
	}

	if (ret && change) {
		err = pm_writel_verified(v, reg->reg);
		if (err != SUCCESS) {
			ret = SFALSE;
		}
		pm_trace(TRACE_PM_ACTION_CLOCK_SET_PARENT,
			 ((new_parent << TRACE_PM_VAL_CLOCK_VAL_SHIFT) &
			  TRACE_PM_VAL_CLOCK_VAL_MASK) |
			 ((clk_id(clk) << TRACE_PM_VAL_CLOCK_ID_SHIFT) &
			  TRACE_PM_VAL_CLOCK_ID_MASK));
	}

	return ret;
}

const struct clk_drv_mux clk_drv_mux_reg_j7_ahclko = {
	.set_parent		= clk_mux_j7_ahclko_set_parent,
	.get_parent		= clk_mux_j7_ahclko_get_parent,
};
