/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <clk_div.h>
#include <clk_mux.h>
#include <lib/container_of.h>
#include <ilog.h>
#include <lib/ioremap.h>

u32 clk_get_div(struct clk *clkp)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_drv_div *divp;

	if (clk_data->type != CLK_TYPE_DIV) {
		return 1;
	}

	divp = container_of(clk_data->drv, const struct clk_drv_div, drv);
	return divp->get_div(clkp);
}

sbool clk_div_notify_freq(struct clk *clkp, u32 parent_freq_hz,
			  sbool query)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_data_div *data_div;
	const struct clk_drv_div *drv_div;
	u32 divp = clk_get_div(clkp);
	u32 i;
	sbool found = SFALSE;

	data_div = container_of(clk_data->data, const struct clk_data_div,
				data);
	drv_div = container_of(clk_data->drv, const struct clk_drv_div, drv);

	/* Just find a frequency that works for all children */

	/* Try the current divisor and lower frequencies */
	for (i = divp; !found && i < data_div->n + 1UL; i++) {
		if (!drv_div->valid_div || drv_div->valid_div(clkp, i)) {
			found = clk_notify_children_freq(clkp,
							 parent_freq_hz / i, STRUE);
		}
	}

	/* Try larger frequencies */
	for (i = divp - 1UL; !found && i > 0UL; i--) {
		if (!drv_div->valid_div || drv_div->valid_div(clkp, i)) {
			found = clk_notify_children_freq(clkp,
							 parent_freq_hz / i, STRUE);
		}
	}

	if (found && !query) {
		if (i > divp) {
			/* Frequency going down */
			drv_div->set_div(clkp, i);
		}
		clk_notify_children_freq(clkp, parent_freq_hz / i, SFALSE);
		if (i < divp) {
			/* Frequency going up */
			drv_div->set_div(clkp, i);
		}
	}

	return found;
}

