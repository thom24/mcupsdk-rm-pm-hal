/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <clk.h>
#include <device.h>
#include <clk_mux.h>
#include <types/errno.h>
#include <limits.h>
#include <stddef.h>
#include <types.h>
#include <lib/container_of.h>
#include <lib/trace.h>
#include <types/array_size.h>

u32 clk_value_set_freq(struct clk *clkp, u32 target_hz,
		       u32 min_hz __attribute__((unused)),
		       u32 max_hz __attribute__((unused)),
		       sbool query, sbool *changed)
{
	const struct clk_data *clk_data = clk_get_data(clkp);

	if (query) {
		return target_hz;
	}
	*changed = STRUE;
	soc_clock_values[clk_data->freq_idx] = target_hz;
	return target_hz;
}

u32 clk_value_get_freq(struct clk *clkp)
{
	const struct clk_data *clk_data = clk_get_data(clkp);

	return soc_clock_values[clk_data->freq_idx];
}

static sbool clk_input_notify_freq(struct clk	*clkp __attribute__((unused)),
				   u32		parent_freq __attribute__(
					   (unused)),
				   sbool	query __attribute__((unused)))
{
	return SFALSE;
}

static sbool clk_input_set_state(struct clk	*clkp __attribute__((unused)),
				 sbool		enabled __attribute__(
					 (unused)))
{
	return STRUE;
}

static u32 clk_input_get_state(struct clk *clkp __attribute__((unused)))
{
	return CLK_HW_STATE_ENABLED;
}

const struct clk_drv clk_drv_input = {
	.set_freq	= clk_value_set_freq,
	.get_freq	= clk_value_get_freq,
	.notify_freq	= clk_input_notify_freq,
	.set_state	= clk_input_set_state,
	.get_state	= clk_input_get_state,
};

u32 clk_get_parent_freq(struct clk *clkp)
{
	const struct clk_parent *p = NULL;
	struct clk *parent_clk = NULL;
	u32 ret = 0;

	if (clkp) {
		p = clk_get_parent(clkp);
	}

	if (p && p->div) {
		parent_clk = clk_lookup((clk_idx_t) p->clk);
	}

	if (parent_clk) {
		ret = clk_get_freq(parent_clk) / p->div;
	}

	return ret;
}

sbool clk_notify_freq(struct clk *clkp, u32 parent_freq_hz, sbool query)
{
	const struct clk_data *clk_data;
	sbool ret = STRUE;

	if (clkp->freq_change_block_count != 0U) {
		ret = SFALSE;
	}

	clk_data = clk_get_data(clkp);

	if (ret) {
		const struct clk_range *range;
		range = clk_get_range(clk_data->range_idx);
		if ((parent_freq_hz < range->min_hz) ||
		    (parent_freq_hz > range->max_hz)) {
			ret = SFALSE;
		}
	}

	if (ret) {
		if (clk_data->drv->notify_freq != NULL) {
			ret = clk_data->drv->notify_freq(clkp, parent_freq_hz, query);
		} else {
			ret = clk_notify_children_freq(clkp, parent_freq_hz, query);
		}
	}

	if (ret && !query) {
		clkp->flags &= ~CLK_FLAG_CACHED;
	}

	return ret;
}

sbool clk_notify_sibling_freq(struct clk *clkp, struct clk *parent,
			      u32 parent_freq, sbool query)
{
	clk_idx_t i;
	clk_idx_t pid = clk_id(parent);
	clk_idx_t id = clkp ? clk_id(clkp) : CLK_ID_NONE;

	/* We must unfortunately walk clock list to find children */
	for (i = 0U; i < soc_clock_count; i++) {
		const struct clk_parent *p;

		/* Skip over clk */
		if (i == id) {
			continue;
		}

		clkp = clk_lookup(i);
		if (!clkp) {
			continue;
		}

		p = clk_get_parent(clkp);
		if (!p || p->clk != pid) {
			continue;
		}

		if (!clk_notify_freq(clkp, parent_freq / p->div, query)) {
			return SFALSE;
		}
	}

	return STRUE;
}

sbool clk_notify_children_freq(struct clk *parent, u32 parent_freq,
			       sbool query)
{
	/*
	 * Reuse sibling walk function, it just avoids whatever clock is in
	 * clk and matches whatever clocks are children of parent.
	 */
	return clk_notify_sibling_freq(parent, parent, parent_freq, query);
}

