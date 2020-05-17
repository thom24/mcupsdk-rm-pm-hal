/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#if defined (__TI_ARM_V7M3__)
#include <device.h>
#include <device_pm.h>
#include <osal/osal_core.h>
#include <osal/osal_msg.h>
#include <tisci_provider/tisci.h>
#include <tisci/tisci_protocol.h>
#include <tisci/pm/tisci_pm_device.h>
#include <types/errno.h>
#include <lib/trace.h>
#include <device_prepare.h>
#include <soc/host_idx_mapping.h>

s32 tisci_msg_set_device_handler(u32 *msg_recv)
{
	struct tisci_msg_set_device_req *req =
		(struct tisci_msg_set_device_req *) msg_recv;
	struct tisci_msg_set_device_resp *resp =
		(struct tisci_msg_set_device_resp *) msg_recv;
	struct device *device = NULL;
	u32 id = req->id;
	u8 state = req->state;
	u32 flags = req->hdr.flags;
	u8 host_id = req->hdr.host;
	sbool enable, retention;
	s32 ret = SUCCESS;
	u8 host_idx;

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_SET_DEVICE);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID, id);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_VAL, state);

	tisci_msg_clear_flags(&resp->hdr);

	ret = device_prepare_exclusive(host_id, id, &host_idx, &device);
	if (ret == SUCCESS) {
		switch (state) {
		case TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF:
			enable = SFALSE;
			retention = SFALSE;
			break;
		case TISCI_MSG_VALUE_DEVICE_SW_STATE_RETENTION:
			enable = SFALSE;
			retention = STRUE;
			break;
		case TISCI_MSG_VALUE_DEVICE_SW_STATE_ON:
			enable = STRUE;
			retention = STRUE;
			break;
		default:
			pm_trace(TRACE_PM_ACTION_INVALID_STATE, state);
			ret = -EINVAL;
		}
	}

	if (ret == SUCCESS) {
		if ((flags & TISCI_MSG_FLAG_DEVICE_EXCLUSIVE) != 0UL) {
			/* Make sure no one else has the device enabled */
			u32 mask = DEV_FLAG_ENABLED_MASK;
			u32 enabled;
			/* It's ok if we already have the device enabled */
			mask &= ~DEV_FLAG_ENABLED(host_idx);
			/* It's also ok if the device in on due to power up en */
			mask &= ~DEV_FLAG_POWER_ON_ENABLED;
			enabled = (device->flags & mask) >> DEV_FLAG_ENABLED_BIT;
			if (enabled != 0UL) {
				u8 i;
				/*
				 * Note, rather than trying to fit the enabled
				 * bit field in the trace message, just pick
				 * single host to include.
				 */
				for (i = 0U; i < sizeof(enabled) * 8U; i++) {
					if ((enabled & 1UL) != 0UL) {
						break;
					}
					enabled >>= 1UL;
				}
#ifdef CONFIG_TRACE
				{
					u32 enabled_host_id = TRACE_PM_VAL_EXCLUSIVE_BUSY_EHOST_ID_MASK >>
							      TRACE_PM_VAL_EXCLUSIVE_BUSY_EHOST_ID_SHIFT;
					/*
					 * Do a reverse lookup. Find host ID from
					 * host index.
					 */
					if (i != sizeof(enabled) * 8U) {
						u8 j;
						for (j = 0U; j < soc_host_indexes_sz; j++) {
							if (soc_host_indexes[j] == i) {
								enabled_host_id = j;
								break;
							}
						}
					}
					pm_trace(TRACE_PM_ACTION_EXCLUSIVE_BUSY,
						 (((u32) id << TRACE_PM_VAL_EXCLUSIVE_BUSY_DEVICE_ID_SHIFT) &
						  TRACE_PM_VAL_EXCLUSIVE_BUSY_DEVICE_ID_MASK) |
						 (((u32) host_id << TRACE_PM_VAL_EXCLUSIVE_BUSY_RHOST_ID_SHIFT) &
						  TRACE_PM_VAL_EXCLUSIVE_BUSY_RHOST_ID_MASK) |
						 (((u32) enabled_host_id << TRACE_PM_VAL_EXCLUSIVE_BUSY_EHOST_ID_SHIFT) &
						  TRACE_PM_VAL_EXCLUSIVE_BUSY_EHOST_ID_MASK));
				}
#endif
				ret = -EINVAL;
			}
		}
	}

	if (ret == SUCCESS) {
		if ((flags & TISCI_MSG_FLAG_DEVICE_WAKE_ENABLED) != 0UL) {
			/* FIXME: Not supported */
		}

		if ((flags & TISCI_MSG_FLAG_DEVICE_EXCLUSIVE) != 0UL) {
			/* Only this host may modify device */
			device->exclusive = host_idx;
		} else {
			/* Allow any host to modify device */
			device->exclusive = 0U;
		}

		if ((flags & TISCI_MSG_FLAG_DEVICE_RESET_ISO) != 0UL) {
			device_set_reset_iso(device, STRUE);
		} else {
			device_set_reset_iso(device, SFALSE);
		}

		/* Ordering to void unnecessary PD transations */
		if (retention) {
			device_set_retention(device, retention);
		}
		device_set_state(device, host_idx, enable);
		if (!retention) {
			device_set_retention(device, retention);
		}
	}

	if ((flags & TISCI_MSG_FLAG_AOP) != 0UL) {
		if (ret == SUCCESS) {
			tisci_msg_set_ack_resp(&resp->hdr);
		} else {
			tisci_msg_set_nak_resp(&resp->hdr);
		}
		osal_msg_response((u32 *) resp, sizeof(*resp));
	}
	return ret;
}

