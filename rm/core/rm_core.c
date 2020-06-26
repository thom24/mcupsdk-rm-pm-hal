/*
 * DMSC RM Core Utilities
 *
 * Resource Manager core utility functions used across RM internal subsystems
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/errno.h>
#include <types/address_types.h>
#include <types/devgrps.h>
#include <devices_internal.h>
#include <lib/trace.h>

#include <config.h>
#include <hosts.h>
#include <hosts_internal.h>

#include <tisci_provider/tisci.h>
#include <tisci/rm/tisci_rm_shared.h>
#include <tisci/rm/tisci_rm_core.h>
#include <osal/osal_core.h>
#include <osal/osal_msg.h>
#include <boardcfg/boardcfg_rm_data.h>
#include <resasg_types.h>

#include <rm_core.h>

#ifdef CONFIG_RM_IRQ
#include <rm_irq.h>
#endif
#ifdef CONFIG_RM_RA
#include <rm_ra.h>
#endif
#ifdef CONFIG_RM_UDMAP
#include <rm_udmap.h>
#endif
#ifdef CONFIG_RM_PROXY
#include <rm_proxy.h>
#endif

/**
 * \brief Resource assignment array indexer
 *
 * \param max_cnt Maximum number of indices.  Must be set equal to the maximum
 *                number of UTYPEs in the SoC
 *
 * \param valid_cnt Number of valid indices in the indexer.  May be less than
 *                  max_cnt if the resource assignment array does not have at
 *                  least one entry per UTYPE
 *
 * \param indices Array of resource assignment index elements sized equal to
 *                the number of UTYPEs in the SoC
 */
struct rm_resasg_utype_indexer {
	u8			max_cnt;
	u8			valid_cnt;
	struct rm_resasg_index	indices[RESASG_UTYPE_CNT];
};

struct rm_resasg_utype_indexer resasg_indexer = {
	.max_cnt	= RESASG_UTYPE_CNT,
	.valid_cnt	= 0u,
};

static sbool region_mapped = SFALSE;

/**
 * \brief Populate the resasg indexer
 *
 * Parse the RM boardcfg resasg array to populate the resasg indexer
 */
static s32 core_resasg_create_index(void)
{
	u16 resasg_size;
	const struct boardcfg_rm_resasg_entry *resasg;
	u16 resasg_entry_cnt;
	u16 i, j;
	s32 r = SUCCESS;

	/*
	 * Only index the resource assignment list once.  An indexed list
	 * will have valid_cnt > 0
	 */
	if (resasg_indexer.valid_cnt == 0U) {
		resasg_size = boardcfg_get_rm_resasg_size();
		resasg = boardcfg_get_rm_resasg();
		if (resasg == NULL) {
			r = -ECONFUSED;
		} else {
			resasg_entry_cnt = resasg_size /
					   sizeof(struct boardcfg_rm_resasg_entry);

			/* Initialize the resasg type indices */
			for (i = 0u; i < resasg_indexer.max_cnt; i++) {
				resasg_indexer.indices[i].resasg_indexp = NULL;
				resasg_indexer.indices[i].utype = 0xFFFFu;
				resasg_indexer.indices[i].len = 0u;
			}

			/* Manually populate first entry of index */
			resasg_indexer.indices[0u].resasg_indexp = &resasg[0u];
			resasg_indexer.indices[0u].utype = resasg[0u].type;
			resasg_indexer.indices[0u].len = 1u;
			j = 0u;

			for (i = 1u; i < resasg_entry_cnt; i++) {
				if (resasg[i].type == resasg_indexer.indices[j].utype) {
					resasg_indexer.indices[j].len++;
				} else {
					j++;
					resasg_indexer.indices[j].resasg_indexp = &resasg[i];
					resasg_indexer.indices[j].utype = resasg[i].type;
					resasg_indexer.indices[j].len = 1u;
				}
			}

			/* Store number of unique indexes found for the resasg list */
			resasg_indexer.valid_cnt = ++j;

			if (resasg_indexer.valid_cnt > resasg_indexer.max_cnt) {
				r = -ECONFUSED;
			}
		}
	}
	return r;
}

