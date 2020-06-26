/*
 * RM Messaging Utilities
 *
 * Resource Manager messaging utility functions used to request actions
 * by entities outside of the RM subsystem
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_REQUEST_H
#define RM_REQUEST_H

#include <types/sbool.h>
#include <types/short_types.h>

/**
 * \brief Channelized firewall configuration for a single host
 *
 * \param fwl_id Channelized firewall ID
 *
 * \param fwl_ch Channelized firewall channel
 *
 * \param host Host to be programmed into firewall
 *
 * \return SUCCESS if firewall cfg succeeds, else -EFAIL
 */
#ifdef CONFIG_RM_LOCAL_SUBSYSTEM_REQUESTS
s32 rm_request_cfg_firewall(u16 fwl_id, u16 fwl_ch, u8 host);
#else
static inline s32 rm_request_cfg_firewall(u16	fwl_id __attribute__((unused)),
					  u16	fwl_ch __attribute__((unused)),
					  u8	host __attribute__((unused)))
{
	return SUCCESS;
}
#endif

/**
 * \brief Extended channelized firewall configuration for a resource type
 *
 * Utilizes the internal Secure extended firewall and RA ISC programming APIs to
 * configure the channelized firewalls for a resource type with real-time MMRs
 *
 * \param dev_id
 * SoC device ID associated with the IP whose firewall is being programmed
 *
 * \param utype
 * Unique resource assignment type
 *
 * \param fwl_id
 * Channelized firewall ID
 *
 * \param fwl_ch_offset
 * Channelized firewall channel offset for the resource
 *
 * \param res_index
 * Resource index who firewall is to be configured
 *
 * \param allow_dmsc
 * TRUE if DMSC must be added as an additional host in the firewall
 * permission slots.
 *
 * \param cfg_ra_isc
 * TRUE if the resource ia a RA ring and the ISC is to be programmed
 *
 * \param host_ro
 * TRUE if the host(s) programmed into the firewall are only allowed read only
 * permissions
 *
 * \return SUCCESS if firewall cfg succeeds, else -EFAIL
 */
#ifdef CONFIG_RM_LOCAL_SUBSYSTEM_REQUESTS
s32 rm_request_resasg_cfg_firewall_ext(u16 dev_id, u16 utype, u16 fwl_id, u16 fwl_ch_offset, u16 res_index, sbool allow_dmsc, sbool cfg_ra_isc, sbool host_ro);
#else
static inline s32 rm_request_resasg_cfg_firewall_ext(u16	dev_id __attribute__((unused)),
						     u16	utype __attribute__((unused)),
						     u16	fwl_id __attribute__((unused)),
						     u16	fwl_ch_offset __attribute__((unused)),
						     u16	res_index __attribute__((unused)),
						     sbool	allow_dmsc __attribute__((unused)),
						     sbool	cfg_ra_isc __attribute__((unused)),
						     sbool	host_ro __attribute__((unused)))
{
	return SUCCESS;
}
#endif

/**
 * \brief Configure ring VirtID
 *
 * \param dev_id Ring device ID
 *
 * \param index Ring index
 *
 * \param host Host to be programmed into VirtID
 *
 * \param virtid VirtID value to program
 *
 * \return SUCCESS if VirtID cfg succeeds, else -EFAIL
 */
#ifdef CONFIG_RM_LOCAL_SUBSYSTEM_REQUESTS
s32 rm_request_cfg_ring_virtid(u16 dev_id, u16 index, u8 host, u16 virtid);
#else
static inline s32 rm_request_cfg_ring_virtid(u16	dev_id __attribute__((unused)),
					     u16	index __attribute__((unused)),
					     u8		host __attribute__((unused)),
					     u16	virtid __attribute__((unused)))
{
	return SUCCESS;
}
#endif


#endif /* RM_REQUEST_H */
