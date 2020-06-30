/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <psc.h>
#include <lib/container_of.h>
#include <device.h>
#include <types/errno.h>
#include <types/array_size.h>
#include <lib/trace.h>

static u32 soc_device_get_state_internal(const struct soc_device_data *dev)
{
	struct device *psc_dev = psc_lookup((psc_idx_t) dev->psc_idx);
	u32 ret = 1;

	if (psc_dev) {
		struct lpsc_module *module;
		module = psc_lookup_lpsc(psc_dev, dev->mod);
		if (module) {
			ret = lpsc_module_get_state(psc_dev, module);
		}
	}

	return ret;
}

u32 soc_device_get_state(struct device *dev)
{
	const struct dev_data *data = get_dev_data(dev);
	u32 ret = 2;

	if (data->soc.psc_idx == PSC_DEV_MULTIPLE) {
		u32 i;
		const struct soc_device_data *domains;
		domains = soc_psc_multiple_domains[data->soc.mod];
		for (i = 0; domains[i].psc_idx != PSC_DEV_NONE; i++) {
			u32 this_ret;
			this_ret = soc_device_get_state_internal(&domains[i]);
			if (i == 0) {
				ret = this_ret;
			} else if (ret != this_ret) {
				/* Mixed state of our domains, label as transition */
				ret = 2;
			}
		}
	} else {
		ret = soc_device_get_state_internal(&data->soc);
	}

	return ret;
}

/*
 * FIXME: Reset ISO and local reset are per module, but those are often
 * shared by several devices.
 */
static void soc_device_set_reset_iso_internal(const struct soc_device_data *dev, sbool enable)
{
	struct device *psc_dev = psc_lookup((psc_idx_t) dev->psc_idx);

	if (psc_dev) {
		struct lpsc_module *module;
		module = psc_lookup_lpsc(psc_dev, dev->mod);
		if (module) {
			lpsc_module_set_reset_iso(psc_dev, module, enable);
		}
	}
}

void soc_device_set_reset_iso(struct device *dev, sbool enable)
{
	const struct dev_data *data = get_dev_data(dev);

	if (data->soc.psc_idx == PSC_DEV_MULTIPLE) {
		/* Reset ISO not supported for devices with multiple domains */
	} else {
		soc_device_set_reset_iso_internal(&data->soc, enable);
	}
}

static sbool soc_device_get_reset_iso_internal(const struct soc_device_data *dev)
{
	struct device *psc_dev = psc_lookup((psc_idx_t) dev->psc_idx);
	sbool ret = SFALSE;

	if (psc_dev) {
		struct lpsc_module *module;
		module = psc_lookup_lpsc(psc_dev, dev->mod);
		if (module) {
			ret = lpsc_module_get_reset_iso(psc_dev, module);
		}
	}

	return ret;
}

sbool soc_device_get_reset_iso(struct device *dev)
{
	const struct dev_data *data = get_dev_data(dev);
	sbool ret = SFALSE;

	if (data->soc.psc_idx == PSC_DEV_MULTIPLE) {
		/* Reset ISO not supported for devices with multiple domains */
	} else {
		ret = soc_device_get_reset_iso_internal(&data->soc);
	}

	return ret;
}

static void soc_device_set_resets_internal(const struct soc_device_data *dev, u32 resets)
{
	struct device *psc_dev = psc_lookup((psc_idx_t) dev->psc_idx);

	if (psc_dev) {
		struct lpsc_module *module;
		module = psc_lookup_lpsc(psc_dev, dev->mod);
		if (module) {
			sbool local_reset = SFALSE;
			sbool module_reset = SFALSE;
			if ((resets & BIT(0)) != 0U) {
				local_reset = STRUE;
			}
			if ((resets & BIT(1)) != 0U) {
				module_reset = STRUE;
			}
			lpsc_module_set_local_reset(psc_dev, module, local_reset);
			lpsc_module_set_module_reset(psc_dev, module, module_reset);
		}
	}
}

void soc_device_set_resets(struct device *dev, u32 resets)
{
	const struct dev_data *data = get_dev_data(dev);

	if (data->soc.psc_idx == PSC_DEV_MULTIPLE) {
		/* Resets not supported for devices with multiple domains */
	} else {
		soc_device_set_resets_internal(&data->soc, resets);
	}
}

static u32 soc_device_get_resets_internal(const struct soc_device_data *dev)
{
	struct device *psc_dev = psc_lookup((psc_idx_t) dev->psc_idx);
	u32 resets = 0U;

	if (psc_dev) {
		struct lpsc_module *module;
		module = psc_lookup_lpsc(psc_dev, dev->mod);
		if (module) {
			sbool ret;
			ret = lpsc_module_get_local_reset(psc_dev, module);
			if (ret) {
				resets |= BIT(0);
			}
			ret = lpsc_module_get_module_reset(psc_dev, module);
			if (ret) {
				resets |= BIT(1);
			}
		}
	}

	return resets;
}

