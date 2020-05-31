/*
 * DMSC RM Core Utilities
 *
 * Resource Manager core utility functions used across RM internal subsystems
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_CORE_H
#define RM_CORE_H

#include <types/sbool.h>
#include <types/short_types.h>
#include <types/address_types.h>
#include <types/devgrps.h>

#include <tisci/tisci_protocol.h>

#include <boardcfg/boardcfg_rm_data.h>

/**
 * \brief Register field make
 *
 * Inserts a value into a register field preserving all other bits
 *
 * \param shift
 * Register field shift offset
 *
 * \param mask
 * Register field mask
 *
 * \param val
 * Field value
 *
 * \return
 * Extracted register field
 */
static inline u32 rm_fmk(u32 shift, u32 mask, u32 val)
{
	return (val << shift) & mask;
}

/**
 * \brief Register field extract
 *
 * Extracts a value from a register field excluding all other bits
 *
 * \param reg
 * Register value
 *
 * \param shift
 * Register field shift offset
 *
 * \param mask
 * Register field mask
 *
 * \return
 * Extracted register field
 */
static inline u32 rm_fext(u32 reg, u32 shift, u32 mask)
{
	return (reg & mask) >> shift;
}

/**
 * \brief Initializes core RM
 *
 * Initializes core RM
 *
 * \return SUCCESS if init completed successfully else error
 */
s32 rm_core_init(void);

/**
 * \brief RAT mapping function for RM drivers
 *
 * Returns the RAT mapped address for the input physical address
 *
 * \param phy_addr
 * Physical address to map
 *
 * \return
 * RAT mapped address
 */
mapped_addr_t rm_core_map_region(soc_phys_addr_t phy_addr);

/**
 * \brief RAT unmapping function for RM drivers
 *
 * Unmaps a RAT region used to map a physical address.
 *
 * TBD - Input will be the RAT mapped address once RAT map and unmap is fully
 * implemented
 */
void rm_core_unmap_region(void);

/**
 * \brief Sends TISCI response message
 *
 * Uses the OSAL layer to send the TISCI response message created
 * by RM drivers
 *
 * \param resp
 * Pointer to the response message created by the RM driver
 *
 * \param size
 * Size of the TISCI response message in bytes
 *
 * \param status
 * Current status of the message handler.  This parameter will be used as the
 * return status for this function if the passed status is a failure.  This is
 * done to avoid overriding the caller's status.
 *
 * \return
 * Response code from the OSAL layer after sending the message or the passed
 * status if the passed status is a failure.
 */
s32 rm_core_send_response(struct tisci_header *resp, u32 size, s32 status);

/**
 * \brief Configure the channelized firewalls for a resource type
 *
 * Utilizes the internal Secure firewall and RA ISC programming APIs to
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
s32 rm_core_resasg_cfg_firewall(u16 dev_id, u16 utype, u16 fwl_id, u16 fwl_ch_offset, u16 res_index, sbool allow_dmsc, sbool cfg_ra_isc, sbool host_ro);

/**
 * \brief Validates a resource against the board cfg data
 *
 * Validates a resource index of the provided unique type is mapped to the
 * specified host in the stored board configuration data.
 *
 * \param host
 * Host ID
 *
 * \param utype
 * Unique resource assignment type
 *
 * \param res_index
 * Index of resource
 */
s32 rm_core_resasg_validate_resource(u8 host, u16 utype, u16 res_index);

/**
 * \brief Validates a device's devgrp against the current devgrp
 *
 * Validates a device's devgrp against the current devgrp specified in the RM
 * board configuration.
 *
 * \param dev_id
 * SoC device ID associated with the IP being device group validated
 *
 * \param dev_devgrp
 * Device devgrp
 *
 * \return SUCCESS if device devgrp matches current devgrp, else -EINVAL
 */
s32 rm_core_validate_devgrp(u16 dev_id, devgrp_t dev_devgrp);

/**
 * \brief Check if a parameter is valid
 *
 * Uses a valid_params field and the bit mask for a paramter to check if a
 * parameter is valid.
 *
 * \param valid_params Valid parameter bit field
 *
 * \param param_mask Bit mask for the parameter to validate
 *
 * \return STRUE if parameter is valid, else SFALSE
 */
sbool rm_core_param_is_valid(u32 valid_params, u32 param_mask);

#endif /* RM_CORE_H */
