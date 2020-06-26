/*
 * Proxy
 *
 * proxy management infrastructure
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/sbool.h>
#include <types/short_types.h>
#include <types/address_types.h>
#include <types/errno.h>
#include <lib/io.h>
#include <lib/trace.h>

#include <config.h>
#include <hosts.h>

#include <osal/osal_core.h>
#include <tisci_provider/tisci.h>
#include <tisci/rm/tisci_rm_proxy.h>

#include <rm_core.h>
#include <rm_request.h>
#include <rm_proxy.h>

#include <proxy_inst.h>
#include <proxy_cfg.h>

/*
 * Proxy Configuration Register Macros
 */
#define PROXY_CFG_PROXY_EVT_REG                    (0x00000000U)
#define PROXY_CFG_MULTIPLIER                       (0x00001000U)

/*
 * Proxy Register Fields
 */
#define PROXY_EVENT_MASK                           (0x0000FFFFU)
#define PROXY_EVENT_SHIFT                          (0x00000000U)
#define PROXY_EVENT_RESETVAL                       (0x0000FFFFU)

/**
 * \brief Get proxy instance mapped to provided device ID
 *
 * \param id proxy device ID
 *
 * \param trace_action proxy action to trace
 *
 * \return Pointer to proxy instance, NULL if no instance mapped to ID
 */
static const struct proxy_instance *proxy_get_inst(u16 id, u8 trace_action)
{
	const struct proxy_instance *inst = NULL;
	u32 i;
	/* Local version to satisfy MISRA */
	u8 local_trace_action = trace_action;

	for (i = 0U; i < PROXY_INST_COUNT; i++) {
		if (proxy_inst[i].id == id) {
			inst = &proxy_inst[i];

			if (rm_core_validate_devgrp(inst->id, inst->devgrp) !=
			    SUCCESS) {
				/*
				 * Return NULL instance if instance devgrp
				 * doesn't align with boardcfg devgrp
				 */
				inst = NULL;
			}
			break;
		}
	}

	if (inst == NULL) {
		local_trace_action |= TRACE_RM_ACTION_FAIL;
	}

	rm_trace_sub(local_trace_action,
		     TRACE_RM_SUB_ACTION_DEVICE_ID,
		     id);

	return inst;
}

/**
 * \brief Get proxy cfg region address offset
 *
 * \param index Proxy index
 *
 * \return Offset of proxy cfg region
 */
static u32 proxy_get_cfg_offset(u16 index)
{
	return (u32) index * PROXY_CFG_MULTIPLIER;
}

/**
 * \brief Validate proxy index against the board cfg resasg data
 *
 * \param inst proxy instance
 *
 * \param host Host ID
 *
 * \param index Proxy index
 *
 * \param utype Returns the proxy utype if not NULL
 *
 * \param trace_action proxy action to trace
 *
 * \return SUCCESS if proxy index is valid, else -EINVAL
 */
static s32 proxy_check_index_range(
	const struct proxy_instance	*inst,
	u8				host,
	u16				index,
	u16				*utype,
	u8				trace_action)
{
	s32 r = -EINVAL;
	/* Local version to satisfy MISRA */
	u8 local_trace_action = trace_action;

	if (index < inst->n_proxies) {
		r = rm_core_resasg_validate_resource(
			host,
			inst->proxy_utype,
			index);
	}

	if (r != SUCCESS) {
		local_trace_action |= TRACE_RM_ACTION_FAIL;
	} else {
		if (utype != NULL) {
			*utype = inst->proxy_utype;
		}
	}

	rm_trace_sub(local_trace_action,
		     TRACE_RM_SUB_ACTION_INDEX,
		     index);

	return r;
}

/**
 * \brief Gets the global event in a proxy event register
 *
 * \param inst proxy instance
 *
 * \param oes_index OES event index
 *
 * \return Global event value within the OES index's event register
 */
static u16 proxy_get_evt(const struct proxy_instance *inst, u16 oes_index)
{
	mapped_addr_t maddr;
	u32 evt_addr;
	u32 evt_reg;

	maddr = rm_core_map_region(inst->cfg->base);
	evt_addr = maddr + proxy_get_cfg_offset(oes_index) +
		   PROXY_CFG_PROXY_EVT_REG;

	evt_reg = readl(evt_addr);
	rm_core_unmap_region();

	return (u16) rm_fext(evt_reg, PROXY_EVENT_SHIFT, PROXY_EVENT_MASK);
}