u32 soc_device_get_resets(struct device *dev)
{
	const struct dev_data *data = get_dev_data(dev);
	u32 resets = 0;

	if (data->soc.psc_idx == PSC_DEV_MULTIPLE) {
		/* Resets not supported for devices with multiple domains */
	} else {
		resets = soc_device_get_resets_internal(&data->soc);
	}

	return resets;
}

static u32 soc_device_get_context_loss_count_internal(const struct soc_device_data *dev)
{
	struct device *psc_dev = psc_lookup((psc_idx_t) dev->psc_idx);
	u32 ret = 0;

	if (psc_dev) {
		struct lpsc_module *module;
		module = psc_lookup_lpsc(psc_dev, dev->mod);
		if (module) {
			ret = module->loss_count;
		}
	}

	return ret;
}

u32 soc_device_get_context_loss_count(struct device *dev)
{
	const struct dev_data *data = get_dev_data(dev);
	u32 ret = 0;

	if (data->soc.psc_idx == PSC_DEV_MULTIPLE) {
		u32 i;
		const struct soc_device_data *domains;
		domains = soc_psc_multiple_domains[data->soc.mod];
		for (i = 0; domains[i].psc_idx != PSC_DEV_NONE; i++) {
			ret += soc_device_get_context_loss_count_internal(&domains[i]);
		}
	} else {
		ret = soc_device_get_context_loss_count_internal(&data->soc);
	}

	return ret;
}

static void soc_device_enable_internal(const struct soc_device_data *dev)
{
	struct device *psc_dev = psc_lookup((psc_idx_t) dev->psc_idx);

	if (psc_dev) {
		struct lpsc_module *module;
		module = psc_lookup_lpsc(psc_dev, dev->mod);
		if (module) {
			lpsc_module_get(psc_dev, module);
		}
	}
}

void soc_device_enable(struct device *dev)
{
	const struct dev_data *data = get_dev_data(dev);

	pm_trace(TRACE_PM_ACTION_DEVICE_ON, device_id(dev));

	if (data->soc.psc_idx == PSC_DEV_MULTIPLE) {
		u32 i;
		const struct soc_device_data *domains;
		domains = soc_psc_multiple_domains[data->soc.mod];
		for (i = 0; domains[i].psc_idx != PSC_DEV_NONE; i++) {
			soc_device_enable_internal(&domains[i]);
		}
	} else {
		soc_device_enable_internal(&data->soc);
	}
}

static void soc_device_disable_internal(const struct soc_device_data *dev)
{
	struct device *psc_dev = psc_lookup((psc_idx_t) dev->psc_idx);

	if (psc_dev) {
		struct lpsc_module *module;
		module = psc_lookup_lpsc(psc_dev, dev->mod);
		if (module) {
			lpsc_module_put(psc_dev, module);
		}
	}
}

void soc_device_disable(struct device *dev, sbool domain_reset)
{
	const struct dev_data *data = get_dev_data(dev);

	pm_trace(TRACE_PM_ACTION_DEVICE_OFF, device_id(dev));

	if (domain_reset) {
		/* No action */
	} else if (data->soc.psc_idx == PSC_DEV_MULTIPLE) {
		u32 i;
		const struct soc_device_data *domains;
		domains = soc_psc_multiple_domains[data->soc.mod];
		for (i = 0; domains[i].psc_idx != PSC_DEV_NONE; i++) {
			soc_device_disable_internal(&domains[i]);
		}
	} else {
		soc_device_disable_internal(&data->soc);
	}
}

static void soc_device_ret_enable_internal(const struct soc_device_data *dev)
{
	struct device *psc_dev = psc_lookup((psc_idx_t) dev->psc_idx);

	if (psc_dev) {
		struct psc_pd *pd;
		struct lpsc_module *module;

		pd = psc_lookup_pd(psc_dev, (pd_idx_t) dev->pd);
		if (pd) {
			psc_pd_get(psc_dev, pd);
		}

		module = psc_lookup_lpsc(psc_dev, dev->mod);
		if (module) {
			lpsc_module_ret_get(psc_dev, module);
		}
	}
}

void soc_device_ret_enable(struct device *dev)
{
	const struct dev_data *data = get_dev_data(dev);

	if (data->soc.psc_idx == PSC_DEV_MULTIPLE) {
		u32 i;
		const struct soc_device_data *domains;
		domains = soc_psc_multiple_domains[data->soc.mod];
		for (i = 0; domains[i].psc_idx != PSC_DEV_NONE; i++) {
			soc_device_ret_enable_internal(&domains[i]);
		}
	} else {
		soc_device_ret_enable_internal(&data->soc);
	}
}