static u32 clk_div_set_freq_dyn_parent(struct clk *clkp,
				       u32 target_hz, u32 min_hz, u32 max_hz,
				       sbool query, sbool *changed)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_parent *p = clk_get_parent(clkp);
	const struct clk_data_div *data_div;
	const struct clk_drv_div *drv_div;
	u32 old_div;
	u32 best_div = 0UL;
	u32 best_parent_freq = 0UL;
	u32 best_min_hz = 0UL;
	u32 best_max_hz = 0UL;
	u32 updated_min_hz = min_hz;
	u32 updated_max_hz = max_hz;
	sbool best_changed = SFALSE;
	u32 min_delta = UINT_MAX;
	u32 i;
	u32 ret;
	struct clk *parent = NULL;

	data_div = container_of(clk_data->data, const struct clk_data_div,
				data);
	drv_div = container_of(clk_data->drv, const struct clk_drv_div, drv);

	/* p and clk_lookup verified by caller */
	if (p != NULL) {
		parent = clk_lookup((clk_idx_t) p->clk);
	}

	old_div = drv_div->get_div(clkp);

	for (i = 1UL; (i <= data_div->n) && (p != NULL) && (min_delta != 0U); i++) {
		u32 new_target, new_min, new_max, new_parent_freq;
		u32 delta;
		u32 divider;
		sbool new_target_overflow;

		if (drv_div->valid_div && !drv_div->valid_div(clkp, i)) {
			continue;
		}

		divider = i * p->div;

		/* Make sure target fits within out clock frequency type */
		if (ULONG_MAX / divider < min_hz) {
			continue;
		}

		new_min = updated_min_hz * divider;
		new_target = target_hz * divider;
		new_max = updated_max_hz * divider;

		/* If an overflow occurs in min, we are outside the range */
		if (new_min < updated_min_hz) {
			break;
		}

		/* Cap overflow in target */
		if (new_target < target_hz) {
			if (best_div != 0UL) {
				/*
				 * Already found a working combination, don't
				 * bother with target overflows.
				 */
				break;
			}
			new_target = ULONG_MAX;
			new_target_overflow = STRUE;
		} else {
			new_target_overflow = SFALSE;
		}

		/* Cap overflow in max */
		if (new_max < updated_max_hz) {
			new_max = ULONG_MAX;
		}
		if (parent != NULL) {
			new_parent_freq = clk_set_freq(parent, new_target, new_min,
						       new_max, STRUE, changed);
		} else {
			new_parent_freq = 0U;
		}

		if (!new_parent_freq) {
			continue;
		}

		/* Check that any siblings can handle the new freq */
		if (*changed && !(clk_notify_sibling_freq(clkp, parent,
							  new_parent_freq,
							  STRUE))) {
			continue;
		}

		if (new_target_overflow) {
			u32 new_parent_freq_div;
			/*
			 * The target frequency was capped to ULONG_MAX, our
			 * delta will be slightly less accurate.
			 */
			new_parent_freq_div = new_parent_freq / divider;
			if (new_parent_freq_div > target_hz) {
				delta = new_parent_freq_div - target_hz;
			} else {
				delta = target_hz - new_parent_freq_div;
			}
		} else {
			if (new_parent_freq > new_target) {
				delta = new_parent_freq - new_target;
			} else {
				delta = new_target - new_parent_freq;
			}
			delta /= divider;
		}
		if (delta >= min_delta) {
			continue;
		}

		min_delta = delta;
		best_div = i;
		best_changed = *changed;
		best_parent_freq = new_parent_freq;
		best_min_hz = new_min;
		best_max_hz = new_max;

		/*
		 * Tighten min/max to decrease search space.
		 * Any new frequency must be an improvement by at least 1Hz.
		 * Note that we stop searching when min_delta reaches zero.
		 * Ensure that subtraction for min and addition for max do
		 * not overflow.
		 */
		if (min_delta != 0U) {
			u32 hz;

			hz = target_hz - (min_delta - 1U);
			if ((hz <= target_hz) && (updated_min_hz < hz)) {
				updated_min_hz = hz;
			}

			hz = target_hz + (min_delta - 1U);
			if ((hz >= target_hz) && (updated_max_hz > hz)) {
				updated_max_hz = hz;
			}
		}
	}

	if (best_div && !query) {
		/* Actually program out parents */
		if (best_changed) {
			clk_set_freq(parent, best_parent_freq, best_min_hz,
				     best_max_hz, SFALSE, changed);
		}

		/* Actually program our own register */
		if (old_div != best_div) {
			drv_div->set_div(clkp, best_div);
		}

		/* Assign new rate to siblings */
		if (best_changed) {
			clk_notify_sibling_freq(clkp, parent,
						best_parent_freq, SFALSE);
		}

		*changed = best_changed || old_div != best_div;
	}

	if (best_div) {
		ret = best_parent_freq / (best_div * p->div);
	} else {
		ret = 0UL;
	}

	return ret;
}

static u32 clk_div_set_freq_static_parent(
	struct clk	*clkp,
	u32		target_hz,
	u32		min_hz,
	u32		max_hz,
	sbool		query,
	sbool		*changed
	__attribute__((unused)))
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_data_div *data_div;
	const struct clk_drv_div *drv_div;
	u32 parent_freq_hz = clk_get_parent_freq(clkp);
	u32 div0, div1;
	sbool div0_ok, div1_ok;
	u32 div0_delta, div1_delta;
	u32 div0_hz, div1_hz;
	u32 n;

	/* Calculate 2 best potential frequencies */
	div0 = parent_freq_hz / target_hz;

	data_div = container_of(clk_data->data, const struct clk_data_div,
				data);
	drv_div = container_of(clk_data->drv, const struct clk_drv_div, drv);

	n = data_div->n;

	/*
	 * Prevent out-of-bounds divider value. Rest of the code in the
	 * function will check if the resulting divider value is within
	 * the allowable min/max range.
	 */
	if (div0 > n - 1) {
		div0 = n - 1;
	}

	div1 = div0 + 1UL;

	if (drv_div->valid_div) {
		for (; div0 > 0UL && !drv_div->valid_div(clkp, div0); div0--) {
			/* Step through loop until valid div is found */
		}

		for (; div1 <= n && !drv_div->valid_div(clkp, div1); div1++) {
			/* Step through loop until valid div is found */
		}
	}

	div0_ok = SFALSE;
	div0_hz = 0UL;
	if (div0 != 0UL) {
		div0_hz = parent_freq_hz / div0;
		/* Check for in range */
		if (div0_hz <= max_hz) {
			div0_ok = STRUE;
			div0_delta = div0_hz - target_hz;
		} else {
			div0_hz = 0UL;
		}
	}

	div1_ok = SFALSE;
	div1_hz = 0UL;
	if (div1 <= n) {
		div1_hz = parent_freq_hz / div1;
		if (div1_hz >= min_hz) {
			div1_ok = STRUE;
			div1_delta = target_hz - div1_hz;
		} else {
			div1_hz = 0UL;
		}
	}

	/* Make sure at least one of them is acceptable */
	if (div1_ok && (!div0_ok || div1_delta < div0_delta)) {
		div0_ok = STRUE;
		div0 = div1;
		div0_hz = div1_hz;
	}

	if (div0_ok && !query) {
		/* Actually program our own register */
		drv_div->set_div(clkp, div0);
	}

	return div0_hz;
}


