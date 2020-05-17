/*
 * System Firmware
 *
 * TISCI Data structures and macros for SA2UL resource management
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef TISCI_SA2UL_RM_H_
#define TISCI_SA2UL_RM_H_

#include <tisci/tisci_protocol.h>
#include <types/short_types.h>

/**
 * \brief Request to acquire the authentication resources from System Fimrware
 *
 * The following is to request for SYSFW authentication resources to be handed
 * off to the requesting host. The following occurs during this API request:
 *
 *   PKA firewall region ownership is transitioned to the requesting host. No
 *   permissions are updated at this time - the host must take further action to
 *   update the region permissions through firewall API.
 *
 *   Secure PSIL threads are unpaired by SYSFW so that the requesting host can
 *   pair to their own DMA channels
 *
 * Only the host who is listed as the auth_resources owner in the security board
 * configuration may make this request.
 *
 * \param hdr Common TI-SCI header
 */

struct tisci_msg_sa2ul_auth_res_acquire_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Response to authentication resource acquisition request
 *
 * \param hdr Generic TISCI message header. ACK response indicates that the
 *            secure threads are unpaired from System Firmware's DMA channels
 *            and the host has exclusive access to PKA registers. A NACK
 *            response indicates that the resources could not be released to the
 *            requesting host.
 */
struct tisci_msg_sa2ul_auth_res_acquire_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Request to release the authentication resources back to System
 *        Fimrware
 *
 * The following is to request for SYSFW authentication resources to be given
 * back to SYSFW. The following occurs during this API request:
 *
 *   PKA firewall is updated so that SYSFW becomes owner once again, and access
 *   is limited to DMSC only
 *
 *   Secure PSIL threads are cleaned up so that they can be are re-paired by
 *   SYSFW
 *
 * Only the host who is listed as the auth_resources owner in the security board
 * configuration may make this request.
 *
 * \param hdr Common TI-SCI header
 */

struct tisci_msg_sa2ul_auth_res_release_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Response to authentication resource release request
 *
 * \param hdr Generic TISCI message header. ACK response indicates that the
 * secure threads are cleaned for pairing to System Firmware's DMA channels and
 * the DMSC access to PKA registers is restored. A NACK response indicates that
 * the resources could not be released to the requesting back to System
 * Firmware.
 */
struct tisci_msg_sa2ul_auth_res_release_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

#endif /* TISCI_SA2UL_RM_H_ */
