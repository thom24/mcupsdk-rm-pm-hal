/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <psc.h>
#include <stddef.h>
#include <lib/container_of.h>
#include <types/errno.h>
#include <types/array_size.h>
#include <lib/ioremap.h>
#include <lib/io.h>
#include <types/short_types.h>
#include <list.h>
#include <lib/trace.h>
#include <device.h>
#include <device_pm.h>
#include <resource.h>
#include <clk.h>
#include <pm_types.h>
#include <osal/osal_clock.h>
#include <config.h>

#define PSC_PID                 0x000
#define PSC_GBLCTL              0x010
#define PSC_GBLSTAT             0x014
#define PSC_INTEVAL             0x018
#define PSC_IPWKCNT             0x01c
#define PSC_MERRPR0             0x040
#define PSC_MERRPR1             0x044
#define PSC_MERRCR0             0x050
#define PSC_MERRCR1             0x054
#define PSC_PERRPR              0x060
#define PSC_PERRCR              0x068
#define PSC_EPCPR               0x070
#define PSC_EPCRR               0x078
#define PSC_RAILSTAT            0x100
#define PSC_RAILCTL             0x104
#define PSC_RAILSET             0x108
#define PSC_PTCMD               0x120
#define PSC_PTSTAT              0x128
#define PSC_PDSTAT(domain)      (0x200 + 4 * (domain))
#define PSC_PDCTL(domain)       (0x300 + 4 * (domain))
#define PSC_PDCFG(domain)       (0x400 + 4 * (domain))
#define PSC_MDCFG(id)           (0x600 + 4 * (id))
#define PSC_MDSTAT(id)          (0x800 + 4 * (id))
#define PSC_MDCTL(id)           (0xa00 + 4 * (id))

#define MDSTAT_STATE_MASK               0x3f
#define MDSTAT_BUSY_MASK                0x30
#define MDSTAT_STATE_SWRSTDISABLE       0x00
#define MDSTAT_STATE_SYNCRST            0x01
#define MDSTAT_STATE_DISABLE            0x02
#define MDSTAT_STATE_ENABLE             0x03
#define MDSTAT_STATE_AUTO_SLEEP         0x04
#define MDSTAT_STATE_AUTO_WAKE          0x05
#define MDSTAT_STATE_DISABLE_CLK_ON     0x21
#define MDSTAT_STATE_DISABLE_IN_PROG    0x22
#define MDSTAT_STATE_RETRY_DISABLE      0x23
#define MDSTAT_STATE_ENABLE_IN_PROG     0x24
#define MDSTAT_STATE_SLEEP_IN_PROG      0x25
#define MDSTAT_STATE_CLK_ON1            0x26
#define MDSTAT_STATE_CLK_OFF1           0x27
#define MDSTAT_STATE_CLK_ON2            0x28
#define MDSTAT_STATE_CLK_OFF2           0x29
#define MDSTAT_STATE_CLK_ON3            0x2a
#define MDSTAT_STATE_CLK_OFF3           0x2b

#define MDSTAT_EMUIHB           BIT(17) /* EMU alters module state */
#define MDSTAT_EMURST           BIT(16) /* EMU alters reset to module */
#define MDSTAT_MCKOUT           BIT(12) /* Module clock output status */
#define MDSTAT_MRSTDONE         BIT(11) /* Module reset done */
#define MDSTAT_MRST             BIT(10) /* Module reset deasserted */
#define MDSTAT_LRSTDONE         BIT(9)  /* Local reset done */
#define MDSTAT_LRST             BIT(8)  /* Local reset deasserted */

#define MDCTL_FORCE             BIT(31)
#define MDCTL_RESET_ISO         BIT(12)         /* Enable reset isolation */
#define MDCTL_EMUIHBIE          BIT(10)         /* EMU alters module IE */
#define MDCTL_EMURSTIE          BIT(9)          /* EMU alter reset IE */
#define MDCTL_LRST              BIT(8)          /* Assert local reset when 0 */

#define PDSTAT_EMUIHB                   BIT(11) /* EMU alters domain state */
#define PDSTAT_PWRBAD                   BIT(10) /* Power bad error */
#define PDSTAT_PORDONE                  BIT(9)  /* Power on reset done */
#define PDSTAT_POR                      BIT(8)  /* Power on reset deasserted */
#define PDSTAT_STATE_MASK               0x1f
#define PDSTAT_STATE_OFF                0x00
#define PDSTAT_STATE_ON                 0x01
#define PDSTAT_STATE_ON_ARB             0x10
#define PDSTAT_STATE_SWITCH_ON          0x11
#define PDSTAT_STATE_ON_RAIL_CNT        0x12
#define PDSTAT_STATE_WAIT_ALL_SYNC_RST  0x13
#define PDSTAT_STATE_STRETCH_POR        0x14
#define PDSTAT_STATE_WAIT_POR_DONE      0x15
#define PDSTAT_STATE_COUNT16            0x16
#define PDSTAT_STATE_WAIT_ALL_SWRST_DIS 0x17
#define PDSTAT_STATE_OFF_ARB            0x18
#define PDSTAT_STATE_SWITCH_OFF         0x19
#define PDSTAT_STATE_OFF_RAIL_CNT       0x1a