u32 clk_div_set_freq(struct clk *clkp, u32 target_hz,
		     u32 min_hz, u32 max_hz,
		     sbool query, sbool *changed)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_parent *p = clk_get_parent(clkp);
	u32 ret = 0;

	*changed = SFALSE;

	if (!p || !clk_lookup((clk_idx_t) p->clk)) {
		/* Cannot function without parent */
	} else if (clk_data->flags & CLK_DATA_FLAG_MODIFY_PARENT_FREQ) {
		ret = clk_div_set_freq_dyn_parent(clkp, target_hz, min_hz,
						  max_hz, query, changed);
	} else {
		ret = clk_div_set_freq_static_parent(clkp, target_hz, min_hz,
						     max_hz, query, changed);
	}

	return ret;
}

u32 clk_div_get_freq(struct clk *clkp)
{
	u32 parent_freq_hz = clk_get_parent_freq(clkp);

	return parent_freq_hz / clk_get_div(clkp);
}

s32 clk_div_init(struct clk *clkp)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_data_div *data_div;
	const struct clk_drv_div *drv_div;
	s32 ret = SUCCESS;

	data_div = container_of(clk_data->data, const struct clk_data_div,
				data);
	drv_div = container_of(clk_data->drv, const struct clk_drv_div, drv);

	if (data_div->default_div && drv_div->set_div) {
		if (!drv_div->set_div(clkp, data_div->default_div)) {
			ret = -EINVAL;
		}
	}

	return ret;
}

u32 clk_div_reg_get_div(struct clk *clkp)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_data_div *data_div;
	const struct clk_data_div_reg *data_reg;
	u32 v;

	data_div = container_of(clk_data->data, const struct clk_data_div,
				data);
	data_reg = container_of(data_div, const struct clk_data_div_reg,
				data_div);

	/*
	 * Hack, temporarily return parent 0 for muxes without register
	 * assignments.
	 */
	if (data_reg->reg == 0) {
		v = 1;
	} else {
		u32 n = data_div->n;
		if (!data_reg->start_at_1) {
			n -= 1;
		}
		v = readl(data_reg->reg) >> data_reg->bit;
		v &= (1 << ilog32(n)) - 1;
		if (!data_reg->start_at_1) {
			v += 1;
		}
	}

	return v;
}

sbool clk_div_reg_set_div(struct clk *clkp, u32 d)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_data_div *data_div;
	const struct clk_data_div_reg *data_reg;
	const struct clk_drv_div *drv_div;
	sbool ret = SFALSE;
	u32 n;
	s32 err;

	data_div = container_of(clk_data->data, const struct clk_data_div,
				data);
	data_reg = container_of(data_div, const struct clk_data_div_reg,
				data_div);
	drv_div = container_of(clk_data->drv, const struct clk_drv_div, drv);

	n = data_div->n;
	if (d <= n && (!drv_div->valid_div || drv_div->valid_div(clkp, d))) {
		u32 v;

		if (!data_reg->start_at_1) {
			d -= 1UL;
			n -= 1UL;
		}

		v = readl(data_reg->reg);
		v &= ~(((1UL << ilog32(n)) - 1UL) << data_reg->bit);
		v |= d << data_reg->bit;
		err = pm_writel_verified(v, (u32) data_reg->reg);
		if (err == SUCCESS) {
			ret = STRUE;
		}
	}

	return ret;
}

