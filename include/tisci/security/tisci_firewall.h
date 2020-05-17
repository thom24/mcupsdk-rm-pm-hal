/*
 * System Firmware
 *
 * TISCI Data structures and macros for firewall messages
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef TISCI_FIREWALL_H_
#define TISCI_FIREWALL_H_

#include <types/short_types.h>
#include <types/address_types.h>
#include <tisci/tisci_protocol.h>
#include <tisci/security/tisci_sec_macros.h>

/**
 * \brief Request for a change owner operation
 *
 * \param hdr Common TI-SCI header
 *
 * \param fwl_id firewall ID in question
 * \param region Region or channel number if applicable
 * \param owner_index New owner index to transfer ownership to
 */
struct tisci_msg_fwl_change_owner_info_req {
	struct tisci_header	hdr;
	u16			fwl_id;
	u16			region;
	u8			owner_index;
} __attribute__((__packed__));

/**
 * \brief Response for a change owner operation
 *
 * \param hdr Common TI-SCI header
 *            ACK response indicates that change owner operation is succesful.
 *            NACK response indicates that change owner operation failed.
 *
 * \param fwl_id firewall ID specified in request
 * \param region Region or channel number specified in request
 * \param owner_index owner index specified in request
 * \param owner_privid new owner priv-ID returned by DMSC. This field is currently
 *        initialized to zero by DMSC.
 * \param owner_permission_bits new owner permission bits returned by DMSC.
 *        This field is currently initialized to zero by DMSC.
 */
struct tisci_msg_fwl_change_owner_info_resp {
	struct tisci_header	hdr;
	u16			fwl_id;
	u16			region;
	u8			owner_index;
	u8			owner_privid;
	u16			owner_permission_bits;
} __attribute__((__packed__));

/**
 * \brief Request for configuring the firewall permissions.
 *
 * \param hdr Common TI-SCI header
 *
 * \param fwl_id firewall ID in question. fwl_id is defined in the TRM.
 *
 * \param region Region or channel number to set config info
 *   This field is unused in case of a simple firewall  and must be initialized
 *   to zero.  In case of a region based firewall, this field indicates the
 *   region in question. (index starting from 0) In case of a channel based
 *   firewall, this field indicates the channel in question (index starting
 *   from 0)
 *
 * \param n_permission_regs Number of permission registers to set
 *
 * \param control Contents of the firewall CONTROL register to set
 *
 * \param permissions Contents of the firewall PERMISSION register to set
 *
 * \param start_address Contents of the firewall START_ADDRESS register to set
 *
 * \param end_address Contents of the firewall END_ADDRESS register to set
 */

struct tisci_msg_fwl_set_firewall_region_req {
	struct tisci_header	hdr;
	u16			fwl_id;
	u16			region;
	u32			n_permission_regs;
	u32			control;
	u32			permissions[FWL_MAX_PRIVID_SLOTS];
	soc_phys_addr_t		start_address;
	soc_phys_addr_t		end_address;
} __attribute__((__packed__));

/**
 * \brief Response for configuring the firewall permissions.
 *
 * \param hdr Generic TISCI message header.
 *      ACK response indicates that firewall configuration is succesful.
 *      NACK response indicates that the configuration was not performed.
 */
struct tisci_msg_fwl_set_firewall_region_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Request for retrieving the firewall permissions.
 *
 * \param hdr Generic TISCI message header.
 *
 * \param fwl_id firewall ID in question. fwl_id is defined in the TRM.
 *
 * \param region Region or channel number to set config info
 *
 *   This field is unused in case of a simple firewall  and must be initialized
 *   to zero.  In case of a region based firewall, this field indicates the
 *   region in question (index starting from 0). In case of a channel based
 *   firewall, this field indicates the channel in question (index starting
 *   from 0).
 *
 * \param n_permission_regs Number of permission registers to retrieve
 */
struct tisci_msg_fwl_get_firewall_region_req {
	struct tisci_header	hdr;
	u16			fwl_id;
	u16			region;
	u32			n_permission_regs;
} __attribute__((__packed__));

/**
 * \brief Response for retrieving the firewall permissions.
 *
 * \param hdr Generic TISCI message header.
 *      A ACK response in the hdr indicates that the message was processed.
 *      successfully.
 *     A NACK response indicates failure to retrieve firewall permissions.
 *
 * \param fwl_id firewall ID in question. fwl_id is defined in the TRM.
 *
 * \param region Region or channel number to set config info This field is
 * unused in case of a simple firewall  and must be initialized to zero.  In
 * case of a region based firewall, this field indicates the region in
 * question. (index starting from 0) In case of a channel based firewall, this
 * field indicates the channel in question (index starting from 0)
 *
 * \param n_permission_regs Number of permission registers retrieved
 *
 * \param control Contents of the firewall CONTROL register
 *
 * \param permissions Contents of the firewall PERMISSION registers
 *
 * \param start_address Contents of the firewall START_ADDRESS register
 * This is not applicable for channelized firewalls.
 *
 * \param end_address Contents of the firewall END_ADDRESS register
 * This is not applicable for channelized firewalls.
 */

struct tisci_msg_fwl_get_firewall_region_resp {
	struct tisci_header	hdr;
	u16			fwl_id;
	u16			region;
	u32			n_permission_regs;
	u32			control;
	u32			permissions[FWL_MAX_PRIVID_SLOTS];
	soc_phys_addr_t		start_address;
	soc_phys_addr_t		end_address;
} __attribute__((__packed__));

#endif