#define PDCTL_STATE_MASK        BIT(0)
#define PDCTL_STATE_OFF         0
#define PDCTL_STATE_ON          1
#define PDCTL_EPCGOOD           BIT(8)  /* Externel power control on */
#define PDCTL_EMUIHBIE          BIT(9)  /* EMU alters domain state IE */
#define PDCTL_FORCE             BIT(31)

#define PSC_TRANSITION_TIMEOUT  10000

/* Enable PTSTAT errata only for J721E and AM65x PG 1.0 */
#if defined(CONFIG_SOC_J721E) || defined(CONFIG_SOC_AM6)
#define PSC_PTSTAT_ERRATA_ENABLE
#endif

/* Extra delay time between powerdomain off and on in nanoseconds */
#define PSC_PTSTAT_ERRATA_DELAY_NS 10000

static struct device *psc_devs;

static void lpsc_module_get_internal(struct device *dev, struct lpsc_module *module, sbool use, sbool ret);
static void lpsc_module_put_internal(struct device *dev, struct lpsc_module *module, sbool use, sbool ret);

#ifdef PSC_PTSTAT_ERRATA_ENABLE
/* Timestamp of last powerdomain poweroff for use in PTSTAT errata check */
static u64 psc_last_pd_off_ns;
#endif

static u32 psc_read(struct device *dev, u32 reg)
{
	const struct resource_mem *mem = device_resource_mem(dev, 0U);
	u32 ret = 0U;

	if (mem != NULL) {
		ret = mem_readl(mem, reg);
	}

	return ret;
}

static void psc_write(struct device *dev, u32 val, u32 reg)
{
	const struct resource_mem *mem = device_resource_mem(dev, 0U);

	if (mem != NULL) {
		mem_writel(mem, val, reg);
	}
}

pd_idx_t psc_pd_idx(struct device *dev, struct psc_pd *pd)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));

	return pd - psc->powerdomains;
}

static inline struct psc_pd *psc_idx2pd(const struct psc_drv_data	*psc,
					pd_idx_t			id)
{
	return psc->powerdomains + id;
}

static const struct psc_pd_data *psc_pd_data(struct device	*dev,
					     struct psc_pd	*pd)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));

	return psc->pd_data + psc_pd_idx(dev, pd);
}

lpsc_idx_t lpsc_module_idx(struct device *dev, struct lpsc_module *module)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));

	return module - psc->modules;
}

static inline struct lpsc_module *psc_idx2mod(const struct psc_drv_data *psc,
					      lpsc_idx_t		id)
{
	return psc->modules + id;
}

/* FIXME: Timeout behavior */
void psc_pd_wait(struct device *dev, struct psc_pd *pd)
{
	if (!(psc_pd_data(dev, pd)->flags & PSC_PD_ALWAYSON)) {
		s32 i = PSC_TRANSITION_TIMEOUT;
		while ((psc_read(dev, PSC_PTSTAT) &
			BIT(psc_pd_idx(dev, pd))) && --i) {
		}
		if (!i) {
			/* Directly convert to psc to get psc_idx */
			pm_trace(TRACE_PM_ACTION_PSC_TRANSITION_TIMEOUT | TRACE_PM_ACTION_FAIL,
				 (((to_psc_drv_data(get_drv_data(dev)))->psc_idx) << TRACE_PM_VAL_PSC_SHIFT) |
				 (psc_pd_idx(dev, pd) << TRACE_PM_VAL_PD_SHIFT) | TRACE_PM_VAL_PD_POS1);
		}
	}
}

static void pd_initiate(struct device *dev, struct psc_pd *pd)
{
	/* Note: This is a state machine reg */
	psc_write(dev, BIT(psc_pd_idx(dev, pd)), PSC_PTCMD);
}