static struct tisci_client tisci_msg_set_device = {
	.handler	= tisci_msg_set_device_handler,
	.subsystem	= SUBSYSTEM_PM,
};

s32 tisci_msg_get_device_handler(u32 *msg_recv)
{
	struct tisci_msg_get_device_req *req =
		(struct tisci_msg_get_device_req *) msg_recv;
	struct tisci_msg_get_device_resp *resp =
		(struct tisci_msg_get_device_resp *) msg_recv;
	struct device *device = NULL;
	u32 id = req->id;
	u32 flags = req->hdr.flags;
	s32 ret = SUCCESS;
	u8 host_idx;

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_GET_DEVICE);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID, id);

	tisci_msg_clear_flags(&resp->hdr);

	ret = device_prepare_nonexclusive(req->hdr.host, id, &host_idx, &device);
	if (ret == SUCCESS) {
		u32 context_loss_count;
		u32 resets;
		u8 programmed_state;
		u8 current_state;

		context_loss_count = device_get_context_loss_count(device);
		resets = device_get_resets(device);

		if ((device->flags & DEV_FLAG_ENABLED(host_idx)) != 0UL) {
			programmed_state = TISCI_MSG_VALUE_DEVICE_SW_STATE_ON;
		} else if (device->flags & DEV_FLAG_RETENTION) {
			programmed_state = TISCI_MSG_VALUE_DEVICE_SW_STATE_RETENTION;
		} else {
			programmed_state = TISCI_MSG_VALUE_DEVICE_SW_STATE_AUTO_OFF;
		}

		switch (device_get_state(device)) {
		case 0:
			current_state = TISCI_MSG_VALUE_DEVICE_HW_STATE_OFF;
			break;
		case 1:
			current_state = TISCI_MSG_VALUE_DEVICE_HW_STATE_ON;
			break;
		default:
			current_state = TISCI_MSG_VALUE_DEVICE_HW_STATE_TRANS;
			break;
		}

		if (device_get_reset_iso(device)) {
			resp->hdr.flags = TISCI_MSG_FLAG_DEVICE_RESET_ISO;
		}

		resp->context_loss_count        = context_loss_count;
		resp->resets                    = resets;
		resp->programmed_state          = programmed_state;
		resp->current_state             = current_state;
	}

	if ((flags & TISCI_MSG_FLAG_AOP) != 0UL) {
		if (ret == SUCCESS) {
			tisci_msg_set_ack_resp(&resp->hdr);
		} else {
			tisci_msg_set_nak_resp(&resp->hdr);
		}
		osal_msg_response((u32 *) resp, sizeof(*resp));
	}
	return ret;
}

static struct tisci_client tisci_msg_get_device = {
	.handler	= tisci_msg_get_device_handler,
	.subsystem	= SUBSYSTEM_PM,
};

s32 tisci_msg_set_device_resets_handler(u32 *msg_recv)
{
	struct tisci_msg_set_device_resets_req *req =
		(struct tisci_msg_set_device_resets_req *) msg_recv;
	struct tisci_msg_set_device_resets_resp *resp =
		(struct tisci_msg_set_device_resets_resp *) msg_recv;
	struct device *device = NULL;
	u32 id = req->id;
	u32 flags = req->hdr.flags;
	u32 resets = req->resets;
	s32 ret = SUCCESS;

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_SET_DEVICE_RESETS);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID, id);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_VAL, resets);

	tisci_msg_clear_flags(&resp->hdr);

	ret = device_prepare_exclusive(req->hdr.host, id, NULL, &device);
	if (ret == SUCCESS) {
		device_set_resets(device, resets);
	}

	if ((flags & TISCI_MSG_FLAG_AOP) != 0UL) {
		if (ret == SUCCESS) {
			tisci_msg_set_ack_resp(&resp->hdr);
		} else {
			tisci_msg_set_nak_resp(&resp->hdr);
		}
		osal_msg_response((u32 *) resp, sizeof(*resp));
	}
	return ret;
}

static struct tisci_client tisci_msg_set_device_resets = {
	.handler	= tisci_msg_set_device_resets_handler,
	.subsystem	= SUBSYSTEM_PM,
};

s32 tisci_msg_device_drop_powerup_ref_handler(u32 *msg_recv)
{
	struct tisci_msg_device_drop_powerup_ref_req *req =
		(struct tisci_msg_device_drop_powerup_ref_req *) msg_recv;
	struct tisci_msg_device_drop_powerup_ref_resp *resp =
		(struct tisci_msg_device_drop_powerup_ref_resp *) msg_recv;
	u32 flags = req->hdr.flags;

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_DEVICE_DROP_POWERUP_REF);

	tisci_msg_clear_flags(&resp->hdr);

	devices_drop_power_up_ref();

	if ((flags & TISCI_MSG_FLAG_AOP) != 0UL) {
		tisci_msg_set_ack_resp(&resp->hdr);
		osal_msg_response((u32 *) resp, sizeof(*resp));
	}

	return SUCCESS;
}

static struct tisci_client tisci_msg_device_drop_powerup_ref = {
	.handler	= tisci_msg_device_drop_powerup_ref_handler,
	.subsystem	= SUBSYSTEM_PM,
};

s32 pm_device_message_init(void)
{
	s32 ret = SUCCESS;

	ret = tisci_user_client_register(TISCI_MSG_SET_DEVICE,
					 &tisci_msg_set_device);

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_GET_DEVICE,
						 &tisci_msg_get_device);
	}

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_SET_DEVICE_RESETS,
						 &tisci_msg_set_device_resets);
	}

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_DEVICE_DROP_POWERUP_REF,
						 &tisci_msg_device_drop_powerup_ref);
	}

	return ret;
}
#endif
