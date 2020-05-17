/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef TISCI_PM_TISCI_CORE_H
#define TISCI_PM_TISCI_CORE_H

#include <types/short_types.h>
#include <tisci/tisci_protocol.h>

/**
 * \brief Empty request for TISCI_MSG_WAKE_REASON.
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr TISCI header.
 */
struct tisci_msg_wake_reason_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Response for TISCI_MSG_WAKE_REASON.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 * \param mode Mode that was active before wake event.
 * \param reason Reason the wakeup happened.
 * \param time_ms Time spent in low power mode.
 */
struct tisci_msg_wake_reason_resp {
	struct tisci_header	hdr;
	char			mode[32];
	char			reason[32];
	u32			time_ms;
} __attribute__((__packed__));

/**
 * \brief Empty request for TISCI_MSG_WAKE_RESET.
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr TISCI header.
 */
struct tisci_msg_wake_reset_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Empty response for TISCI_MSG_WAKE_RESET.
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr TISCI header.
 */
struct tisci_msg_wake_reset_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Empty request for TISCI_MSG_ENABLE_WDT.
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr TISCI header.
 */
struct tisci_msg_enable_wdt_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Empty response for TISCI_MSG_ENABLE_WDT.
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr TISCI header.
 */
struct tisci_msg_enable_wdt_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Empty request for TISCI_MSG_GOODBYE.
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr TISCI header.
 */
struct tisci_msg_goodbye_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Empty response for TISCI_MSG_GOODBYE.
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr TISCI header.
 */
struct tisci_msg_goodbye_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Empty request for TISCI_MSG_SYS_RESET.
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr TISCI header.
 */
struct tisci_msg_sys_reset_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Empty response for TISCI_MSG_SYS_RESET.
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr TISCI header.
 */
struct tisci_msg_sys_reset_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

#endif /* TISCI_PM_TISCI_CORE_H */