u32 __clk_generic_set_freq(struct clk *clkp, struct clk *parent,
			   u32 target_hz, u32 min_hz,
			   u32 max_hz, sbool query,
			   sbool *changed,
			   s32 div)
{
	u32 new_target, new_min, new_max;
	u32 new_parent_freq = 0;

	/* Make sure target fits within out clock frequency type */
	if (ULONG_MAX / div < min_hz) {
		return 0;
	}

	new_min = min_hz * div;
	new_target = target_hz * div;
	new_max = max_hz * div;

	if (new_min < min_hz) {
		return 0;
	}

	/* Cap overflow in target and max */
	if (new_target < new_min) {
		new_target = ULONG_MAX;
	}

	if (new_max < new_target) {
		new_max = ULONG_MAX;
	}

	new_parent_freq = clk_set_freq(parent, new_target, new_min, new_max,
				       STRUE, changed);

	if (!new_parent_freq) {
		return 0;
	}

	/* Check that any siblings can handle the new freq */
	if (*changed && !(clk_notify_sibling_freq(clkp, parent, new_parent_freq,
						  STRUE))) {
		return 0;
	}

	if (query) {
		return new_parent_freq / div;
	}

	/* Actually perform the frequency change */
	clk_set_freq(parent, new_target, new_min, new_max, SFALSE, changed);

	/* Notify new rate to siblings */
	if (*changed) {
		clk_notify_sibling_freq(clkp, parent, new_parent_freq, SFALSE);
	}

	return new_parent_freq / div;
}

static u32 clk_generic_set_freq(struct clk *clkp,
				u32 target_hz,
				u32 min_hz,
				u32 max_hz, sbool query,
				sbool *changed)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_parent *p = clk_get_parent(clkp);
	u32 ret = 0;

	*changed = SFALSE;

	if (p && (clk_data->flags & CLK_DATA_FLAG_MODIFY_PARENT_FREQ)) {
		struct clk *parent;
		parent = clk_lookup((clk_idx_t) p->clk);
		if (parent) {
			ret = __clk_generic_set_freq(clkp, parent, target_hz,
						     min_hz, max_hz, query,
						     changed,
						     p->div);
		}
	} else {
		u32 freq = clk_get_freq(clkp);
		if (freq >= min_hz && freq <= max_hz) {
			ret = freq;
		}
	}

	return ret;
}
#ifdef CONFIG_TRACE
static void clk_set_freq_trace(struct clk *clkp, u32 freq_hz, sbool failed)
#else
static void clk_set_freq_trace(struct clk *clkp __attribute__((unused)), u32 freq_hz, sbool failed)
#endif
{
	u16 trace_act = TRACE_PM_ACTION_CLOCK_SET_RATE;
	u32 val = freq_hz;
	u32 exp_val = 0;

	if (failed) {
		trace_act |= TRACE_PM_ACTION_FAIL;
	}

	while (val > TRACE_PM_VAL_MAX_FREQ) {
		val >>= 1;
		exp_val += 1U;
	}

	pm_trace(trace_act,
		 (val << TRACE_PM_VAL_CLOCK_VAL_SHIFT) |
		 (exp_val << TRACE_PM_VAL_CLOCK_EXP_SHIFT) |
		 ((clk_id(clkp) << TRACE_PM_VAL_CLOCK_ID_SHIFT) &
		  TRACE_PM_VAL_CLOCK_ID_MASK));
}

/*
 * FIXME: When called directly from device_clk_set_freq, it can change
 * the freq without regard for children of the clock
 */
u32 clk_set_freq(struct clk *clkp, u32 target_hz,
		 u32 min_hz, u32 max_hz, sbool query,
		 sbool *changed)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	u32 ret;

	*changed = SFALSE;

	if ((clkp->flags & CLK_FLAG_INITIALIZED) == 0U) {
		ret = 0U;
	} else if (clk_data->drv->set_freq != NULL) {
		ret = clk_data->drv->set_freq(clkp, target_hz, min_hz,
					      max_hz, query, changed);
	} else {
		ret = clk_generic_set_freq(clkp, target_hz, min_hz, max_hz,
					   query, changed);
	}

	clk_set_freq_trace(clkp, target_hz, ret == 0U);

	return ret;
}

u32 clk_get_freq(struct clk *clkp)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	u32 ret;

	if ((clkp->flags & CLK_FLAG_INITIALIZED) == 0U) {
		ret = 0U;
	} else if (clk_data->drv->get_freq != NULL) {
		ret = clk_data->drv->get_freq(clkp);
	} else {
		ret = clk_get_parent_freq(clkp);
	}

	return ret;
}