void psc_pd_get(struct device *dev, struct psc_pd *pd)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 idx = psc_pd_idx(dev, pd);
	u32 pdctl;
	u32 i;

	pm_trace(TRACE_PM_ACTION_PD_GET,
		 (psc->psc_idx << TRACE_PM_VAL_PSC_SHIFT) |
		 (idx << TRACE_PM_VAL_PD_SHIFT) |
		 (pd->use_count & TRACE_PM_VAL_MAX_PSC_DATA));

	if (pd->use_count++) {
		return;
	}

	if (psc->pd_data[idx].flags & PSC_PD_ALWAYSON) {
		return;
	}

	/* Verify any previous transitions have completed */
	psc_pd_wait(dev, pd);

	if (psc->pd_data[idx].flags & PSC_PD_DEPENDS) {
		psc_pd_get(dev, psc_idx2pd(psc,
					   (pd_idx_t) psc->pd_data[idx].depends));
	}

	for (i = 0UL; i < ARRAY_SIZE(psc->pd_data[idx].clock_dep); i++) {
		struct clk *clk = clk_lookup(psc->pd_data[idx].clock_dep[i]);
		if (clk != NULL) {
			clk_get(clk);
		}
	}

	pdctl = psc_read(dev, PSC_PDCTL(idx));

	if ((pdctl & PDCTL_STATE_MASK) != PDCTL_STATE_ON) {
		/* Avoid redundant power-up transitions */
		pdctl &= ~PDCTL_STATE_MASK;
		pdctl |= PDCTL_STATE_ON;

#ifdef PSC_PTSTAT_ERRATA_ENABLE
		/*
		 * Handle PTSTAT errata.
		 *
		 * We need to delay an extra 10uS before turning on a power
		 * domain after turning off that power domain. Note that in
		 * order to conserve memory, we only store one time stamp
		 * rather than a time stamp per powerdomain.
		 */
		if (psc_last_pd_off_ns != 0ULL) {
			u64 delta_ns;
			/*
			 * Calculate how long it's been since the last time
			 * we turned off a powerdomain.
			 * osal_timestamp64 returns a nanosecond timestamp
			 */
			delta_ns = osal_timestamp64() - psc_last_pd_off_ns;
			if (delta_ns < ((u64) PSC_PTSTAT_ERRATA_DELAY_NS)) {
				u32 delay_us;
				/*
				 * Calculate the delay we need to complete
				 * the wait period. The osal_delay argument
				 * is in microseconds. In the calculation we
				 * convert to microseconds and use the
				 * ceiling value to ensure we wait the
				 * minimum required time.
				 */
				delay_us = (PSC_PTSTAT_ERRATA_DELAY_NS - ((u32) delta_ns) + 999UL) / 1000UL;
				osal_delay(delay_us);
			}
			/*
			 * Reset the timer so we can avoid bothering with
			 * unnecessary osal_timestamp64 calls and comparisons.
			 */
			psc_last_pd_off_ns = 0ULL;
		}
#endif


		/* Note: This is a state machine reg */
		psc_write(dev, pdctl, PSC_PDCTL(idx));

		pd_initiate(dev, pd);
		psc_pd_wait(dev, pd);
	}

	psc->data->pds_enabled |= BIT(idx);
}

void psc_pd_put(struct device *dev, struct psc_pd *pd)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 idx = psc_pd_idx(dev, pd);
	u32 pdctl;
	u32 i;

	pm_trace(TRACE_PM_ACTION_PD_PUT,
		 (psc->psc_idx << TRACE_PM_VAL_PSC_SHIFT) |
		 (idx << TRACE_PM_VAL_PD_SHIFT) |
		 (pd->use_count & TRACE_PM_VAL_MAX_PSC_DATA));

	if (--pd->use_count) {
		return;
	}

	if (psc->pd_data[idx].flags & PSC_PD_ALWAYSON) {
		return;
	}

	/* Verify any previous transitions have completed */
	psc_pd_wait(dev, pd);

	pdctl = psc_read(dev, PSC_PDCTL(idx));
	if ((pdctl & PDCTL_STATE_MASK) != PDCTL_STATE_OFF) {
		/* Avoid redundant power-up transitions */
		pdctl &= ~PDCTL_STATE_MASK;
		pdctl |= PDCTL_STATE_OFF;
		/* Note: This is a state machine reg */
		psc_write(dev, pdctl, PSC_PDCTL(idx));

		pd_initiate(dev, pd);
		psc_pd_wait(dev, pd);

#ifdef PSC_PTSTAT_ERRATA_ENABLE
		/*
		 * Store the last powerdomain poweroff time for use in the
		 * PTSTAT errata check.
		 */
		psc_last_pd_off_ns = osal_timestamp64();
#endif
	}

	for (i = 0UL; i < ARRAY_SIZE(psc->pd_data[idx].clock_dep); i++) {
		struct clk *clk = clk_lookup(psc->pd_data[idx].clock_dep[i]);
		if (clk != NULL) {
			clk_put(clk);
		}
	}

	if (psc->pd_data[idx].flags & PSC_PD_DEPENDS) {
		psc_pd_put(dev, psc_idx2pd(psc,
					   (pd_idx_t) psc->pd_data[idx].depends));
	}

	psc->data->pds_enabled &= ~BIT(idx);
}

u32 psc_pd_get_state(struct device *dev, struct psc_pd *pd)
{
	u32 idx = psc_pd_idx(dev, pd);
	u8 state;

	if (psc_read(dev, PSC_PTSTAT) & BIT(idx)) {
		return 2;
	}

	state = psc_read(dev, PSC_PDSTAT(idx)) & PDSTAT_STATE_MASK;
	return state == PDCTL_STATE_ON ? 1 : 0;
}

static void lpsc_module_notify_suspend(struct device		*dev,
				       struct lpsc_module	*mod)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 i;
	u32 idx = lpsc_module_idx(dev, mod);
	const struct lpsc_module_data *data = psc->mod_data + idx;
	struct device *sub_dev;

	/*
	 * All our devices are going into reset/losing power, notify them so
	 * they can call their suspend functions.
	 *
	 * FIXME: Block transition if suspend fails
	 */
	if (data->flags & LPSC_DEVICES_LIST) {
		for (i = 0UL; data->dev_list[i] != DEV_ID_NONE; i++) {
			sub_dev = device_lookup(data->dev_list[i]);
			if (sub_dev != NULL) {
				device_suspend(sub_dev);
			}
		}
	} else {
		for (i = 0UL; i < ARRAY_SIZE(data->dev_array) &&
		     data->dev_array[i] != DEV_ID_NONE; i++) {
			sub_dev = device_lookup(data->dev_array[i]);
			if (sub_dev != NULL) {
				device_suspend(sub_dev);
			}
		}
	}


	psc->data->mods_enabled[idx / 32UL] |= BIT(idx % 32UL);
}

