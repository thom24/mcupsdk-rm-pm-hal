/*
 * System Firmware
 *
 * TISCI Data structures for obtaining SOC UID
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef TISCI_SOC_UID_H_
#define TISCI_SOC_UID_H_

#include <tisci/tisci_protocol.h>
#include <types/short_types.h>
#include <tisci/security/tisci_sec_macros.h>

/**
 * \brief Request to provide the SOC UID via TISCI_MSG_GET_SOC_UID
 *
 * \param hdr Common TI-SCI header
 */
struct tisci_msg_get_soc_uid_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Response to the TISCI_MSG_GET_SOC_UID message
 *
 * \param hdr Common TI-SCI header
 * \param soc_uid 8 words with the SOC UID
 *
 */
struct tisci_msg_get_soc_uid_resp {
	struct tisci_header	hdr;
	u32			soc_uid[UID_LEN_WORDS];
} __attribute__((__packed__));
#endif