const struct clk_drv_div clk_drv_div_reg_ro = {
	.drv			= {
		.get_freq	= clk_div_get_freq,
	},
	.get_div		= clk_div_reg_get_div,
};

const struct clk_drv_div clk_drv_div_reg = {
	.drv			= {
		.notify_freq	= clk_div_notify_freq,
		.set_freq	= clk_div_set_freq,
		.get_freq	= clk_div_get_freq,
		.init		= clk_div_init,
	},
	.set_div		= clk_div_reg_set_div,
	.get_div		= clk_div_reg_get_div,
};

u32 clk_div_reg_go_get_div(struct clk *clkp)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_data_div *data_div;
	const struct clk_data_div_reg_go *data_reg;
	u32 v;

	data_div = container_of(clk_data->data, const struct clk_data_div,
				data);
	data_reg = container_of(data_div, const struct clk_data_div_reg_go,
				data_div);

	/*
	 * Hack, temporarily return parent 0 for muxes without register
	 * assignments.
	 */
	if (data_reg->reg == 0) {
		v = 1;
	} else {
		u32 n = data_div->n;
		if (!data_reg->start_at_1) {
			n -= 1;
		}
		v = readl(data_reg->reg) >> data_reg->bit;
		v &= (1 << ilog32(n)) - 1;
		v += 1;
	}

	return v;
}

sbool clk_div_reg_go_set_div(struct clk *clkp, u32 d)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_data_div *data_div;
	const struct clk_data_div_reg_go *data_reg;
	const struct clk_drv_div *drv_div;
	sbool ret = SFALSE;
	u32 n;
	s32 err;

	data_div = container_of(clk_data->data, const struct clk_data_div,
				data);
	data_reg = container_of(data_div, const struct clk_data_div_reg_go,
				data_div);
	drv_div = container_of(clk_data->drv, const struct clk_drv_div, drv);

	n = data_div->n;
	if (d <= n && (!drv_div->valid_div || drv_div->valid_div(clkp, d))) {
		u32 v;

		if (!data_reg->start_at_1) {
			d -= 1;
			n -= 1;
		}

		v = readl(data_reg->reg);
		v &= ~(((1 << ilog32(n)) - 1) << data_reg->bit);
		v &= ~BIT(data_reg->go);
		v |= d << data_reg->bit;
		err = pm_writel_verified(v, data_reg->reg);
		if (err == SUCCESS) {
			ret = STRUE;

			/* Go bit registers typically do not read back */
			v |= BIT(data_reg->go);
			writel(v, (u32) data_reg->reg);
			v &= ~BIT(data_reg->go);
			writel(v, (u32) data_reg->reg);
		}
	}

	return ret;
}

const struct clk_drv_div clk_drv_div_reg_go = {
	.drv			= {
		.notify_freq	= clk_div_notify_freq,
		.set_freq	= clk_div_set_freq,
		.get_freq	= clk_div_get_freq,
		.init		= clk_div_init,
	},
	.set_div		= clk_div_reg_go_set_div,
	.get_div		= clk_div_reg_go_get_div,
};

static u32 clk_div_fixed_get_div(struct clk *clkp)
{
	const struct clk_data *clk_data = clk_get_data(clkp);
	const struct clk_data_div *data_div;

	data_div = container_of(clk_data->data, const struct clk_data_div,
				data);
	return data_div->n;
}

const struct clk_drv_div clk_drv_div_fixed = {
	.drv			= {
		.get_freq	= clk_div_get_freq,
	},
	.get_div		= clk_div_fixed_get_div,
};