static void lpsc_module_notify_resume(struct device		*dev,
				      struct lpsc_module	*module)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 idx = lpsc_module_idx(dev, module);

	/* No resume functionality yet required */

	psc->data->mods_enabled[idx / 32UL] &= ~BIT(idx % 32UL);
}

static void lpsc_module_sync_state(struct device	*dev,
				   struct lpsc_module	*module)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 mdctl;
	u32 idx = lpsc_module_idx(dev, module);
	const struct lpsc_module_data *data = psc->mod_data + idx;
	struct psc_pd *pd = psc_idx2pd(psc, (pd_idx_t) data->powerdomain);
	u8 state;
	u8 old_state;
	sbool transition;
	sbool get_en;
	sbool get_ret;
	sbool put_en;
	sbool put_ret;

	if (!module->use_count && !module->ret_count &&
	    !(data->flags & LPSC_NO_MODULE_RESET)) {
		/*
		 * A module reset is how we transition to power off. We block
		 * module reset if the module is in use, retention is required
		 * or reset is not allowed for the module.
		 *
		 * FIXME: Put module in DISABLE state if possible, delaying
		 * transition to SWRSTDISABLE until power domain is ready to
		 * transition to reduce unnecessary context loss.
		 */

		state = MDSTAT_STATE_SWRSTDISABLE;
	} else if (module->use_count || (data->flags & LPSC_NO_CLOCK_GATING)) {
		/*
		 * Fully enable the module if it is in use or if clock gating
		 * is not supported by this module.
		 */
		state = MDSTAT_STATE_ENABLE;
	} else {
		/*
		 * Only reached if module is not in use, retention is required,
		 * and clock gating is supported by the module.
		 */
		state = MDSTAT_STATE_DISABLE;
	}

	old_state = module->sw_state;
	if (old_state == state) {
		return;
	}

	module->sw_state = state;

	/* Notify of loss of functionality transitions before we do them */
	if (state == MDSTAT_STATE_SWRSTDISABLE) {
		lpsc_module_notify_suspend(dev, module);
	} else if (state == MDSTAT_STATE_DISABLE &&
		   old_state == MDSTAT_STATE_ENABLE) {
		lpsc_module_notify_suspend(dev, module);
	}

	get_en = SFALSE;
	get_ret = SFALSE;
	if (state == MDSTAT_STATE_ENABLE) {
		get_en = STRUE;
		if (old_state != MDSTAT_STATE_DISABLE) {
			get_ret = STRUE;
		}
	} else if (state == MDSTAT_STATE_DISABLE) {
		if (old_state != MDSTAT_STATE_ENABLE) {
			get_ret = STRUE;
		}
	}

	if ((get_en || get_ret) && (data->flags & LPSC_DEPENDS) != 0UL) {
		const struct psc_drv_data *depends_psc = psc;
		struct device *depends_dev = dev;
		if (data->depends_psc_idx != psc->psc_idx) {
			depends_dev = psc_lookup((psc_idx_t) data->depends_psc_idx);
			depends_psc = to_psc_drv_data(get_drv_data(depends_dev));
		}
		if (!depends_dev) {
			pm_trace(TRACE_PM_ACTION_PSC_INVALID_DEP_DATA | TRACE_PM_ACTION_FAIL,
				 (psc->psc_idx << TRACE_PM_VAL_PSC_SHIFT) |
				 (data->depends_psc_idx << TRACE_PM_VAL_PD_SHIFT) | TRACE_PM_VAL_PD_POS1);
		} else {
			/*
			 * Moving from dis/off to en/dis, bump ref count on
			 * dep.
			 */
			lpsc_module_get_internal(depends_dev,
						 psc_idx2mod(depends_psc, data->depends),
						 get_en, get_ret);
		}
	}

	if (old_state == MDSTAT_STATE_SWRSTDISABLE) {
		/*
		 * Coming out of reset, bump the context loss count and make
		 * sure pd is on.
		 */
		module->loss_count++;
		psc_pd_get(dev, pd);
	}

	mdctl = psc_read(dev, PSC_MDCTL(idx));
	transition = (mdctl & MDSTAT_STATE_MASK) != state;
	if (transition) {
		mdctl &= ~MDSTAT_STATE_MASK;
		mdctl |= (u32) state;
		/* Note: This is a state machine reg */
		psc_write(dev, mdctl, PSC_MDCTL(idx));
	}

	if (state == MDSTAT_STATE_SWRSTDISABLE) {
		/* Module is ready for power down, drop ref count on pd */
		psc_pd_put(dev, pd);
		if (pd->use_count != 0U && transition) {
			/*
			 * If psc_pd_put has a use count of zero, it already
			 * initaited the transition, otherwise we need to
			 * do the transition ourselves.
			 */
			pd_initiate(dev, pd);
		}
	} else if (transition) {
		/*
		 * Initiate transition
		 * FIXME: defer (for coalescing) if wait not requested
		 */
		pd_initiate(dev, pd);
	}

	/* Notify of gain of functionality transitions after we do them */
	if (state == MDSTAT_STATE_ENABLE) {
		lpsc_module_notify_resume(dev, module);
	} else if (state == MDSTAT_STATE_DISABLE &&
		   old_state == MDSTAT_STATE_SWRSTDISABLE) {
		lpsc_module_notify_resume(dev, module);
	}

	put_en = SFALSE;
	put_ret = SFALSE;
	if (state == MDSTAT_STATE_SWRSTDISABLE) {
		put_ret = STRUE;
		if (old_state == MDSTAT_STATE_ENABLE) {
			put_en = STRUE;
		}
	} else if (state == MDSTAT_STATE_DISABLE) {
		/*
		 * If moving from MDSTAT_STATE_SWRSTDISABLE to MDSTAT_STATE_DISABLE
		 * do not put dependency, as get is not called for dependency in
		 * this scenario.
		 */
		if (old_state == MDSTAT_STATE_ENABLE) {
			put_en = STRUE;
		}
	}

	if ((put_en || put_ret) && (data->flags & LPSC_DEPENDS) != 0UL) {
		const struct psc_drv_data *depends_psc = psc;
		struct device *depends_dev = dev;
		if (data->depends_psc_idx != psc->psc_idx) {
			depends_dev = psc_lookup((psc_idx_t) data->depends_psc_idx);
			depends_psc = to_psc_drv_data(get_drv_data(depends_dev));
		}
		if (!depends_dev) {
			pm_trace(TRACE_PM_ACTION_PSC_INVALID_DEP_DATA | TRACE_PM_ACTION_FAIL,
				 (psc->psc_idx << TRACE_PM_VAL_PSC_SHIFT) |
				 (data->depends_psc_idx << TRACE_PM_VAL_PD_SHIFT) | TRACE_PM_VAL_PD_POS2);
		} else {
			/*
			 * Moving from enable/dis to off/dis, drop ref count on
			 * dep
			 */
			lpsc_module_put_internal(depends_dev,
						 psc_idx2mod(depends_psc, data->depends),
						 put_en, put_ret);
		}
	}
}