/**
 * \brief Retrieve a resource range from the boardcfg resasg list
 *
 * Retrieves the resource range defined in the boardcfg resource assignment
 * list for the provided host and unique resource type combination.
 *
 * Will return the range start and number as zeroes if the host and type
 * combination is not found in the resource list.  This provides a common
 * response mechanism across SoCs.
 *
 * \param host
 * Host ID
 *
 * \param utype
 * Unique resource assignment type
 *
 * \param start
 * Pointer to range start variable.  Returns the range start value.  Value
 * is zero if the utype to host assignment is not found.
 *
 * \param num
 * Pointer to range number variable.  Returns the range number value.  Value
 * is zero if the utype to host assignment is not found.
 *
 * \param start_sec
 * Pointer to secondary_range start variable.  Returns the secondary range start
 * value.  Value is zero if the utype to host assignment is not found or if a
 * secondary range does not exist for the resource
 *
 * \param num_sec
 * Pointer to secondary range number variable.  Returns the secondary range
 * number value.  Value is zero if the utype to host assignment is not found or
 * if a secondary range does not exist for the resource.
 */
static void core_resasg_get_range(u8 host, u16 utype, u16 *start, u16 *num,
				  u16 *start_sec, u16 *num_sec)
{
	const struct rm_resasg_index *utype_index;
	u16 i;

	utype_index = rm_core_resasg_get_utype_index(utype);

	/*
	 * No error if host + utype combination not found in the
	 * resource assignment list provided via board cfg.  In this
	 * case, just return start and num as zeroes to allow for a
	 * common response mechanism across SoCs
	 */
	*start = 0U;
	*num = 0U;
	*start_sec = 0U;
	*num_sec = 0U;

	/*
	 * Not a failure if utype is not found.  Just means boardcfg
	 * does not assign any resources to the utype
	 */
	if (utype_index != NULL) {
		for (i = 0u; i < utype_index->len; i++) {
			if ((utype_index->resasg_indexp[i].host_id == host) &&
			    (utype_index->resasg_indexp[i].type == utype)) {
				/* Populate first range then secondary range */
				if (*num == 0U) {
					*start = utype_index->resasg_indexp[i].start_resource;
					*num = utype_index->resasg_indexp[i].num_resource;
				} else {
					*start_sec = utype_index->resasg_indexp[i].start_resource;
					*num_sec = utype_index->resasg_indexp[i].num_resource;
					break;
				}
			}
		}
	}
}

/**
 * \brief Validate resource assignment type
 *
 * Checks the resource assignment type to make sure within range of
 * valid type values
 *
 * \param type
 * Resource assignment type
 *
 * \param trace_action RA action to trace
 *
 * \return SUCCESS if type is valid, else, -EINVAL
 */
static s32 core_resasg_validate_type(u16 type, u8 trace_action)
{
	s32 r = SUCCESS;
	u16 mask = RESASG_TYPE_MASK >> RESASG_TYPE_SHIFT;

	/* Type cannot be greater than mask width */
	if (type > mask) {
		trace_action |= TRACE_RM_ACTION_FAIL;
		r = -EINVAL;
	}

	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_RESOURCE_GET_TYPE,
		     type);

	return r;
}

/**
 * \brief Validate resource assignment subtype
 *
 * Checks the resource assignment subtype to make sure within range of
 * valid type values
 *
 * \param subtype
 * Resource assignment subtype
 *
 * \param trace_action RA action to trace
 *
 * \return SUCCESS if subtype is valid, else, -EINVAL
 */
static s32 core_resasg_validate_subtype(u16 subtype, u8 trace_action)
{
	s32 r = SUCCESS;
	u16 mask = RESASG_SUBTYPE_MASK >> RESASG_SUBTYPE_SHIFT;

	/* Subtype cannot be greater than mask width */
	if (subtype > mask) {
		trace_action |= TRACE_RM_ACTION_FAIL;
		r = -EINVAL;
	}

	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_RESOURCE_GET_SUBTYPE,
		     subtype);

	return r;
}

