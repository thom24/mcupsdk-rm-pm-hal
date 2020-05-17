/*
 * System Firmware
 *
 * TISCI Data structures and macros for runtime keystore
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef TISCI_KEYSTORE_H_
#define TISCI_KEYSTORE_H_

#include <tisci/tisci_protocol.h>
#include <types/short_types.h>

/** Keystore Major ABI revision value */
#define KEYSTORE_ABI_MAJ_VALUE                  0x00
/** Keystore Minor ABI revision value */
#define KEYSTORE_ABI_MIN_VALUE                  0x01

/**
 * \brief Request for writing the entire keystore contents
 *
 *  A user may unlock the keystore to write its contents using a signed and
 *  encrypted keystore structure. This operation is required for keystore
 *  initialization and is mandatorily the first keystore operation which must be
 *  executed in order to put the keystore in a valid state for subsequent
 *  operations.
 *
 * \param hdr Common TI-SCI header
 *
 * \param keystore_lo Lower 32-bit memory location of the signed and
 *                    encrypted keystore contents
 * \param keystore_hi Higher 32-bit memory location of the signed and
 *                    encrypted keystore contents
 */
struct tisci_msg_keystore_write_req {
	struct tisci_header	hdr;
	u32			keystore_lo;
	u32			keystore_hi;
} __attribute__((__packed__));

/**
 * \brief Response to the keystore write
 *
 * \param hdr Generic TISCI message header. ACK response indicates that the
 *            accompanying certificate was validated and the keystore contents
 *            were successfully decrypted, authenticated, and copied to the
 *            internal keystore memory. NACK response indicates that the
 *            keystore write could not be completed.
 */
struct tisci_msg_keystore_write_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Request for exporting the entire keystore contents
 *
 *  The host will make the request to encrypt and export the entire keystore
 *  contents for saving to some storage mechanism to be made available for
 *  future re-import. Only the host who owns the keystore structure may execute
 *  this operation. The host is responsible for pre-allocating enough memory to
 *  fit the keystore structure and all encryption parameters.
 *
 * \param hdr Common TI-SCI header
 *
 * \param keystore_lo Lower 32-bit memory location where the encrypted keystore
 *                    contents will be placed to pass back to the host
 * \param keystore_hi Higher 32-bit memory location where the encrypted keystore
 *                    contents will be placed to pass back to the host
 */
struct tisci_msg_keystore_export_req {
	struct tisci_header	hdr;
	u32			keystore_lo;
	u32			keystore_hi;
} __attribute__((__packed__));

/**
 * \brief Response to the keystore export
 *
 * \param hdr Generic TISCI message header. ACK response indicates that the
 *            keystore has been encrypted and copied into the host-provided
 *            memory. NACK response indicates that the keystore export could not
 *            be completed
 */
struct tisci_msg_keystore_export_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Request for importing a previously exported keystore
 *
 * \param hdr Common TI-SCI header
 *
 * \param keystore_lo Lower 32-bit memory location of the encrypted keystore
 *                    contents provided by the host
 * \param keystore_hi Higher 32-bit memory location of the encrypted keystore
 *                    contents provided by the host
 */
struct tisci_msg_keystore_import_req {
	struct tisci_header	hdr;
	u32			keystore_lo;
	u32			keystore_hi;
} __attribute__((__packed__));

/**
 * \brief Response to the keystore import
 *
 * \param hdr Generic TISCI message header. ACK response indicates that the
 *            imported keystore has been successfully decrypted and
 *            authenticated. NACK response indicates that the keystore import
 *            could not be completed.
 */
struct tisci_msg_keystore_import_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

#endif /* TISCI_KEYSTORE_H_ */
