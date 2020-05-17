/*
 * System Firmware
 *
 * TISCI Data structures for opening the JTAG port
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef TISCI_SECURE_JTAG_H_
#define TISCI_SECURE_JTAG_H_

#include <tisci/tisci_protocol.h>
#include <types/short_types.h>
#include <tisci/security/tisci_sec_macros.h>

/**
 * \brief Request to provide the SOC UID via TISCI_MSG_OPEN_DEBUG_FWLS
 *
 * \param hdr Common TI-SCI header
 * \param debug_cert_addr Physical address of the debug unlock certificate
 */
struct tisci_msg_open_debug_fwls_req {
	struct tisci_header	hdr;
	u64			debug_cert_addr;
} __attribute__((__packed__));

/**
 * \brief Response to the TISCI_MSG_OPEN_DEBUG_FWLS message
 *
 * \param hdr Common TI-SCI header
 *
 */
struct tisci_msg_open_debug_fwls_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));
#endif
