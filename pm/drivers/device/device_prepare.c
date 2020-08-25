/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <device_prepare.h>
#include <device.h>
#include <lib/trace.h>
#include <types/errno.h>
#include <soc/host_idx_mapping.h>

static s32 device_prepare(u8 host_id, u32 id, u8 *host_idx, struct device **device, sbool exclusive)
{
	s32 ret = SUCCESS;
	struct device *local_device = NULL;
	u8 local_host_idx = HOST_IDX_NONE;

	local_device = device_api_lookup(id);
	if (!local_device) {
		pm_trace(TRACE_PM_ACTION_BAD_DEVICE, id);
		ret = -EINVAL;
	}

	if (ret == SUCCESS) {
		if (local_device->initialized == 0U) {
			ret = -EINVAL;
		}
	}

	if (ret == SUCCESS) {
		local_host_idx = host_idx_lookup(host_id);
		if (local_host_idx == HOST_IDX_NONE) {
			ret = -EINVAL;
		}
	}

	if ((ret == SUCCESS) && exclusive) {
		if ((local_device->exclusive != 0U) && (local_device->exclusive != local_host_idx)) {
			pm_trace(TRACE_PM_ACTION_EXCLUSIVE_DEVICE,
				 (((u32) id << TRACE_PM_VAL_EXCLUSIVE_DEVICE_ID_SHIFT) &
				  TRACE_PM_VAL_EXCLUSIVE_DEVICE_ID_MASK) |
				 (((u32) host_id << TRACE_PM_VAL_EXCLUSIVE_HOST_ID_SHIFT) &
				  TRACE_PM_VAL_EXCLUSIVE_HOST_ID_MASK));
			ret = -EINVAL;
		}
	}

	if (device) {
		*device = local_device;
	}
	if (host_idx) {
		*host_idx = local_host_idx;
	}

	return ret;
}

s32 device_prepare_exclusive(u8 host_id, u32 id, u8 *host_idx, struct device **device)
{
	s32 ret;

	/* Ensure devices are fully initialized to allow modification */
	ret = devices_init_rw();

	if (ret == SUCCESS) {
		ret = device_prepare(host_id, id, host_idx, device, STRUE);
	}
	return ret;
}

s32 device_prepare_nonexclusive(u8 host_id, u32 id, u8 *host_idx, struct device **device)
{
	return device_prepare(host_id, id, host_idx, device, SFALSE);
}