s32 clk_get_state(struct clk *clkp)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	s32 ret = CLK_HW_STATE_DISABLED;

	if ((clkp->flags & CLK_FLAG_INITIALIZED) == 0U) {
		ret = CLK_HW_STATE_DISABLED;
	} else if (clk_data->drv->get_state != NULL) {
		ret = clk_data->drv->get_state(clkp);
	} else {
		const struct clk_parent *p;
		p = clk_get_parent(clkp);
		if (p) {
			struct clk *clk_parent;
			clk_parent = clk_lookup((clk_idx_t) p->clk);
			if (clk_parent) {
				ret = clk_get_state(clk_parent);
			}
		}
	}

	return ret;
}

sbool clk_set_state(struct clk *clkp, sbool enable)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	sbool ret;

	if ((clkp->flags & CLK_FLAG_INITIALIZED) == 0U) {
		/* defer action */
		ret = STRUE;
	} else if (clk_data->drv->set_state == NULL) {
		ret = STRUE;
	} else {
		ret = clk_data->drv->set_state(clkp, enable);
	}

	return ret;
}

sbool clk_get(struct clk *clkp)
{
	sbool ret = STRUE;

	if (!clkp->ref_count) {
		const struct clk_parent *p;
		struct clk *clk_parent = NULL;

		p = clk_get_parent(clkp);
		if (p) {
			clk_parent = clk_lookup((clk_idx_t) p->clk);
		}

		if (clk_parent) {
			ret = clk_get(clk_parent);
		}

		if (ret) {
			ret = clk_set_state(clkp, STRUE);
			if (!ret && clk_parent) {
				pm_trace(TRACE_PM_ACTION_CLOCK_ENABLE |
					 TRACE_PM_ACTION_FAIL, clk_id(clkp));
				clk_put(clk_parent);
			} else {
				pm_trace(TRACE_PM_ACTION_CLOCK_ENABLE,
					 clk_id(clkp));
			}
		}
	}

	if (ret) {
		clkp->ref_count++;
	}

	return ret;
}

void clk_put(struct clk *clkp)
{
	if (--clkp->ref_count == 0) {
		const struct clk_parent *p;

		p = clk_get_parent(clkp);
		clk_set_state(clkp, SFALSE);
		pm_trace(TRACE_PM_ACTION_CLOCK_DISABLE, clk_id(clkp));
		if (p) {
			struct clk *clk_parent;
			clk_parent = clk_lookup((clk_idx_t) p->clk);
			if (clk_parent) {
				clk_put(clk_parent);
			}
		}
	}
}

/* FIXME: Stop propogation at PLL and notify PLL */
void clk_ssc_allow(struct clk *clkp)
{
	if (--clkp->ssc_block_count == 0) {
		const struct clk_parent *p;
		p = clk_get_parent(clkp);
		if (p) {
			struct clk *clk_parent;
			clk_parent = clk_lookup((clk_idx_t) p->clk);
			if (clk_parent) {
				clk_ssc_allow(clk_parent);
			}
		}
	}
}

void clk_ssc_block(struct clk *clkp)
{
	if (!clkp->ssc_block_count++) {
		const struct clk_parent *p;
		p = clk_get_parent(clkp);
		if (p) {
			struct clk *clk_parent;
			clk_parent = clk_lookup((clk_idx_t) p->clk);
			if (clk_parent) {
				clk_ssc_block(clk_parent);
			}
		}
	}
}

void clk_freq_change_allow(struct clk *clkp)
{
	clkp->freq_change_block_count--;
}

void clk_freq_change_block(struct clk *clkp)
{
	clkp->freq_change_block_count++;
}

static s32 clk_register_clock(struct clk *clkp, const struct clk_data *clk_data)
{
	s32 ret = SUCCESS;
	struct clk *clk_parent = NULL;
	const struct clk_parent *p;

	p = clk_get_parent(clkp);
	if (p) {
		clk_parent = clk_lookup((clk_idx_t) p->clk);
	}
	if ((clk_parent != NULL) && ((clk_parent->flags & CLK_FLAG_INITIALIZED) == 0U)) {
		ret = -EDEFER;
	}

	if ((ret == SUCCESS) && (clk_data->drv->init != NULL)) {
		ret = clk_data->drv->init(clkp);
	}

	if (ret == SUCCESS) {
		clkp->flags |= CLK_FLAG_INITIALIZED;
		if (clkp->ref_count != 0U) {
			if (!clk_set_state(clkp, STRUE)) {
				pm_trace(TRACE_PM_ACTION_CLOCK_ENABLE |
					 TRACE_PM_ACTION_FAIL, clk_id(clkp));
			} else {
				pm_trace(TRACE_PM_ACTION_CLOCK_ENABLE,
					 clk_id(clkp));
			}
		}
		if (clk_data->drv->get_state != NULL) {
			if (clk_data->drv->get_state(clkp) != CLK_HW_STATE_DISABLED) {
				clkp->flags |= CLK_FLAG_PWR_UP_EN;
			}
		}
	}

	return ret;
}

