/*
 * System Firmware TISCI LPM Messaging
 *
 * TISCI LPM layer for managing Low Power Mode TISCI message handlers
 *
 * Copyright (C) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TISCI_LPM_H
#define TISCI_LPM_H

#include <config.h>
#include <types/short_types.h>
#include <tisci/tisci_protocol.h>

#define TISCI_MSG_VALUE_SLEEP_MODE_DEEP_SLEEP              0x0
#define TISCI_MSG_VALUE_SLEEP_MODE_MCU_ONLY                        0x1
#define TISCI_MSG_VALUE_SLEEP_MODE_STANDBY                         0x2

#define MSG_FLAG_CERT_AUTH_PASS                        0x555555
#define MSG_FLAG_CERT_AUTH_FAIL                        0xffffff

#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_00            0x0x00000001
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_01            0x0x00000002
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_02            0x0x00000004
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_03            0x0x00000008
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_04            0x0x00000010
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_05            0x0x00000020
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_06            0x0x00000040
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_07            0x0x00000080
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_08            0x0x00000100
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_09            0x0x00000200
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_10            0x0x00000400
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_11            0x0x00000800
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_12            0x0x00001000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_13            0x0x00002000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_14            0x0x00004000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_15            0x0x00008000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_16            0x0x00010000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_17            0x0x00020000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_18            0x0x00040000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_19            0x0x00080000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_20            0x0x00100000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_21            0x0x00200000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_22            0x0x00400000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_23            0x0x00800000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_24            0x0x01000000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_25            0x0x02000000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_26            0x0x04000000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_27            0x0x08000000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_28            0x0x10000000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_29            0x0x20000000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_30            0x0x40000000
#define TISCI_MSG_VALUE_SLEEP_DEBUG_FLAG_31            0x0x80000000

/**
 * \brief Request for TISCI_MSG_PREPARE_SLEEP.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 * \param mode Low power mode to enter.
 * \param ctx_lo Low 32-bits of physical pointer to address to use for context save.
 * \param ctx_hi High 32-bits of physical pointer to address to use for context save.
 * \param debug_flags Flags that can be set to halt the sequence during suspend or
 *                                    resume to allow JTAG connection and debug.
 *
 * This message is used as the first step of entering a low power mode. It
 * allows configurable information, including which state to enter to be
 * easily shared from the application, as this is a non-secure message and
 * therefore can be sent by anyone.
 *
 * Notes:
 *  * Mode is defined as one of TISCI_MSG_VALUE_SLEEP_MODE_x macros.
 *  * ctx_lo and ctx_hi are to be a reserved memory region as decided on by
 *    the HLOS. This region should be a carveout in DDR and valid for use
 *    with DMA. Otherwise there are no constraints on this memory. An
 *    encrypted blob will be placed here and only a valid blob can be
 *    decrypted and authenticated, which eliminates risk of tampering.
 */
struct tisci_msg_prepare_sleep_req {
	struct tisci_header	hdr;
	u8			mode;
	u32			ctx_lo;
	u32			ctx_hi;
	u32			debug_flags;
} __attribute__((__packed__));

/**
 * \brief Response for TISCI_MSG_PREPARE_SLEEP.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 */
struct tisci_msg_prepare_sleep_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Request for TISCI_MSG_ENTER_SLEEP.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 * \param mode Low power mode to enter.
 * \param proc_id Processor id to be used for restoring boot vector and debug
 *                status upon resume
 * \param core_resume_lo Low 32-bits of physical pointer to address for core to begin execution upon resume.
 * \param core_resume_hi High 32-bits of physical pointer to address for core to begin execution upon resume.
 *
 * This message is to be sent after TISCI_MSG_PREPARE_SLEEP and actually triggers entry into the specified
 * low power mode.
 *
 */
struct tisci_msg_enter_sleep_req {
	struct tisci_header	hdr;
	u8			mode;
	u8			proc_id;
	u32			core_resume_lo;
	u32			core_resume_hi;
} __attribute__((__packed__));

/**
 * \brief Response for TISCI_MSG_ENTER_SLEEP.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 * \param status Value that gives information about what happened during LPM cycle
 */
struct tisci_msg_enter_sleep_resp {
	struct tisci_header	hdr;
	u32			status;
} __attribute__((__packed__));

/**
 * \brief Request for TISCI_MSG_FIRMWARE_LOAD.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 * \param image_addr SPS memory address to load FS stub from.
 * \param image_size size of the FS stub imsage.
 */
struct tisci_msg_firmware_load_req {
	struct tisci_header	hdr;
	u32			image_addr;
	u32			image_size;
} __attribute__((__packed__));

/**
 * \brief Response for TISCI_MSG_FIRMWARE_LOAD.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 */
struct tisci_msg_firmware_load_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Request for TISCI_MSG_SYNC_RESUME.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 *
 * Generic synchronization message between cores to be used as a checkpoint
 * when TIFS and DM are working in coordination.
 */
struct tisci_msg_sync_resume_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Response for TISCI_MSG_SYNC_RESUME.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 *
 * Generic synchronization message between cores to be used as a checkpoint
 * when TIFS and DM are working in coordination.
 */
struct tisci_msg_sync_resume_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Request for TISCI_MSG_CONTINUE_RESUME.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 *
 * This message is sent from TIFS Stub to DM stub to indicate that all
 * prerequisite steps to allow DDR restore to proceed have been completed.
 *
 */
struct tisci_msg_continue_resume_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Response for TISCI_MSG_CONTINUE_RESUME.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 *
 * \param ctx_lo Low 32-bits of physical pointer to address that was used for context save.
 * \param ctx_hi High 32-bits of physical pointer to address that was used for context save.
 *
 * This response is sent from the DM stub to the TIFS stub to trigger TIFS
 * Stub restore of TIFS context from the address provided in the ctx_lo and
 * ctx_hi parameters. This response assumes DDR has been fully restored by DM
 * Stub before it is sent.
 *
 */
struct tisci_msg_continue_resume_resp {
	struct tisci_header	hdr;
	u32			ctx_lo;
	u32			ctx_hi;
} __attribute__((__packed__));

/**
 * \brief Request for TISCI_MSG_CORE_RESUME.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 *
 * This message is sent from the DM firmware to the TIFS firmware during
 * resume to indicate that it is ready for all other cores to be restored.
 * TIFS receives this message and restores A53 and HSM core.
 */
struct tisci_msg_core_resume_req {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Response for TISCI_MSG_CORE_RESUME.
 *
 * \param hdr TISCI header to provide ACK/NAK flags to the host.
 *
 */
struct tisci_msg_core_resume_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

#endif