/**
 * \brief Gets the global event within a proxy's OES register
 *
 * \param host Host ID of processing entity attempting to get the event.
 *
 * \param id SoC device ID in which the proxy OES index resides
 *
 * \param oes_index Flattened OES register index.
 *
 * \param evt Returns the global event value within the OES index's OES register
 *
 * \return SUCCESS if global event retrieved successfully, else error
 */
static s32 proxy_get_ring_evt(u8 host, u16 id, u16 oes_index, u16 *evt)
{
	s32 r = SUCCESS;
	const struct proxy_instance *inst = NULL;
	u16 utype;
	u8 trace_action = TRACE_RM_ACTION_PROXY_OES_GET;

	if (evt == NULL) {
		r = -EINVAL;
	} else {
		inst = proxy_get_inst(id, trace_action);
		if (inst == NULL) {
			r = -EINVAL;
		}
	}

	if (r == SUCCESS) {
		if (oes_index < inst->n_proxies) {
			r = proxy_check_index_range(inst, host,
						    oes_index, &utype,
						    trace_action);
		} else {
			trace_action |= TRACE_RM_ACTION_FAIL;
			r = -EINVAL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_OES_REG_INDEX,
			     oes_index);
	}

	if (r == SUCCESS) {
		/* Configure cfg channelized firewall */
		r = rm_request_resasg_cfg_firewall_ext(
			inst->id,
			utype,
			inst->cfg->fwl_id,
			inst->cfg->fwl_ch_start,
			oes_index,
			STRUE,
			SFALSE,
			STRUE);
	}

	if (r == SUCCESS) {
		*evt = proxy_get_evt(inst, oes_index);
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_EVENT,
			     *evt);
	}

	return r;
}

/**
 * \brief Sets the global event within a proxy's OES register
 *
 * \param host Host ID of processing entity attempting to set the event.
 *
 * \param id SoC device ID in which the proxy OES index resides
 *
 * \param oes_index Flattened OES register index.
 *
 * \param evt Global event value to program into the OES index's register
 *
 * \return SUCCESS if global event programmed successfully, else error
 */
static s32 proxy_set_ring_evt(u8 host, u16 id, u16 oes_index, u16 evt)
{
	s32 r = SUCCESS;
	const struct proxy_instance *inst = NULL;
	mapped_addr_t maddr;
	u16 utype;
	u32 evt_reg;
	u32 evt_addr;
	u8 trace_action = TRACE_RM_ACTION_PROXY_OES_SET;

	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_EVENT,
		     evt);

	inst = proxy_get_inst(id, trace_action);
	if (inst == NULL) {
		r = -EINVAL;
	}

	if (r == SUCCESS) {
		if (oes_index < inst->n_proxies) {
			r = proxy_check_index_range(inst, host,
						    oes_index, &utype,
						    trace_action);
		} else {
			trace_action |= TRACE_RM_ACTION_FAIL;
			r = -EINVAL;
		}

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_OES_REG_INDEX,
			     oes_index);
	}

	if (r == SUCCESS) {
		/* Configure cfg channelized firewall */
		r = rm_request_resasg_cfg_firewall_ext(
			inst->id,
			utype,
			inst->cfg->fwl_id,
			inst->cfg->fwl_ch_start,
			oes_index,
			STRUE,
			SFALSE,
			STRUE);
	}

	if (r == SUCCESS) {
		/* oes_index verified already at this point */
		maddr = rm_core_map_region(inst->cfg->base);
		evt_reg = rm_fmk(PROXY_EVENT_SHIFT,
				 PROXY_EVENT_MASK, evt);
		evt_addr = maddr + proxy_get_cfg_offset(oes_index) +
			   PROXY_CFG_PROXY_EVT_REG;

		if (writel_verified(evt_reg, evt_addr) != SUCCESS) {
			/* Readback of write failed: halt */
			r = -EFAILVERIFY;
		}
		rm_core_unmap_region();
	}

	return r;
}