/**
 * \brief Resource range retrieval message handler
 *
 * \param msg_recv TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
static s32 core_get_resource_range_msg_handler(u32 *msg_recv)
{
	s32 r = SUCCESS;
	struct tisci_msg_rm_get_resource_range_req *msg =
		(struct tisci_msg_rm_get_resource_range_req *) msg_recv;
	struct tisci_msg_rm_get_resource_range_resp *resp =
		(struct tisci_msg_rm_get_resource_range_resp *) msg;
	u8 host;
	u16 utype;
	sbool type_found;
	u8 trace_action = TRACE_RM_ACTION_RESOURCE_GET;

	if ((msg->secondary_host != TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST) &&
	    (msg->secondary_host != HOST_ID_ALL)) {
		r = osal_core_verify_host_id(msg->secondary_host);
		if (r != SUCCESS) {
			trace_action |= TRACE_RM_ACTION_FAIL;
		}
	}

	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_RESOURCE_GET_SECONDARY_HOST,
		     msg->secondary_host);

	if (r == SUCCESS) {
		r = core_resasg_validate_type(msg->type, trace_action);
	}
	if (r == SUCCESS) {
		r = core_resasg_validate_subtype(msg->subtype, trace_action);
	}

	if (r == SUCCESS) {
		host = msg->secondary_host ==
		       TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST ?
		       msg->hdr.host :
		       msg->secondary_host;
		utype = RESASG_UTYPE(msg->type, msg->subtype);
		type_found = SFALSE;

		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_RESASG_UTYPE,
			     utype);

#ifdef CONFIG_RM_IRQ
		if (type_found == SFALSE) {
			type_found = rm_irq_is_managed_resasg_utype(utype);
		}
#endif
#ifdef CONFIG_RM_RA
		if (type_found == SFALSE) {
			type_found = rm_ra_is_managed_resasg_utype(utype);
		}
#endif
#ifdef CONFIG_RM_UDMAP
		if (type_found == SFALSE) {
			type_found = rm_udmap_is_managed_resasg_utype(utype);
		}
#endif
#ifdef CONFIG_RM_PROXY
		if (type_found == SFALSE) {
			type_found = rm_proxy_is_managed_resasg_utype(utype);
		}
#endif

		if (type_found == STRUE) {
			core_resasg_get_range(host, utype,
					      &resp->range_start,
					      &resp->range_num,
					      &resp->range_start_sec,
					      &resp->range_num_sec);
		} else {
			/*
			 * Do not return failure so there's a common response
			 * mechanism even for valid resource types not used
			 * by an SoC.  Just zero the response range_start and
			 * range_num fields.
			 */
			resp->range_start = 0u;
			resp->range_num = 0u;
			resp->range_start_sec = 0u;
			resp->range_num_sec = 0u;
		}
	}

	if (r == SUCCESS) {
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_RESOURCE_GET_RANGE_START,
			     resp->range_start);
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_RESOURCE_GET_RANGE_NUM,
			     resp->range_num);
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_RESOURCE_GET_RANGE_START_SEC,
			     resp->range_start_sec);
		rm_trace_sub(trace_action,
			     TRACE_RM_SUB_ACTION_RESOURCE_GET_RANGE_NUM_SEC,
			     resp->range_num_sec);
	}

	r = rm_core_send_response((struct tisci_header *) resp,
				  sizeof(*resp),
				  r);

	return r;
}

static struct tisci_client tisci_msg_rm_core_get_resource_range = {
	.handler	= core_get_resource_range_msg_handler,
	.subsystem	= SUBSYSTEM_RM,
};

s32 rm_core_init(void)
{
	s32 r = SUCCESS;

	r = core_resasg_create_index();
	if (r == SUCCESS) {
		r = tisci_user_client_register(TISCI_MSG_RM_GET_RESOURCE_RANGE,
					       &tisci_msg_rm_core_get_resource_range);
	}

	if (r != SUCCESS) {
		rm_trace_sub(TRACE_RM_ACTION_RM_CORE_INIT |
			     TRACE_RM_ACTION_FAIL, 0U, 0U);
	}

	return r;
}

mapped_addr_t rm_core_map_region(soc_phys_addr_t phy_addr)
{
	/* Take region mapped lock. */
	if (region_mapped == SFALSE) {
		region_mapped = STRUE;
	}

	/**
	 * TBD - we need RAT if the mapping is not available.
	 *
	 * NOTE: we will misuse pm/soc/k3m/dmsc.c configuration for now:
	 *
	 * ~~~
	 * Physical address | mapped address | Size
	 * ----------------------------------------
	 * 0x00000000ULL    | 0x60000000UL   | 512MB
	 * 0x20000000ULL    | 0x80000000UL   | 512MB
	 * 0x40000000ULL    | 0xa0000000UL   | 512MB
	 * ~~~
	 *
	 * *NOTE*: This wont work for firewall setup and separated ops.
	 */
	return soc_phys_low_u32(phy_addr) + CONFIG_ADDR_REMAP_OFFSET;
}

void rm_core_unmap_region(void)
{
	/* Release region mapped lock. */
	if (region_mapped == STRUE) {
		region_mapped = SFALSE;
	}

	/**
	 * TBD - we need RAT if the mapping is not available - Empty function
	 * for now.
	 */
	return;
}

