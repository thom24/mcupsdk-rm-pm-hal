/*
 * System Firmware TISCI RM Core Messaging
 *
 * TISCI Protocol Definitions for RM core messages
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_TISCI_CORE_H
#define RM_TISCI_CORE_H

#include <tisci/tisci_protocol.h>
#include <tisci/rm/tisci_rm_shared.h>

/**
 * \brief Retrieves a host's assigned range for a resource
 *
 * Returns the range for a unique resource type assigned to the specified host,
 * or secondary host.  The unique resource type is formed by combining the
 * 10 LSB of type and the 6 LSB of subtype.
 *
 * Unique types which do not map to an SoC resource will not be NACK'd.  Instead
 * the tisci_msg_rm_get_resource_range_resp range_start and range_num values are
 * zeroed.  This provides a known response mechanism across varied SoCs.
 *
 * \param hdr
 * Standard TISCI header
 *
 * \param type
 * Resource assignment type used to form unique resource type.  Only 10 LSB are
 * valid.  Types are found in the "Enumeration of Resource Type IDs" section of
 * the DMSC public document.
 *
 * \param subtype
 * Resource assignment subtype used to form unique resource type.  Only 6 LSB
 * are valid.  Subtypes are found in the "Enumeration of Resource Type IDs"
 * section of the DMSC public document.
 *
 * \param secondary_host
 * The host processing entity attempting to allocate the ring if not set to
 * @ref TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST.  Otherwise, the host within
 * the TISCI message header is the host attempting to allocate the ring.
 *
 * Populating secondary_host with @ref TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST
 * specifies the value as unused.
 */
struct tisci_msg_rm_get_resource_range_req {
	struct tisci_header	hdr;
	u16			type;
	u8			subtype;
	u8			secondary_host;
} __attribute__((__packed__));

/**
 * \brief Get resource range response message
 *
 * Response sent to host processor containing the requested resource range
 * assigned to the host who sent the range request.
 *
 * The range_start and range_num values are zero if the type and subtype in the
 * range request do not form a unique resource type for the SoC.  In this case,
 * the response will still contain an ACK.
 *
 * \param hdr
 * Standard TISCI header
 *
 * \param range_start
 * Start index of retrieved resource range.  Zero if the resource is not valid.
 *
 * \param range_num
 * Number of resources in the range.  Zero if the resource is not valid.
 *
 * \param range_start_sec
 * Start index of retrieved secondary resource range.  Zero if the resource
 * is not valid.
 *
 * \param range_num_sec
 * Number of resources in secondary range.  Zero if the resource is not valid.
 */
struct tisci_msg_rm_get_resource_range_resp {
	struct tisci_header	hdr;
	u16			range_start;
	u16			range_num;
	u16			range_start_sec;
	u16			range_num_sec;
} __attribute__((__packed__));

#endif /* RM_TISCI_CORE_H */