void clk_drop_pwr_up_en(void)
{
	clk_idx_t i;

	for (i = 0U; i < soc_clock_count; i++) {
		if (soc_clocks[i].flags & CLK_FLAG_PWR_UP_EN) {
			clk_put(soc_clocks + i);
			soc_clocks[i].flags &= ~CLK_FLAG_PWR_UP_EN;
		}
	}
}

s32 clk_deinit_pm_devgrp(u8 pm_devgrp)
{
	s32 ret = SUCCESS;
	u32 i;
	u32 clk_id_start;
	u32 clk_id_end;

	clk_id_start = soc_devgroups[pm_devgrp].clk_idx;

	if (pm_devgrp >= soc_devgroup_count) {
		return -EINVAL;
	} else if (pm_devgrp == soc_devgroup_count - 1) {
		/* Last devgrp's last clock id is the same as last of all clock ids */
		clk_id_end = soc_clock_count;
	} else {
		/* Chosen devgrp's last clock id is next devgrp's first clock id */
		clk_id_end = soc_devgroups[pm_devgrp + 1].clk_idx;
	}

	/*
	 * Loop through all the clocks in selected device group.
	 * First pass make sure any clock with the PWR_UP_EN bit set gets
	 * a matching put call and the flag cleared. Clocks can be in this
	 * state if initialization for the given domain is in the deferred state.
	 */
	for (i = clk_id_start; i < clk_id_end; i++) {
		struct clk *clkp = soc_clocks + i;

		/* Clear the power up flag */
		if ((clkp->flags & CLK_FLAG_PWR_UP_EN) != 0U) {
			clk_put(clkp);
			soc_clocks[i].flags &= ~CLK_FLAG_PWR_UP_EN;
		}
	}

	/*
	 * Second pass clear the initialized flag and check that the ref_count
	 * is zero as expected.
	 */
	for (i = clk_id_start; i < clk_id_end; i++) {
		struct clk *clkp = soc_clocks + i;

		/* Clear the initialized flag */
		clkp->flags &= ~CLK_FLAG_INITIALIZED;
	}

	return ret;
}


s32 clk_init(void)
{
	sbool progress;
	sbool contents;
	sbool enabled = STRUE;
	s32 ret = SUCCESS;
	u32 i;
	u32 clock_count = soc_clock_count;

	for (i = 0U; i < soc_devgroup_count; i++) {
		devgrp_t devgrp;

		/* Translate compressed internal representation to bitfield */
		if (i == PM_DEVGRP_DMSC) {
			devgrp = DEVGRP_DMSC;
		} else {
			devgrp = BIT(i - 1U);
		}

		/* First disabled devgroup, stop at this clock index */
		if (enabled && !pm_devgroup_is_enabled(devgrp)) {
			clock_count = soc_devgroups[i].clk_idx;
			enabled = SFALSE;
		}
	}

	contents = SFALSE;
	progress = SFALSE;

	/* Loop through all the clocks to initialize them */
	for (i = 0U; i < clock_count; i++) {
		struct clk *clkp = soc_clocks + i;
		const struct clk_data *clk_data = soc_clock_data + i;
		s32 curr;

		if (((clkp->flags & CLK_FLAG_INITIALIZED) == 0U) && (clk_data->drv != NULL)) {
			contents = STRUE;
			curr = clk_register_clock(clkp, clk_data);
			if (curr != -EDEFER) {
				progress = STRUE;
				if (curr != SUCCESS) {
					ret = curr;
				}
			}
		}
	}

	if (progress) {
		for (i = 0U; i < clock_count; i++) {
			if ((soc_clocks[i].flags & CLK_FLAG_PWR_UP_EN) != 0U) {
				/* FIXME: Error handling */
				clk_get(soc_clocks + i);
			}
		}
	} else if (contents) {
		/* We processed at least one clock but didn't make progress */
		ret = -EDEFER;
	} else {
		/* We didn't process any clocks */
		ret = SUCCESS;
	}

	return ret;
}