/**
 * \brief proxy configure message handler
 *
 * \param msg_recv TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
static s32 proxy_cfg_msg_handler(u32 *msg_recv)
{
	s32 r = SUCCESS;
	struct tisci_msg_rm_proxy_cfg_req *msg =
		(struct tisci_msg_rm_proxy_cfg_req *) msg_recv;
	struct tisci_msg_rm_proxy_cfg_resp *resp =
		(struct tisci_msg_rm_proxy_cfg_resp *) msg_recv;
	const struct proxy_instance *inst = NULL;
	u16 utype;
	u8 trace_action = TRACE_RM_ACTION_PROXY_CFG;

	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_VALID_PARAM_HI,
		     ((msg->valid_params >> 16U) & TRACE_DEBUG_SUB_ACTION_VAL_MASK));
	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_VALID_PARAM_LO,
		     (msg->valid_params & TRACE_DEBUG_SUB_ACTION_VAL_MASK));

	inst = proxy_get_inst(msg->nav_id, trace_action);
	if (inst == NULL) {
		r = -EINVAL;
	}

	if (r == SUCCESS) {
		r = proxy_check_index_range(inst, msg->hdr.host,
					    msg->index, &utype,
					    trace_action);
	}

	if (r == SUCCESS) {
		/* Configure proxy target0_data channelized firewall */
		r = rm_request_resasg_cfg_firewall_ext(
			inst->id,
			utype,
			inst->target0_data->fwl_id,
			inst->target0_data->fwl_ch_start,
			msg->index,
			SFALSE,
			SFALSE,
			SFALSE);
	}

	if (r == SUCCESS) {
		/* Configure cfg channelized firewall */
		r = rm_request_resasg_cfg_firewall_ext(
			inst->id,
			utype,
			inst->cfg->fwl_id,
			inst->cfg->fwl_ch_start,
			msg->index,
			STRUE,
			SFALSE,
			STRUE);
	}

	r = rm_core_send_response((struct tisci_header *) resp,
				  (u32) sizeof(*resp),
				  r);

	return r;
}

static struct tisci_client tisci_msg_rm_proxy_cfg = {
	.handler	= proxy_cfg_msg_handler,
	.subsystem	= SUBSYSTEM_RM,
};

sbool rm_proxy_is_managed_resasg_utype(u16 utype)
{
	sbool r = SFALSE;
	u16 i;

	for (i = 0U; i < PROXY_INST_COUNT; i++) {
		if (utype == proxy_inst[i].proxy_utype) {
			r = STRUE;
			break;
		}
	}

	return r;
}

s32 rm_proxy_init(void)
{
	s32 r = SUCCESS;
	u16 i;

	for (i = 0U; i < PROXY_INST_COUNT; i++) {
		if ((rm_core_validate_devgrp(proxy_inst[i].id,
					     proxy_inst[i].devgrp) ==
		     SUCCESS) &&
		    (proxy_inst[i].initialized == SFALSE)) {
#ifdef CONFIG_RM_IRQ
			if (r == SUCCESS) {
				proxy_inst[i].oes_handler.oes_get = proxy_get_ring_evt;
				proxy_inst[i].oes_handler.oes_set = proxy_set_ring_evt;

				r = rm_irq_oes_src_register(proxy_inst[i].id,
							    &proxy_inst[i].oes_handler);
			}
#endif

			if (r != SUCCESS) {
				break;
			} else {
				proxy_inst[i].initialized = STRUE;
			}
		}
	}

	if (r == SUCCESS) {
		r = tisci_user_client_register(TISCI_MSG_RM_PROXY_CFG,
					       &tisci_msg_rm_proxy_cfg);
	}

	if (r != SUCCESS) {
		rm_trace_sub((u32) (TRACE_RM_ACTION_PROXY_INIT |
				    TRACE_RM_ACTION_FAIL), 0U, 0U);
	}

	return r;
}

s32 rm_proxy_deinit(devgrp_t devgrp)
{
	s32 r = -EFAIL;
	u8 i;

	for (i = 0U; i < PROXY_INST_COUNT; i++) {
		if ((rm_core_validate_devgrp(proxy_inst[i].id, proxy_inst[i].devgrp) ==
		     SUCCESS) &&
		    (proxy_inst[i].initialized == STRUE) &&
		    (proxy_inst[i].devgrp == devgrp)) {
			proxy_inst[i].initialized = SFALSE;
			r = SUCCESS;
		}
	}

	return r;
}
