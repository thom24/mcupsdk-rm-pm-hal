/*
 * System Firmware TISCI RM Messaging Core
 *
 * Common TISCI Protocol Definitions for RM messages
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_TISCI_PROTOCOL_H
#define RM_TISCI_PROTOCOL_H

/**
 * The secondary_host parameter is valid for any RM TISCI message utilizing
 * the seconday host mechanic.
 */
#define TISCI_MSG_VALUE_RM_SECONDARY_HOST_VALID ((u32) 1u << 31u)

/**
 * Value specified for the secondary_host element within TISCI RM messages to
 * signify the secondary_host value is not used and the source host of the
 * message is specified in the TISCI message header @ref tisci_header::host
 * field.
 */
#define TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST (0xFFu)

/**
 * \brief Resource sharing types
 *
 * Enumerates the sharing options allowed to be programmed for any TISCI RM
 * messages supporting the share parameter.
 */
enum tisci_msg_value_rm_share_type {
	/** Exclusive - Resource is allocatable by a single processing entity */
	TISCI_MSG_VALUE_RM_SHARE_EXCLUSIVE = 0u,
	/** Open sharing - Resource can be shared by an unlimited number of
	 *                 processing entities after allocation.  The sharing
	 *                 limit is the max usage count of 255 */
	TISCI_MSG_VALUE_RM_SHARE_OPEN = 1u,
	/** Limited sharing - Resource can be shared by a limited number of
	 *                    processing entities after allocation.  The limit
	 *                    is enforced by the SoC channelized firewall
	 *                    characteristics. */
	TISCI_MSG_VALUE_RM_SHARE_LIMITED = 2u,
};

#endif /* RM_TISCI_PROTOCOL_H */