u32 lpsc_module_get_state(struct device		*dev,
			  struct lpsc_module	*module)
{
	u32 idx = lpsc_module_idx(dev, module);

	switch (psc_read(dev, PSC_MDSTAT(idx)) & MDSTAT_STATE_MASK) {
	case MDSTAT_STATE_SWRSTDISABLE:
		return 0;
	case MDSTAT_STATE_DISABLE:
	case MDSTAT_STATE_ENABLE:
		return 1;
	default:
		return 2;
	}
}

/*
 * FIXME: Block context loss count increments if applicable when reset
 * iso is enabled.
 */
void lpsc_module_set_reset_iso(struct device *dev, struct lpsc_module *module,
			       sbool enable)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 idx = lpsc_module_idx(dev, module);
	const struct lpsc_module_data *data = psc->mod_data + idx;
	sbool is_enabled;
	u32 mdctl;

	if (!(data->flags & LPSC_HAS_RESET_ISO)) {
		return;
	}

	mdctl = psc_read(dev, PSC_MDCTL(idx));
	is_enabled = !!(mdctl & MDCTL_RESET_ISO);

	if (enable != is_enabled) {
		if (enable) {
			mdctl |= MDCTL_RESET_ISO;
		} else {
			mdctl &= ~MDCTL_RESET_ISO;
		}
		/* Note: This is a state machine reg */
		psc_write(dev, mdctl, PSC_MDCTL(idx));
	}
}

sbool lpsc_module_get_reset_iso(struct device *dev, struct lpsc_module *module)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 idx = lpsc_module_idx(dev, module);
	const struct lpsc_module_data *data = psc->mod_data + idx;

	if (!(data->flags & LPSC_HAS_RESET_ISO)) {
		return SFALSE;
	}

	return !!(psc_read(dev, PSC_MDCTL(idx)) & MDCTL_RESET_ISO);
}

/* Does not bump context loss count */
void lpsc_module_set_local_reset(struct device *dev,
				 struct lpsc_module *module, sbool enable)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 idx = lpsc_module_idx(dev, module);
	const struct lpsc_module_data *data = psc->mod_data + idx;
	sbool is_enabled;
	u32 mdctl;

	if (!(data->flags & LPSC_HAS_LOCAL_RESET)) {
		return;
	}

	mdctl = psc_read(dev, (u32) PSC_MDCTL(idx));
	is_enabled = !(mdctl & MDCTL_LRST);

	if (enable != is_enabled) {
		pm_trace(TRACE_PM_ACTION_SET_LOCAL_RESET,
			 (psc->psc_idx << TRACE_PM_VAL_PSC_SHIFT) |
			 (idx << TRACE_PM_VAL_PD_SHIFT) |
			 enable);

		if (enable) {
			mdctl &= ~MDCTL_LRST;
		} else {
			mdctl |= MDCTL_LRST;
		}

		/* Note: This is a state machine reg */
		psc_write(dev, mdctl, PSC_MDCTL(idx));
	}
}

