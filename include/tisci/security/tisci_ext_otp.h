/*
 * System Firmware
 *
 * TISCI Data structures and macros for External OTP access
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef TISCI_EXT_OTP_H
#define TISCI_EXT_OTP_H

#include <tisci/tisci_protocol.h>
#include <types/short_types.h>

/**
 * \brief Request message for reading OTP MMR
 *
 * \param hdr Common TI-SCI header
 * \param mmr_idx Index of the 32-bit MMR to be read. Index starts from zero.
 */
struct tisci_msg_read_otp_mmr_req {
	struct tisci_header	hdr;
	u8			mmr_idx;
} __attribute__((__packed__));

/**
 * \brief Respone message for reading OTP MMR
 *
 * \param hdr Common TI-SCI header
 * \param mmr_val Value of the requested 32-bit MMR
 */
struct tisci_msg_read_otp_mmr_resp {
	struct tisci_header	hdr;
	u32			mmr_val;
} __attribute__((__packed__));

/**
 * \brief Request message for performing a global soft write lock on OTP rows
 *
 * \param hdr Common TI-SCI header
 */
struct tisci_msg_soft_lock_otp_write_global_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Respone message for global soft write lock on OTP rows
 *
 * \param hdr Common TI-SCI header
 */
struct tisci_msg_soft_lock_otp_write_global_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Request message for hardware locking an OTP row
 *
 * \param hdr Common TI-SCI header
 * \param row_idx Index of the otp row to be written. Index starts from zero.
 * \param hw_write_lock    indicates if write lock has to be applied in HW on the current row. Set to 0x5A for write lock.
 * \param hw_read_lock     indicates if read lock has to be applied in HW on the current row. (ignored for now)
 * \param row_soft_lock    indicates if soft lock has to be enabled on current row preventing writes. (ignored for now)
 *
 * In all cases 0x5A indicates true and 0xA5 indicates false. All other values are invalid.
 */
struct tisci_msg_lock_otp_row_req {
	struct tisci_header	hdr;
	u8			row_idx;
	u8			hw_write_lock;
	u8			hw_read_lock;
	u8			row_soft_lock;
} __attribute__((__packed__));

/**
 * \brief Respone message for hardware lock OTP row
 *
 * \param hdr Common TI-SCI header
 */
struct tisci_msg_lock_otp_row_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Request message for writing to an OTP row
 *
 * \param hdr Common TI-SCI header
 * \param row_idx Index of the otp row to be written. Index starts from zero.
 * \param row_val value to be written to the otp row
 * \param row_mask mask specifying the bits in row_val to be written
 */
struct tisci_msg_write_otp_row_req {
	struct tisci_header	hdr;
	u8			row_idx;
	u32			row_val;
	u32			row_mask;
} __attribute__((__packed__));

/**
 * \brief Respone message for writing to an OTP row
 *
 * \param hdr Common TI-SCI header
 * \param row_val value read back from the row after the write operation.
 */
struct tisci_msg_write_otp_row_resp {
	struct tisci_header	hdr;
	u32			row_val;
} __attribute__((__packed__));

/**
 * \brief Request message for querying lock status of an OTP row
 *
 * \param hdr Common TI-SCI header
 * \param row_idx Index of the otp row to be queried. Index starts from zero.
 */
struct tisci_msg_get_otp_row_lock_status_req {
	struct tisci_header	hdr;
	u8			row_idx;
} __attribute__((__packed__));

/**
 * \brief Respone message for Get OTP row lock status request
 *
 * \param hdr Common TI-SCI header
 * \param global_soft_lock indicates if global soft lock has been enabled preventing writes.
 * \param hw_write_lock    indicates if write lock has been applied in HW on the current row.
 * \param hw_read_lock     indicates if read lock has been applied in HW on the current row.
 * \param row_soft_lock    indicates if soft lock has been enabled on current row preventing writes.
 *
 * In all cases 0x5A indicates true and 0xA5 indicates false. All other values are invalid.
 */
struct tisci_msg_get_otp_row_lock_status_resp {
	struct tisci_header	hdr;
	u8			global_soft_lock;
	u8			hw_write_lock;
	u8			hw_read_lock;
	u8			row_soft_lock;
} __attribute__((__packed__));

#endif /* TISCI_EXT_OTP_H */
