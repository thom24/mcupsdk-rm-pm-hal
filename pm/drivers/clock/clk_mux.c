/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <clk_mux.h>
#include <lib/container_of.h>
#include <ilog.h>
#include <lib/ioremap.h>
#include <lib/trace.h>

static const struct clk_parent *clk_mux_get_parent(struct clk *clk)
{
	const struct clk_data *clk_data = clk_get_data(clk);
	const struct clk_data_mux *mux;
	const struct clk_data_mux_reg *reg;
	u32 v;

	mux = container_of(clk_data->data, const struct clk_data_mux, data);
	reg = container_of(mux, const struct clk_data_mux_reg, data_mux);

	/*
	 * Hack, temporarily return parent 0 for muxes without register
	 * assignments.
	 */
	if (reg->reg == 0) {
		v = 0;
	} else {
		v = readl(reg->reg);
		v >>= reg->bit;
		v &= (1 << ilog32(mux->n - 1)) - 1;
	}

	return (v < mux->n && mux->parents[v].div) ? &mux->parents[v] : NULL;
}

static sbool clk_mux_set_parent(struct clk *clk, u8 new_parent)
{
	const struct clk_data *clk_data = clk_get_data(clk);
	const struct clk_data_mux *mux;
	const struct clk_data_mux_reg *reg;
	u32 v;
	sbool ret = STRUE;

	mux = container_of(clk_data->data, const struct clk_data_mux, data);
	reg = container_of(mux, const struct clk_data_mux_reg, data_mux);

	if (reg->reg == 0) {
		/*
		 * Hack, temporarily ignore assignments for muxes without
		 * register assignments.
		 */
	} else {
		s32 err;
		v = readl(reg->reg);
		v &= ~(((1 << ilog32(mux->n - 1)) - 1) << reg->bit);
		v |= new_parent << reg->bit;
		err = pm_writel_verified(v, reg->reg);
		if (err != SUCCESS) {
			ret = SFALSE;
		} else {
			pm_trace(TRACE_PM_ACTION_CLOCK_SET_PARENT,
				 ((new_parent << TRACE_PM_VAL_CLOCK_VAL_SHIFT) &
				  TRACE_PM_VAL_CLOCK_VAL_MASK) |
				 ((clk_id(clk) << TRACE_PM_VAL_CLOCK_ID_SHIFT) &
				  TRACE_PM_VAL_CLOCK_ID_MASK));
		}
	}

	return ret;
}

const struct clk_drv_mux clk_drv_mux_reg_ro = {
	.get_parent	= clk_mux_get_parent,
};

const struct clk_drv_mux clk_drv_mux_reg = {
	.set_parent		= clk_mux_set_parent,
	.get_parent		= clk_mux_get_parent,
};

const struct clk_parent *clk_get_parent(struct clk *clk)
{
	const struct clk_data *clk_data = clk_get_data(clk);

	if (clk_data->type == CLK_TYPE_MUX) {
		const struct clk_drv_mux *mux;
		mux = container_of(clk_data->drv, const struct clk_drv_mux,
				   drv);
		return mux->get_parent(clk);
	}
	return clk_data->parent.div ? &clk_data->parent : NULL;
}

/* FIXME: freq change ok/notify? new freq in range? */
sbool clk_set_parent(struct clk *clk, u8 new_parent)
{
	const struct clk_data *clk_data = clk_get_data(clk);
	const struct clk_drv_mux *mux_drv = NULL;
	const struct clk_data_mux *mux_data = NULL;
	const struct clk_parent *op;
	struct clk *parent;
	sbool ret = STRUE;
	sbool done = SFALSE;

	if (clk_data->type != CLK_TYPE_MUX) {
		ret = SFALSE;
		done = STRUE;
	}

	if (!done) {
		mux_data = container_of(clk_data->data,
					const struct clk_data_mux, data);
		if (new_parent >= mux_data->n) {
			ret = SFALSE;
			done = STRUE;
		} else if (!mux_data->parents[new_parent].div) {
			ret = SFALSE;
			done = STRUE;
		}
	}

	if (!done) {
		mux_drv = container_of(clk_data->drv,
				       const struct clk_drv_mux, drv);
		if (!mux_drv->set_parent) {
			ret = SFALSE;
			done = STRUE;
		}
	}

	if (!done) {
		op = mux_drv->get_parent(clk);
		if (op && op->clk == mux_data->parents[new_parent].clk) {
			ret = STRUE;
			done = STRUE;
		}
	}

	if (!done) {
		parent = clk_lookup((clk_idx_t) mux_data->parents[new_parent].clk);
		if (!parent) {
			ret = SFALSE;
			done = STRUE;
		} else if ((clk->flags & CLK_FLAG_INITIALIZED) == 0U) {
			ret = SFALSE;
			done = STRUE;
		} else if (clk->ref_count == 0U) {
			/* No get neccessary */
		} else if (!clk_get(parent)) {
			ret = SFALSE;
			done = STRUE;
		}
	}

	if (!done) {
		if (!mux_drv->set_parent(clk, new_parent)) {
			if (clk->ref_count != 0U) {
				clk_put(parent);
			}
			ret = SFALSE;
			done = STRUE;
		}
	}

	if (!done) {
		if (op && clk->ref_count != 0U) {
			struct clk *op_parent;
			op_parent = clk_lookup((clk_idx_t) op->clk);
			if (op_parent) {
				clk_put(op_parent);
			}
		}
	}

	return ret;
}