sbool lpsc_module_get_local_reset(struct device *dev, struct lpsc_module *module)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 idx = lpsc_module_idx(dev, module);
	const struct lpsc_module_data *data = psc->mod_data + idx;

	if (!(data->flags & LPSC_HAS_LOCAL_RESET)) {
		return SFALSE;
	}

	return !(psc_read(dev, (u32) (PSC_MDCTL(idx)) & MDCTL_LRST));
}

void lpsc_module_wait(struct device *dev, struct lpsc_module *module)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 idx = lpsc_module_idx(dev, module);
	const struct lpsc_module_data *data = psc->mod_data + idx;
	struct psc_pd *pd = psc_idx2pd(psc, (pd_idx_t) data->powerdomain);

	s32 i = PSC_TRANSITION_TIMEOUT;

	psc_pd_wait(dev, pd);

	while ((psc_read(dev, PSC_MDSTAT(idx)) & MDSTAT_BUSY_MASK) && --i) {
	}
	if (!i) {
		pm_trace(TRACE_PM_ACTION_PSC_TRANSITION_TIMEOUT | TRACE_PM_ACTION_FAIL,
			 ((psc->psc_idx) << TRACE_PM_VAL_PSC_SHIFT) |
			 (idx << TRACE_PM_VAL_PD_SHIFT) | TRACE_PM_VAL_PD_POS2);
	}

	/* Only wait for reset to complete if module is in use */
	if (module->use_count) {
		u32 mask = MDSTAT_MRSTDONE;
		i = PSC_TRANSITION_TIMEOUT;

		if (!lpsc_module_get_local_reset(dev, module)) {
			mask |= MDSTAT_LRSTDONE;
		}
		while (!(psc_read(dev, PSC_MDSTAT(idx)) & mask) && --i) {
		}
		if (!i) {
			pm_trace(TRACE_PM_ACTION_PSC_RST_DONE_TIMEOUT | TRACE_PM_ACTION_FAIL,
				 ((psc->psc_idx) << TRACE_PM_VAL_PSC_SHIFT) |
				 (idx << TRACE_PM_VAL_PD_SHIFT) | TRACE_PM_VAL_PD_POS1);
		}
	}
}

static void lpsc_module_clk_get(struct device *dev, struct lpsc_module *mod)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 idx = lpsc_module_idx(dev, mod);
	const struct lpsc_module_data *data = psc->mod_data + idx;
	u32 i;

	for (i = 0UL; i < ARRAY_SIZE(data->clock_dep); i++) {
		struct clk *clk = clk_lookup(data->clock_dep[i]);
		if (clk != NULL) {
			clk_get(clk);
		}
	}
}

static void lpsc_module_clk_put(struct device *dev, struct lpsc_module *mod)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 idx = lpsc_module_idx(dev, mod);
	const struct lpsc_module_data *data = psc->mod_data + idx;
	sbool wait = SFALSE;
	u32 i;

	for (i = 0UL; i < ARRAY_SIZE(data->clock_dep); i++) {
		struct clk *clk = clk_lookup(data->clock_dep[i]);
		if (clk != NULL) {
			/*
			 * We have to wait for the transition to complete
			 * taking a clock away.
			 */
			if (!wait) {
				lpsc_module_wait(dev, mod);
				wait = STRUE;
			}
			clk_put(clk);
		}
	}
}

static void lpsc_module_get_internal(struct device *dev,
				     struct lpsc_module *module, sbool use, sbool ret)
{
#ifdef CONFIG_TRACE
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
#endif
	sbool modify = SFALSE;

	if (use) {
		pm_trace(TRACE_PM_ACTION_MODULE_GET,
			 (psc->psc_idx << TRACE_PM_VAL_PSC_SHIFT) |
			 (lpsc_module_idx(dev, module) << TRACE_PM_VAL_LPSC_SHIFT) |
			 (module->use_count & TRACE_PM_VAL_MAX_PSC_DATA));
		module->use_count++;
		if (module->use_count == 1U) {
			lpsc_module_clk_get(dev, module);
			modify = STRUE;
		}
	}

	if (ret) {
		pm_trace(TRACE_PM_ACTION_RETENTION_GET,
			 (psc->psc_idx << TRACE_PM_VAL_PSC_SHIFT) |
			 (lpsc_module_idx(dev, module) << TRACE_PM_VAL_LPSC_SHIFT) |
			 (module->ret_count & TRACE_PM_VAL_MAX_PSC_DATA));
		module->ret_count++;
		if (module->ret_count == 1U) {
			lpsc_module_clk_get(dev, module);
			modify = STRUE;
		}
	}

	if (modify) {
		lpsc_module_sync_state(dev, module);
		lpsc_module_wait(dev, module);
	}
}

static void lpsc_module_put_internal(struct device *dev,
				     struct lpsc_module *module, sbool use, sbool ret)
{
#ifdef CONFIG_TRACE
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
#endif
	sbool modify = SFALSE;

	if (use) {
		pm_trace(TRACE_PM_ACTION_MODULE_PUT,
			 (psc->psc_idx << TRACE_PM_VAL_PSC_SHIFT) |
			 (lpsc_module_idx(dev, module) << TRACE_PM_VAL_LPSC_SHIFT) |
			 (module->use_count & TRACE_PM_VAL_MAX_PSC_DATA));
		module->use_count--;
		if (module->use_count == 0U) {
			modify = STRUE;
		}
	}

