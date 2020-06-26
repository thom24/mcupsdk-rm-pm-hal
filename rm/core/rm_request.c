/*
 * RM Messaging Utilities
 *
 * Resource Manager messaging utility functions used to request actions
 * by entities outside of the RM subsystem
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/errno.h>
#include <lib/trace.h>
#include <types/fterr.h>

#include <config.h>

#include <rm_core.h>
#include <rm_request.h>

#ifdef CONFIG_RM_LOCAL_SUBSYSTEM_REQUESTS
#include <security/rm_int_firewall.h>
#include <security/rm_int_isc.h>

s32 rm_request_cfg_firewall(u16 fwl_id, u16 fwl_ch, u8 host)
{
	s32 r = SUCCESS;
	u8 hosts[FWL_MAX_PRIVID_SLOTS];

	hosts[0U] = host;
	if (sec_rm_fwl_set_perm(fwl_id,
				fwl_ch,
				hosts,
				1U) != EFTOK) {
		r = -EFAIL;
	}

	return r;
}

s32 rm_request_resasg_cfg_firewall_ext(u16 dev_id, u16 utype, u16 fwl_id,
				       u16 fwl_ch_offset, u16 res_index,
				       sbool allow_dmsc, sbool cfg_ra_isc,
				       sbool host_ro)
{
	s32 r = SUCCESS;
	const struct rm_resasg_index *utype_index;
	const struct boardcfg_rm_resasg_entry *entry = NULL;
	u16 i;
	u16 res_end;
	u8 hosts[FWL_MAX_PRIVID_SLOTS];
	u8 write_perms[FWL_MAX_PRIVID_SLOTS] = { FT_TRUE, FT_TRUE, FT_TRUE };
	u8 n_slots = 0U;
	u16 fwl_ch;
	u8 trace_action = TRACE_RM_ACTION_RESASG_FIREWALL_CFG;

	utype_index = rm_core_resasg_get_utype_index(utype);

	/*
	 * Not a failure if utype is not found.  Just means boardcfg
	 * does not assign any resources to the utype
	 */
	if (utype_index != NULL) {
		for (i = 0U; i < utype_index->len; i++) {
			entry = &utype_index->resasg_indexp[i];
			res_end = entry->start_resource + entry->num_resource;
			if ((res_index >= entry->start_resource) &&
			    (res_index < res_end)) {
				if (host_ro == STRUE) {
					write_perms[n_slots] = FT_FALSE;
				}
				hosts[n_slots++] = entry->host_id;
			}
		}

		/*
		 * Not an error if resource is not found in matching utype
		 * list.  Just means boardcfg does not specify assignment
		 * for the resource
		 */
		if (n_slots > 0U) {
			fwl_ch = res_index + fwl_ch_offset;

			if (hosts[0U] == HOST_ID_ALL) {
				if (sec_rm_fwl_allow_all(fwl_id, fwl_ch) !=
				    EFTOK) {
					r = -EFAIL;
				}
			} else {
				if (allow_dmsc == STRUE) {
					hosts[n_slots++] = HOST_ID_DMSC;
				}

				if (sec_rm_fwl_set_perm_ext(fwl_id, fwl_ch,
							    hosts, n_slots,
							    write_perms) !=
				    EFTOK) {
					r = -EFAIL;
				} else {
					if (cfg_ra_isc == STRUE) {
						if (sec_rm_ra_isc_set_perm(dev_id, res_index,
									   hosts[0U]) !=
						    EFTOK) {
							r = -EFAIL;
						}
					}
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
				     TRACE_RM_SUB_ACTION_RESASG_FWL_ID,
				     fwl_id);
			rm_trace_sub(trace_action,
				     TRACE_RM_SUB_ACTION_RESASG_FWL_CH,
				     fwl_ch);
		}
	}

	return r;
}

s32 rm_request_cfg_ring_virtid(u16 dev_id, u16 index, u8 host, u16 virtid)
{
	s32 r = SUCCESS;

	if (sec_rm_ra_isc_set_virtid(dev_id, index, host, virtid) != EFTOK) {
		r = -EFAIL;
	}

	return r;
}
#endif
