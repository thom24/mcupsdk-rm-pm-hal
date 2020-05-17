/*
 * System Firmware TISCI RM Proxy Messaging
 *
 * TISCI Protocol Definitions for proxy messages
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_TISCI_PROXY_H
#define RM_TISCI_PROXY_H

#include <tisci/tisci_protocol.h>

/**
 * \brief Configures a Navigator Subsystem proxy
 *
 * Configures the channelized firewalls of a Navigator Subsystem
 * proxy.  The firewalls are configured to all the header host access to the
 * backing RAM and target data configuration registers.  The proxy index must
 * be assigned to the host defined in the TISCI header via the RM board
 * configuration resource assignment range list.
 *
 * \param hdr
 * Standard TISCI header
 *
 * \param valid_params
 * Bitfield defining validity of proxy configuration parameters.
 * This field is unused at the moment but exists if expansion of the API is
 * needed in the future.
 *
 * \param nav_id
 * SoC device ID of Navigator Subsystem where proxy is located
 *
 * \param index
 * Proxy index.
 */
struct tisci_msg_rm_proxy_cfg_req {
	struct tisci_header	hdr;
	u32			valid_params;
	u16			nav_id;
	u16			index;
} __attribute__((__packed__));

/**
 * \brief Response to configuring a proxy.
 *
 * \param hdr
 * Standard TISCI header
 */
struct tisci_msg_rm_proxy_cfg_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

#endif /* RM_TISCI_PROXY_H */