	if (ret) {
		pm_trace(TRACE_PM_ACTION_RETENTION_PUT,
			 (psc->psc_idx << TRACE_PM_VAL_PSC_SHIFT) |
			 (lpsc_module_idx(dev, module) << TRACE_PM_VAL_LPSC_SHIFT) |
			 (module->ret_count & TRACE_PM_VAL_MAX_PSC_DATA));
		module->ret_count--;
		if (module->ret_count == 0U) {
			modify = STRUE;
		}
	}

	if (modify) {
		lpsc_module_sync_state(dev, module);
		if (module->use_count == 0U && use) {
			lpsc_module_clk_put(dev, module);
		}
		if (module->ret_count == 0U && ret) {
			lpsc_module_clk_put(dev, module);
		}
	}
}

void lpsc_module_get(struct device *dev, struct lpsc_module *module)
{
	lpsc_module_get_internal(dev, module, STRUE, SFALSE);
}

void lpsc_module_put(struct device *dev, struct lpsc_module *module)
{
	lpsc_module_put_internal(dev, module, STRUE, SFALSE);
}

void lpsc_module_ret_get(struct device *dev, struct lpsc_module *module)
{
	lpsc_module_get_internal(dev, module, SFALSE, STRUE);
}

void lpsc_module_ret_put(struct device *dev, struct lpsc_module *module)
{
	lpsc_module_put_internal(dev, module, SFALSE, STRUE);
}

/* Drop power up ref counts */
static void psc_pd_drop_pwr_up_ref(struct device *dev)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	pd_idx_t idx;

	for (idx = 0U; idx < psc->pd_count; idx++) {
		struct psc_pd *pd = psc_idx2pd(psc, idx);
		if (pd->pwr_up_enabled) {
			pd->pwr_up_enabled = SFALSE;
			psc_pd_put(dev, pd);
		}
	}
}

struct device *psc_lookup(psc_idx_t id)
{
	struct device *dev;

	dev = psc_devs;
	while (dev) {
		const struct psc_drv_data *psc;
		psc = to_psc_drv_data(get_drv_data(dev));

		if ((psc_idx_t) psc->psc_idx == id) {
			break;
		}

		dev = psc->data->next;
	}

	return dev;
}

struct psc_pd *psc_lookup_pd(struct device *dev, pd_idx_t id)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	struct psc_pd *pd = NULL;

	if (id < psc->pd_count &&
	    (psc->pd_data[id].flags & PSC_PD_EXISTS)) {
		pd = psc_idx2pd(psc, id);
	}
	return pd;
}

struct lpsc_module *psc_lookup_lpsc(struct device *dev, pd_idx_t id)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	struct lpsc_module *mod = NULL;

	if (id < psc->module_count &&
	    (psc->mod_data[id].flags & LPSC_MODULE_EXISTS)) {
		mod = psc_idx2mod(psc, id);
	}
	return mod;
}

/**
 * \brief Initialize all the PSC powerdomains.
 *
 * This initializes the powerdomains by waiting for them to finish any
 * active transitions, reading their state, and syncronizing it with the
 * in memory state.
 *
 * \return
 * 0 on success, <0 on failure.
 */
static s32 psc_initialize_pds(struct device *dev)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	pd_idx_t idx;

	/* First pass, find out which domains are on */
	for (idx = 0U; idx < psc->pd_count; idx++) {
		struct psc_pd *pd = psc_idx2pd(psc, idx);
		u8 state;

		if (!(psc->pd_data[idx].flags & PSC_PD_EXISTS)) {
			continue;
		}

		pm_trace(TRACE_PM_ACTION_PD_INIT,
			 (psc->psc_idx << TRACE_PM_VAL_PSC_SHIFT) |
			 (idx << TRACE_PM_VAL_PD_SHIFT));
		psc_pd_wait(dev, pd);
		state = psc_read(dev, PSC_PDSTAT(idx)) & PDSTAT_STATE_MASK;

		/*
		 * Mark a PD as power up in use so we don't power everything
		 * off before PMMC startup is complete
		 */
		pd->pwr_up_enabled =
			state == PDCTL_STATE_ON ||
			(psc->pd_data[idx].flags & PSC_PD_ALWAYSON);
	}

	/* Second pass, sync use count and impossible hardware states */
	for (idx = 0U; idx < psc->pd_count; idx++) {
		struct psc_pd *pd = psc_idx2pd(psc, idx);
		if (pd->pwr_up_enabled) {
			psc_pd_get(dev, pd);
		}
	}

	return 0;
}

/* Drop power up ref counts */
void psc_drop_pwr_up_ref(void)
{
	struct device *dev = psc_devs;

	while (dev) {
		const struct psc_drv_data *psc;
		lpsc_idx_t idx;

		psc = to_psc_drv_data(get_drv_data(dev));

		for (idx = 0U; idx < psc->module_count; idx++) {
			struct lpsc_module *mod = psc_idx2mod(psc, idx);
			if (mod->pwr_up_enabled) {
				mod->pwr_up_enabled = SFALSE;
				lpsc_module_put(dev, mod);
			}
			if (mod->pwr_up_ret) {
				mod->pwr_up_ret = SFALSE;
				lpsc_module_ret_put(dev, mod);
			}
		}
		dev = psc->data->next;
	}
}