static void soc_device_ret_disable_internal(const struct soc_device_data *dev)
{
	struct device *psc_dev = psc_lookup((psc_idx_t) dev->psc_idx);

	if (psc_dev) {
		struct lpsc_module *module;
		struct psc_pd *pd;

		module = psc_lookup_lpsc(psc_dev, dev->mod);
		if (module) {
			lpsc_module_ret_put(psc_dev, module);
		}

		pd = psc_lookup_pd(psc_dev, (pd_idx_t) dev->pd);
		if (pd) {
			psc_pd_put(psc_dev, pd);
		}
	}
}

void soc_device_ret_disable(struct device *dev)
{
	const struct dev_data *data = get_dev_data(dev);

	if (data->soc.psc_idx == PSC_DEV_MULTIPLE) {
		u32 i;
		const struct soc_device_data *domains;
		domains = soc_psc_multiple_domains[data->soc.mod];
		for (i = 0; domains[i].psc_idx != PSC_DEV_NONE; i++) {
			soc_device_ret_disable_internal(&domains[i]);
		}
	} else {
		soc_device_ret_disable_internal(&data->soc);
	}
}

void soc_device_init_complete(void)
{
	psc_drop_pwr_up_ref();
}

static s32 soc_device_verify_mapping(const struct psc_drv_data *psc,
				     u32 dev_id, const struct soc_device_data *dev)
{
	s32 ret = 0;

	/*
	 * Make sure the redundant const data stored in the PSC data is
	 * correct. This redundant data would idealy be checked or even
	 * generated at compile time.
	 */
	if (dev->mod != PSC_LPSC_NONE) {
		const struct lpsc_module_data *mdata = psc->mod_data + dev->mod;
		u32 i;

		if ((mdata->flags & LPSC_DEVICES_LIST) != 0UL) {
			for (i = 0U; mdata->dev_list[i] != dev_id; i++) {
				if (mdata->dev_list[i] == DEV_ID_NONE) {
					ret = -EINVAL;
					break;
				}
			}
		} else {
			for (i = 0U; mdata->dev_array[i] != dev_id; i++) {
				if (i >= ARRAY_SIZE(mdata->dev_array) - 1UL ||
				    mdata->dev_array[i] == DEV_ID_NONE) {
					ret = -EINVAL;
					break;
				}
			}
		}
	}

	if (ret != 0L) {
		pm_trace(TRACE_PM_ACTION_INVALID_PSC_DATA | TRACE_PM_ACTION_FAIL, 0UL);
	}

	return ret;
}

static s32 soc_device_init_internal(struct device *dev)
{
	const struct dev_data *dev_data;
	struct device *psc_dev = NULL;
	const struct psc_drv_data *psc = NULL;
	u32 dev_id;
	s32 ret = 0;

	dev_id = device_id(dev);
	dev_data = get_dev_data(dev);

	/* Check if this PSC manages it's own power domain */
	if (dev_data->flags & DEVD_FLAG_DRV_DATA) {
		const struct drv_data *drv_data;
		drv_data = to_drv_data(dev_data);
		if (drv_data->drv == &psc_drv) {
			psc = to_psc_drv_data(drv_data);
			if (psc->psc_idx == dev_data->soc.psc_idx) {
				psc_dev = dev;
			} else {
				psc = NULL;
			}
		}
	}

	if (psc) {
		/* We are our own PSC */
		ret = soc_device_verify_mapping(psc, dev_id, &dev_data->soc);
	} else if (dev_data->soc.psc_idx == PSC_DEV_MULTIPLE) {
		/* Find all the PSCs this device needs */
		u32 i;
		const struct soc_device_data *domains;
		domains = soc_psc_multiple_domains[dev_data->soc.mod];
		for (i = 0; domains[i].psc_idx != PSC_DEV_NONE; i++) {
			psc_dev = psc_lookup((psc_idx_t) domains[i].psc_idx);
			if (ret != 0) {
				/* Do nothing */
			} else if (!psc_dev) {
				ret = -EDEFER;
			} else {
				psc = to_psc_drv_data(get_drv_data(psc_dev));
				ret = soc_device_verify_mapping(psc, dev_id, &domains[i]);
			}
		}
	} else {
		/* We just need the one PSC */
		psc_dev = psc_lookup((psc_idx_t) dev_data->soc.psc_idx);
		if (!psc_dev) {
			/*
			 * Don't try to bring this dev up before calling init
			 * on the device's PSC.
			 */
			ret = -EDEFER;
		} else {
			psc = to_psc_drv_data(get_drv_data(psc_dev));
			ret = soc_device_verify_mapping(psc, dev_id, &dev_data->soc);
		}
	}

	return ret;
}

/* Defer all other device intialization until PSC initializes */
s32 soc_device_init(struct device *dev)
{
	const struct dev_data *dev_data;
	s32 ret = 0;

	dev_data = get_dev_data(dev);

	if (dev_data->soc.psc_idx != PSC_DEV_NONE) {
		ret = soc_device_init_internal(dev);
	}

	return ret;
}
