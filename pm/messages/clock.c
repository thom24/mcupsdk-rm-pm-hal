/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#if defined (__TI_ARM_V7M3__)
#include <clk.h>
#include <clk_mux.h>
#include <clk_div.h>
#include <device.h>
#include <device_clk.h>
#include <types/errno.h>
#include <osal/osal_core.h>
#include <osal/osal_msg.h>
#include <tisci_provider/tisci.h>
#include <tisci/tisci_protocol.h>

#include <tisci/pm/tisci_pm_clock.h>
#include <limits.h>
#include <lib/trace.h>
#include <device_prepare.h>

static s32 tisci_msg_set_clock_handler(u32 *msg_recv)
{
	struct tisci_msg_set_clock_req *req =
		(struct tisci_msg_set_clock_req *) msg_recv;
	struct tisci_msg_set_clock_resp *resp =
		(struct tisci_msg_set_clock_resp *) msg_recv;
	struct device *device = NULL;
	sbool gated = SFALSE;
	u32 id = req->device;
	dev_clk_idx_t clk;
	u8 state = req->state;
	s32 ret = SUCCESS;
	u32 flags = req->hdr.flags;

	/* Handle higher clock IDs */
	if (req->clk == 255UL) {
		clk = req->clk32;
	} else {
		clk = req->clk;
	}

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_SET_CLOCK);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID,
		 id | ((u32) clk << TRACE_PM_MSG_CLK_ID_SHIFT));
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_VAL, state);

	tisci_msg_clear_flags(&resp->hdr);

	ret = device_prepare_exclusive(req->hdr.host, id, NULL, &device);
	if (ret == SUCCESS) {
		switch (state) {
		case TISCI_MSG_VALUE_CLOCK_SW_STATE_UNREQ:
			gated = STRUE;
			break;
		case TISCI_MSG_VALUE_CLOCK_SW_STATE_AUTO:
		case TISCI_MSG_VALUE_CLOCK_SW_STATE_REQ:
			gated = SFALSE;
			break;
		default:
			pm_trace(TRACE_PM_ACTION_INVALID_STATE, state);
			ret = -EINVAL;
		}
	}

	if (ret == SUCCESS) {
		if ((flags & TISCI_MSG_FLAG_CLOCK_ALLOW_SSC) != 0UL) {
			device_clk_set_ssc(device, clk, STRUE);
		} else {
			device_clk_set_ssc(device, clk, SFALSE);
		}

		if ((flags & TISCI_MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE) != 0UL) {
			device_clk_set_freq_change(device, clk, STRUE);
		} else {
			device_clk_set_freq_change(device, clk, SFALSE);
		}

		if ((flags & TISCI_MSG_FLAG_CLOCK_INPUT_TERM) != 0UL) {
			device_clk_set_input_term(device, clk, STRUE);
		} else {
			device_clk_set_input_term(device, clk, SFALSE);
		}

		if (!device_clk_set_gated(device, clk, gated)) {
			ret = -EINVAL;
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

static struct tisci_client tisci_msg_set_clock = {
	.handler	= tisci_msg_set_clock_handler,
	.subsystem	= SUBSYSTEM_PM,
};

static s32 tisci_msg_get_clock_handler(u32 *msg_recv)
{
	struct tisci_msg_get_clock_req *req =
		(struct tisci_msg_get_clock_req *) msg_recv;
	struct tisci_msg_get_clock_resp *resp =
		(struct tisci_msg_get_clock_resp *) msg_recv;
	struct device *device = NULL;
	u32 id = req->device;
	dev_clk_idx_t clk;
	s32 ret = SUCCESS;
	u32 flags = req->hdr.flags;

	/* Handle higher clock IDs */
	if (req->clk == 255UL) {
		clk = req->clk32;
	} else {
		clk = req->clk;
	}

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_GET_CLOCK);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID,
		 id | ((u32) clk << TRACE_PM_MSG_CLK_ID_SHIFT));

	tisci_msg_clear_flags(&resp->hdr);

	ret = device_prepare_nonexclusive(req->hdr.host, id, NULL, &device);
	if (ret == SUCCESS) {
		u8 prog;
		u8 state;

		prog = device_clk_get_sw_gated(device, clk) ?
		       TISCI_MSG_VALUE_CLOCK_SW_STATE_UNREQ :
		       TISCI_MSG_VALUE_CLOCK_SW_STATE_AUTO;

		state = device_clk_get_hw_ready(device, clk) ?
			TISCI_MSG_VALUE_CLOCK_HW_STATE_READY :
			TISCI_MSG_VALUE_CLOCK_HW_STATE_NOT_READY;

		if (device_clk_get_ssc(device, clk)) {
			resp->hdr.flags |= TISCI_MSG_FLAG_CLOCK_ALLOW_SSC;
		}

		if (device_clk_get_hw_ssc(device, clk)) {
			resp->hdr.flags |= TISCI_MSG_FLAG_CLOCK_SSC_ACTIVE;
		}

		if (device_clk_get_freq_change(device, clk)) {
			resp->hdr.flags |= TISCI_MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE;
		}

		if (device_clk_get_input_term(device, clk)) {
			resp->hdr.flags |= TISCI_MSG_FLAG_CLOCK_INPUT_TERM;
		}

		resp->programmed_state  = prog;
		resp->current_state     = state;
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

static struct tisci_client tisci_msg_get_clock = {
	.handler	= tisci_msg_get_clock_handler,
	.subsystem	= SUBSYSTEM_PM,
};

static s32 tisci_msg_set_clock_parent_handler(u32 *msg_recv)
{
	struct tisci_msg_set_clock_parent_req *req =
		(struct tisci_msg_set_clock_parent_req *) msg_recv;
	struct tisci_msg_set_clock_parent_resp *resp =
		(struct tisci_msg_set_clock_parent_resp *) msg_recv;
	struct device *device = NULL;
	u32 id = req->device;
	dev_clk_idx_t clk;
	dev_clk_idx_t parent;
	s32 ret = SUCCESS;
	u32 flags = req->hdr.flags;

	/* Handle higher clock IDs */
	if (req->clk == 255UL) {
		clk = req->clk32;
	} else {
		clk = req->clk;
	}

	if (req->parent == 255UL) {
		parent = req->parent32;
	} else {
		parent = req->parent;
	}

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_SET_CLOCK_PARENT);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID,
		 id | ((u32) clk << TRACE_PM_MSG_CLK_ID_SHIFT));
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_VAL, parent);

	tisci_msg_clear_flags(&resp->hdr);

	ret = device_prepare_exclusive(req->hdr.host, id, NULL, &device);
	if (ret == SUCCESS) {
		if (!device_clk_set_parent(device, clk, parent)) {
			ret = -EINVAL;
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

static struct tisci_client tisci_msg_set_clock_parent = {
	.handler	= tisci_msg_set_clock_parent_handler,
	.subsystem	= SUBSYSTEM_PM,
};

static s32 tisci_msg_get_clock_parent_handler(u32 *msg_recv)
{
	struct tisci_msg_get_clock_parent_req *req =
		(struct tisci_msg_get_clock_parent_req *) msg_recv;
	struct tisci_msg_get_clock_parent_resp *resp =
		(struct tisci_msg_get_clock_parent_resp *) msg_recv;
	struct device *device = NULL;
	u32 id = req->device;
	dev_clk_idx_t clk;
	s32 ret = SUCCESS;
	u32 flags = req->hdr.flags;

	/* Handle higher clock IDs */
	if (req->clk == 255UL) {
		clk = req->clk32;
	} else {
		clk = req->clk;
	}

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_GET_CLOCK_PARENT);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID,
		 id | ((u32) clk << TRACE_PM_MSG_CLK_ID_SHIFT));

	tisci_msg_clear_flags(&resp->hdr);

	ret = device_prepare_nonexclusive(req->hdr.host, id, NULL, &device);
	if (ret == SUCCESS) {
		dev_clk_idx_t parent;

		parent = device_clk_get_parent(device, clk);

		if (parent == DEV_CLK_ID_NONE) {
			ret = -EINVAL;
		} else {
			/* Use extended API for clock indexes >= 255 */
			if (parent >= 255UL) {
				resp->parent = 255UL;
				resp->parent32 = parent;
			} else {
				resp->parent = parent;
				resp->parent32 = 0xffffffffUL;
			}
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

static struct tisci_client tisci_msg_get_clock_parent = {
	.handler	= tisci_msg_get_clock_parent_handler,
	.subsystem	= SUBSYSTEM_PM,
};

static s32 tisci_msg_get_num_clock_parents_handler(u32 *msg_recv)
{
	struct tisci_msg_get_num_clock_parents_req *req =
		(struct tisci_msg_get_num_clock_parents_req *) msg_recv;
	struct tisci_msg_get_num_clock_parents_resp *resp =
		(struct tisci_msg_get_num_clock_parents_resp *) msg_recv;
	struct device *device = NULL;
	u32 id = req->device;
	dev_clk_idx_t clk;
	s32 ret = SUCCESS;
	u32 flags = req->hdr.flags;

	/* Handle higher clock IDs */
	if (req->clk == 255UL) {
		clk = req->clk32;
	} else {
		clk = req->clk;
	}

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED,
		 TISCI_MSG_GET_NUM_CLOCK_PARENTS);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID,
		 id | ((u32) clk << TRACE_PM_MSG_CLK_ID_SHIFT));

	tisci_msg_clear_flags(&resp->hdr);

	ret = device_prepare_nonexclusive(req->hdr.host, id, NULL, &device);
	if (ret == SUCCESS) {
		dev_clk_idx_t num_parents;

		num_parents = device_clk_get_num_parents(device, clk);

		if (num_parents == DEV_CLK_ID_NONE) {
			ret = -EINVAL;
		} else {
			/* Use extended API for clock indexes >= 255 */
			if (num_parents >= 255UL) {
				resp->num_parents = 255UL;
				resp->num_parents32 = num_parents;
			} else {
				resp->num_parents = num_parents;
				resp->num_parents32 = 0xffffffffUL;
			}
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

static struct tisci_client tisci_msg_get_num_clock_parents = {
	.handler	= tisci_msg_get_num_clock_parents_handler,
	.subsystem	= SUBSYSTEM_PM,
};

static s32 tisci_msg_set_freq_handler(u32 *msg_recv)
{
	struct tisci_msg_set_freq_req *req =
		(struct tisci_msg_set_freq_req *) msg_recv;
	struct tisci_msg_set_freq_resp *resp =
		(struct tisci_msg_set_freq_resp *) msg_recv;
	struct device *device = NULL;
	u32 id = req->device;
	u64 min_freq_hz = req->min_freq_hz;
	u64 target_freq_hz = req->target_freq_hz;
	u64 max_freq_hz = req->max_freq_hz;
	dev_clk_idx_t clk;
	s32 ret = SUCCESS;
	u32 flags = req->hdr.flags;

	/* Handle higher clock IDs */
	if (req->clk == 255UL) {
		clk = req->clk32;
	} else {
		clk = req->clk;
	}

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_SET_FREQ);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID,
		 id | ((u32) clk << TRACE_PM_MSG_CLK_ID_SHIFT));

	tisci_msg_clear_flags(&resp->hdr);

	ret = device_prepare_exclusive(req->hdr.host, id, NULL, &device);
	if (ret == SUCCESS) {
		if (min_freq_hz > ULONG_MAX || min_freq_hz > target_freq_hz ||
		    target_freq_hz > max_freq_hz) {
			ret = -EINVAL;
		}
	}

	if (ret == SUCCESS) {
		if (max_freq_hz > ULONG_MAX) {
			max_freq_hz = ULONG_MAX;
		}

		if (target_freq_hz > ULONG_MAX) {
			target_freq_hz = ULONG_MAX;
		}

		if (!device_clk_set_freq(device, clk, min_freq_hz,
					 target_freq_hz, max_freq_hz)) {
			ret = -EINVAL;
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

static struct tisci_client tisci_msg_set_freq = {
	.handler	= tisci_msg_set_freq_handler,
	.subsystem	= SUBSYSTEM_PM,
};

static s32 tisci_msg_query_freq_handler(u32 *msg_recv)
{
	struct tisci_msg_query_freq_req *req =
		(struct tisci_msg_query_freq_req *) msg_recv;
	struct tisci_msg_query_freq_resp *resp =
		(struct tisci_msg_query_freq_resp *) msg_recv;
	struct device *device = NULL;
	u32 id = req->device;
	u64 min_freq_hz = req->min_freq_hz;
	u64 target_freq_hz = req->target_freq_hz;
	u64 max_freq_hz = req->max_freq_hz;
	dev_clk_idx_t clk;
	u64 freq_hz;
	s32 ret = SUCCESS;
	u32 flags = req->hdr.flags;

	/* Handle higher clock IDs */
	if (req->clk == 255UL) {
		clk = req->clk32;
	} else {
		clk = req->clk;
	}

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_QUERY_FREQ);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID,
		 id | ((u32) clk << TRACE_PM_MSG_CLK_ID_SHIFT));

	tisci_msg_clear_flags(&resp->hdr);

	ret = device_prepare_exclusive(req->hdr.host, id, NULL, &device);
	if (ret == SUCCESS) {
		if (min_freq_hz > ULONG_MAX || min_freq_hz > target_freq_hz ||
		    target_freq_hz > max_freq_hz) {
			ret = -EINVAL;
		}
	}

	if (ret == SUCCESS) {
		if (max_freq_hz > ULONG_MAX) {
			max_freq_hz = ULONG_MAX;
		}

		if (target_freq_hz > ULONG_MAX) {
			target_freq_hz = ULONG_MAX;
		}

		freq_hz = device_clk_query_freq(device, clk, min_freq_hz,
						target_freq_hz, max_freq_hz);

		resp->freq_hz = freq_hz;
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

static struct tisci_client tisci_msg_query_freq = {
	.handler	= tisci_msg_query_freq_handler,
	.subsystem	= SUBSYSTEM_PM,
};

static s32 tisci_msg_get_freq_handler(u32 *msg_recv)
{
	struct tisci_msg_get_freq_req *req =
		(struct tisci_msg_get_freq_req *) msg_recv;
	struct tisci_msg_get_freq_resp *resp =
		(struct tisci_msg_get_freq_resp *) msg_recv;
	struct device *device = NULL;
	u32 id = req->device;
	dev_clk_idx_t clk;
	s32 ret = SUCCESS;
	u32 flags = req->hdr.flags;

	/* Handle higher clock IDs */
	if (req->clk == 255UL) {
		clk = req->clk32;
	} else {
		clk = req->clk;
	}

	pm_trace(TRACE_PM_ACTION_MSG_RECEIVED, TISCI_MSG_GET_FREQ);
	pm_trace(TRACE_PM_ACTION_MSG_PARAM_DEV_CLK_ID,
		 id | ((u32) clk << TRACE_PM_MSG_CLK_ID_SHIFT));

	tisci_msg_clear_flags(&resp->hdr);

	ret = device_prepare_nonexclusive(req->hdr.host, id, NULL, &device);
	if (ret == SUCCESS) {
		resp->freq_hz = device_clk_get_freq(device, clk);
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

static struct tisci_client tisci_msg_get_freq = {
	.handler	= tisci_msg_get_freq_handler,
	.subsystem	= SUBSYSTEM_PM,
};

s32 pm_clock_message_init(void)
{
	s32 ret = SUCCESS;

	ret = tisci_user_client_register(TISCI_MSG_SET_CLOCK,
					 &tisci_msg_set_clock);

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_GET_CLOCK,
						 &tisci_msg_get_clock);
	}

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_SET_CLOCK_PARENT,
						 &tisci_msg_set_clock_parent);
	}

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_GET_CLOCK_PARENT,
						 &tisci_msg_get_clock_parent);
	}

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_GET_NUM_CLOCK_PARENTS,
						 &tisci_msg_get_num_clock_parents);
	}

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_SET_FREQ,
						 &tisci_msg_set_freq);
	}

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_QUERY_FREQ,
						 &tisci_msg_query_freq);
	}

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_GET_FREQ,
						 &tisci_msg_get_freq);
	}

	return ret;
}
#endif