/**
 * \brief Initialize all the PSC modules.
 *
 * This initializes the modules by waiting for them to finish any active
 * transitions and reading their state.
 *
 * \return
 * 0 on success, <0 on failure.
 */
static s32 psc_initialize_modules(struct device *dev)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	lpsc_idx_t idx;

	/* First pass, find out which modules are enabled */
	for (idx = 0U; idx < psc->module_count; idx++) {
		struct lpsc_module *mod = psc_idx2mod(psc, idx);
		u32 v;
		s32 i;

		if (!(psc->mod_data[idx].flags & LPSC_MODULE_EXISTS)) {
			continue;
		}

		v = psc_read(dev, PSC_MDCTL(idx));

		i = PSC_TRANSITION_TIMEOUT;
		while (((v = psc_read(dev, PSC_MDSTAT(idx))) &
			MDSTAT_BUSY_MASK) && --i) {
		}
		if (!i) {
			pm_trace(TRACE_PM_ACTION_PSC_TRANSITION_TIMEOUT | TRACE_PM_ACTION_FAIL,
				 ((psc->psc_idx) << TRACE_PM_VAL_PSC_SHIFT) |
				 (idx << TRACE_PM_VAL_PD_SHIFT) | TRACE_PM_VAL_PD_POS3);
		}

		v = psc_read(dev, PSC_MDSTAT(idx));
		v &= MDSTAT_STATE_MASK;

		/* Ref count as if we are moving out of off state */
		mod->sw_state = MDSTAT_STATE_SWRSTDISABLE;

		switch (v) {
		case MDSTAT_STATE_ENABLE:
			mod->pwr_up_enabled = STRUE;
		case MDSTAT_STATE_DISABLE:
			mod->pwr_up_ret = STRUE;
		case MDSTAT_STATE_SWRSTDISABLE:
			break;
		default:
			/* Invalid initial state, try turning every on */
			mod->pwr_up_ret = STRUE;
			mod->pwr_up_enabled = STRUE;
		}
	}

	return 0;
}

/**
 * \brief Finish initializing all the PSC modules.
 *
 * This finishes the initialization of modules by syncronizing their
 * state with the in memory state.
 *
 * \return
 * 0 on success, <0 on failure.
 */
static s32 psc_initialize_modules_finish(struct device *dev)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	lpsc_idx_t idx;

	/* Second pass, sync ref counts */
	for (idx = 0U; idx < psc->module_count; idx++) {
		struct lpsc_module *mod = psc_idx2mod(psc, idx);
		lpsc_module_get_internal(dev, mod, mod->pwr_up_enabled,
					 mod->pwr_up_ret);
	}

	psc_pd_drop_pwr_up_ref(dev);

	return 0;
}

/**
 * \brief Check if PSCs we depend on have completed their initial config
 *
 * PSCs can have domains that depend on domains in other PSCs. We break up
 * initialization into two stages because PSCs can have cross dependencies.
 * Once all PSCs in a cross dependency set have completed, each one can
 * move to the second stage of initialization. We use the -EDEFER system
 * to manage this.
 *
 * \return
 * 0 on success, <0 on failure.
 */
static s32 psc_module_deps_ready(struct device *dev)
{
	const struct psc_drv_data *psc = to_psc_drv_data(get_drv_data(dev));
	u32 idx;
	sbool not_ready = SFALSE;
	s32 ret = 0;

	for (idx = 0; !not_ready && idx < psc->module_count; idx++) {
		if (((psc->mod_data[idx].flags & LPSC_DEPENDS) != 0UL) && (psc->mod_data[idx].depends_psc_idx != psc->psc_idx)) {
			if (psc_lookup((psc_idx_t) psc->mod_data[idx].depends_psc_idx) == NULL) {
				not_ready = STRUE;
				ret = -EDEFER;
			}
		}
	}

	return ret;
}

static s32 psc_pre_init(struct device *dev)
{
	const struct drv_data *data;
	const struct psc_drv_data *psc;
	s32 ret = 0;

	data = get_drv_data(dev);
	psc = to_psc_drv_data(data);

	/* Only perform initial configuration if it has not been completed */
	if (psc_lookup((psc_idx_t) psc->psc_idx) == NULL) {
		const struct resource_mem *mem;

		mem = device_resource_mem(dev, 0);
		if (!mem) {
			ret = -EINVAL;
		}

		if (ret == 0) {
			ret = psc_initialize_pds(dev);
		}

		if (ret == 0) {
			ret = psc_initialize_modules(dev);
		}

		if (ret == 0) {
			/* This marks initial config as complete */
			psc->data->next = psc_devs;
			psc_devs = dev;
		}
	}

	return ret;
}

static s32 psc_post_init(struct device *dev)
{
	s32 ret;

	ret = psc_module_deps_ready(dev);

	if (ret == SUCCESS) {
		ret = psc_initialize_modules_finish(dev);
	}

	return ret;
}

const struct drv psc_drv = {
	.pre_init	= psc_pre_init,
	.post_init	= psc_post_init,
};