s32 rm_core_send_response(struct tisci_header	*resp,
			  u32			size,
			  s32			status)
{
	s32 r = SUCCESS;

	/*
	 * Response reuses same buffer as receive.  Received message header is
	 * untouched at this point so verify the ACK on process flag is set
	 * before sending the response.
	 */
	if ((resp->flags & TISCI_MSG_FLAG_AOP) != 0UL) {
		tisci_msg_clear_flags(resp);
		if (status == SUCCESS) {
			tisci_msg_set_ack_resp(resp);
		} else {
			tisci_msg_set_nak_resp(resp);
		}

		r = osal_msg_response((u32 *) resp, size);
	}

	/*
	 * Avoid overwriting status of calling message handler if the message
	 * handler has a failure status.
	 */
	if (status != SUCCESS) {
		r = status;
	}

	return r;
}

const struct rm_resasg_index *rm_core_resasg_get_utype_index(u16 utype)
{
	const struct rm_resasg_index *cur_index = NULL;
	u16 lower, upper, current, cnt;
	sbool found = SFALSE;

	lower = 0u;
	upper = resasg_indexer.valid_cnt - 1u;
	cnt = resasg_indexer.valid_cnt;

	/*
	 * Bounds check the search for failure robustness.  Make sure lower
	 * and upper do not go outside searchable range.  Also, search should
	 * be log(valid_cnt) but fail out after valid_cnt iterations to avoid
	 * infinite loop in case of data corruption
	 */
	while ((lower <= upper) &&
	       (lower < resasg_indexer.valid_cnt) &&
	       (upper < resasg_indexer.valid_cnt) &&
	       (cnt > 0u)) {
		current = (lower + upper) / (2u);
		cur_index = &resasg_indexer.indices[current];
		if (cur_index->utype == utype) {
			found = STRUE;
			break;
		} else {
			if (cur_index->utype < utype) {
				lower = current + (1u);
			} else {
				upper = current - (1u);
			}
		}
		cnt--;
	}

	if (found == SFALSE) {
		cur_index = NULL;
	}

	return cur_index;
}

s32 rm_core_resasg_validate_resource(u8 host, u16 utype, u16 res_index)
{
	s32 r = -EINVAL;
	u16 start, start_sec;
	u16 num, num_sec;
	u8 trace_action = TRACE_RM_ACTION_RESASG_VALIDATE_RESOURCE;

	core_resasg_get_range(host, utype, &start, &num, &start_sec, &num_sec);

	/*
	 * Returned num will be zero if range is not found for the host
	 * and utype combination
	 */
	if (((res_index >= start) && (res_index < (start + num))) ||
	    ((res_index >= start_sec) && (res_index < (start_sec + num_sec)))) {
		r = SUCCESS;
	}

	if (r != SUCCESS) {
		/* Check if resource is assigned in "all hosts" range */
		core_resasg_get_range(HOST_ID_ALL, utype, &start, &num,
				      &start_sec, &num_sec);

		if (((res_index >= start) &&
		     (res_index < (start + num))) ||
		    ((res_index >= start_sec) &&
		     (res_index < (start_sec + num_sec)))) {
			r = SUCCESS;
		}
	}

	if (r != SUCCESS) {
		trace_action |= TRACE_RM_ACTION_FAIL;
	}

	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_INDEX,
		     res_index);
	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_RESASG_UTYPE,
		     utype);
	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_RESASG_VALIDATE_HOST,
		     host);

	return r;
}

#ifdef CONFIG_TRACE
s32 rm_core_validate_devgrp(u16 dev_id, devgrp_t dev_devgrp)
#else
s32 rm_core_validate_devgrp(u16 dev_id __attribute__((unused)), devgrp_t dev_devgrp)
#endif
{
	s32 r;
	devgrp_t current_devgrp;
	u8 trace_action = TRACE_RM_ACTION_DEVGRP_VALIDATE;

	r = boardcfg_get_rm_devgrp(&current_devgrp);

	if (r == SUCCESS) {
		r = is_devgrp(dev_devgrp, current_devgrp);
	}

	if (r != SUCCESS) {
		trace_action |= TRACE_RM_ACTION_FAIL;
	}

	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_DEVGRP_BOARDCFG,
		     current_devgrp);
	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_DEVGRP_DEVICE,
		     dev_devgrp);
	rm_trace_sub(trace_action,
		     TRACE_RM_SUB_ACTION_DEVICE_ID,
		     dev_id);

	return r;
}

sbool rm_core_param_is_valid(u32 valid_params, u32 param_mask)
{
	sbool r = SFALSE;

	if ((valid_params & param_mask) != 0u) {
		r = STRUE;
	}

	return r;
}
