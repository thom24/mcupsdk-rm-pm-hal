/*
 * System Firmware
 *
 * TISCI Data structures and macros for processor boot messages
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef TISCI_PROCBOOT_H_
#define TISCI_PROCBOOT_H_

#include <tisci/tisci_protocol.h>
#include <types/short_types.h>

/**
 * \brief Request for physical processor control request
 *
 * Provides a means for either the "recovery master" host or another host
 * in the permitted access list to request for a physical processor control.
 *
 * \param hdr Generic TISCI message header.
 * \param processor_id Specifies a Processor ID. See
 *                       the SoC Family Specific Documentation Chapter of the
 *                       TISCI User Guide for accepted values.
 */
struct tisci_msg_proc_request_req {
	struct tisci_header	hdr;
	u8			processor_id;
} __attribute__((__packed__));

/**
 * \brief Request for physical processor control response
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * ACK response: The processor access is permitted for the host if
 * processor is un-claimed AND host is permitted to control the
 * processor OR if the host is the recovery master.
 *
 * NAK response: The processor access is not permitted.
 *
 * \param hdr Generic TISCI message header.
 */
struct tisci_msg_proc_request_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Release physical processor control request
 *
 * Provides a means for the host with current control to relinquish a
 * physical processor control.
 *
 * \param hdr Generic TISCI message header.
 * \param processor_id ID of processor to release.
 */
struct tisci_msg_proc_release_req {
	struct tisci_header	hdr;
	u8			processor_id;
} __attribute__((__packed__));

/**
 * \brief Release physical processor control response
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr Generic TISCI message header.
 *
 * ACK Response: The host had control over the processor and is
 * confirmed to be released to "free pool".
 *
 * NAK Response: The processor access is not permitted.
 */
struct tisci_msg_proc_release_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Request to handover control of a processor to another host
 *        if permitted.
 *
 * Provides a means for the host with current control to relinquish a
 * physical processor control to another host in the permitted list.
 *
 * \param hdr Generic TISCI message header.
|* \param processor_id Specifies a Processor ID.
 * \param host_id Specifies the new host to hand over control to.
 */
struct tisci_msg_proc_handover_req {
	struct tisci_header	hdr;
	u8			processor_id;
	u8			host_id;
} __attribute__((__packed__));

/**
 * \brief Response to handover of control of a processor to another
 *        host if permitted.
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr Generic TISCI message header.
 *
 * ACK Response: The host had control over the processor and is
 * confirmed to be released to "free pool".
 *
 * NAK Response: The processor access is not permitted.
 */
struct tisci_msg_proc_handover_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/* A53 Config Flags */

/** ARMV8 Invasive debug */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_ARMV8_DBG_EN         (0x00000001U)
/** ARMV8 Non-Invasive debug */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_ARMV8_DBG_NIDEN      (0x00000002U)
/** ARMV8 Secure invasive Debug */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_ARMV8_DBG_SPIDEN     (0x00000004U)
/** ARMV8 Secure Non-invasive Debug */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_ARMV8_DBG_SPNIDEN    (0x00000008U)
/** ARMV8 AARCH32 */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_ARMV8_AARCH32        (0x00000100U)

/* R5 Config Flags */

/** R5 Invasive debug */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_DBG_EN            (0x00000001U)
/** R5 Non-Invasive debug */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_DBG_NIDEN         (0x00000002U)
/** R5 Lockstep */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_LOCKSTEP          (0x00000100U)
/** R5 Exception handling state at reset */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_TEINIT            (0x00000200U)
/** R5 Enable Core Non-Maskable Fast Interrupts */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_NMFI_EN           (0x00000400U)
/** R5 Core A/BTCM Reset Base address Indicator */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_TCM_RSTBASE       (0x00000800U)
/** R5 Enable Core BTCM RAM at reset */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_BTCM_EN           (0x00001000U)
/** R5 Enable Core ATCM RAM at reset */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_R5_ATCM_EN           (0x00002000U)

/* C7x Config Flags */

/* L2_PIPELINE_LATENCY_VALUE */
/** L2_PIPELINE_LATENCY_VALUES shifted mask for config */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2PL_MASK        (0x0000000FU)
/** L2_PIPELINE_LATENCY_VALUES bit shift for config */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2PL_SHIFT       (0x00000000U)
/** L2_PIPELINE_LATENCY_VALUES Latency of 1 */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2PL_1           (0x00000001U)
/** L2_PIPELINE_LATENCY_VALUES Latency of 2 */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2PL_2           (0x00000002U)
/** L2_PIPELINE_LATENCY_VALUES Latency of 3 */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2PL_3           (0x00000003U)
/** L2_PIPELINE_LATENCY_VALUES Latency of 4 */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2PL_4           (0x00000004U)
/** L2_PIPELINE_LATENCY_VALUES Latency of 5 */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2PL_5           (0x00000005U)

/* L2_ACCESS_LATENCY_VALUE */
/** L2_ACCESS_LATENCY_VALUE shifted mask for config */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2AL_MASK        (0x000000F0U)
/** L2_ACCESS_LATENCY_VALUE bit shift for config */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2AL_SHIFT       (0x00000004U)
/** L2_ACCESS_LATENCY_VALUE Latency of 2 */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2AL_2           (0x00000020U)
/** L2_ACCESS_LATENCY_VALUE Latency of 3 */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2AL_3           (0x00000030U)
/** L2_ACCESS_LATENCY_VALUE Latency of 4 */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2AL_4           (0x00000040U)
/** L2_ACCESS_LATENCY_VALUE Latency of 5 */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C7X_L2AL_5           (0x00000050U)

/* C6x Config Flags */

/* SSCLK_MODE_DIV_CLK_MODE_VALUE values
 *
 * NOTE: Values are 1 more than actual programmed values to avoid '0' as a
 * valid value that we pass via flags.
 */
/** SSCLK_MODE_DIV_CLK_MODE_VALUE shifted mask for config */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C6X_SSCLKMV_MASK    (0x00000007U)
/** SSCLK_MODE_DIV_CLK_MODE_VALUE bit shift for config */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C6X_SSCLKMV_SHIFT   (0x00000000U)
/** SSCLK_MODE_DIV_CLK_MODE_VALUE Div2 clock mode. */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C6X_SSCLKMV_DIV2    (0x00000001U)
/** SSCLK_MODE_DIV_CLK_MODE_VALUE Div3 clock mode. */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C6X_SSCLKMV_DIV3    (0x00000002U)
/** SSCLK_MODE_DIV_CLK_MODE_VALUE Div4 clock mode. */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_C6X_SSCLKMV_DIV4    (0x00000003U)

/* M4F Config Flags */

/** M4F Invasive debug */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_M4F_DBG_EN            (0x00000001U)
/** M4F Non-Invasive debug */
#define TISCI_MSG_VAL_PROC_BOOT_CFG_FLAG_M4F_DBG_NIDEN         (0x00000002U)
/**
 * \brief Processor Boot Configuration
 * \param hdr Message header
 * \param processor_id ID of processor
 * \param bootvector_lo Lower 32bit (Little Endian) of boot vector
 * \param bootvector_hi Higher 32bit (Little Endian) of boot vector
 * \param config_flags_1_set Optional Processor specific Config Flags to set.
 *	Setting a bit here implies required bit has to be set to 1.
 * \param config_flags_1_clear Optional Processor specific Config Flags to clear.
 *	Setting a bit here implies required bit has to be cleared to 0.
 */
struct tisci_msg_proc_set_config_req {
	struct tisci_header	hdr;
	u8			processor_id;
	u32			bootvector_lo;
	u32			bootvector_hi;
	u32			config_flags_1_set;
	u32			config_flags_1_clear;
} __attribute__((__packed__));

/**
 * \brief Response to Processor Boot Configuration message.
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr Generic TISCI message header.
 *
 * ACK Response: The host had control over the processor and requested
 * operation is successful
 *
 * NAK Response: The processor access is not permitted or the operation failed.
 */
struct tisci_msg_proc_set_config_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/* ARMV8 Control Flags */

/** ARMV8 ACINACTM control: with the primary core of cluster */
#define TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_ARMV8_ACINACTM                (0x00000001U)
/** ARMV8 AINACTS control: with primary core of cluster */
#define TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_ARMV8_AINACTS                 (0x00000002U)
/** ARMV8 SoC L2FLUSHREQ control: with primary core of cluster */
#define TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_ARMV8_L2FLUSHREQ              (0x00000100U)

/* R5 Control Flags */

/** R5 Core Halt */
#define TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_CORE_HALT                (0x00000001U)

/**
 * \brief Optional processor specific message for sequence control
 * \param hdr Message header
 * \param processor_id ID of processor
 * \param control_flags_1_set Optional Processor specific Control Flags to set.
 *	Setting a bit here implies required bit has to be set to 1.
 * \param control_flags_1_clear Optional Processor specific Control Flags to clear.
 *	Setting a bit here implies required bit has to be cleared to 0.
 */
struct tisci_msg_proc_set_control_req {
	struct tisci_header	hdr;
	u8			processor_id;
	u32			control_flags_1_set;
	u32			control_flags_1_clear;
} __attribute__((__packed__));

/**
 * \brief Response to optional processor specific message for sequence control
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr Generic TISCI message header.
 *
 * ACK Response: The host had control over the processor and requested
 * operation is successful
 *
 * NAK Response: The processor access is not permitted or the operation failed.
 */
struct tisci_msg_proc_set_control_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Authenticate and start image
 * \param hdr Message header
 * \param certificate_address_lo Lower 32bit (Little Endian) of certificate
 * \param certificate_address_hi Higher 32bit (Little Endian) of certificate
 */
struct tisci_msg_proc_auth_boot_req {
	struct tisci_header	hdr;
	u32			certificate_address_lo;
	u32			certificate_address_hi;
} __attribute__((__packed__));

/**
 * \brief Response to authenticate and start image request
 *
 * \param hdr Generic TISCI message header.
 * \param image_address_lo Lower 32bit (Little Endian) of image
 * \param image_address_hi Higher 32bit (Little Endian) of image
 * \param image_size Size of the binary
 *
 * ACK Response: The host had control over the processor and requested
 * operation is successful
 *
 * NAK Response: The processor access is not permitted or the operation failed.
 *
 * IMPORTANT: Reason for failure is NOT provided to prevent security attacks
 * by scan. If permitted, System firmware logs shall provide relevant failure
 * information.
 */
struct tisci_msg_proc_auth_boot_resp {
	struct tisci_header	hdr;
	u32			image_address_lo;
	u32			image_address_hi;
	u32			image_size;
} __attribute__((__packed__));

/**
 * \brief Processor Status request
 *
 * \param hdr Message header
 * \param processor_id ID of processor
 */
struct tisci_msg_proc_get_status_req {
	struct tisci_header	hdr;
	u8			processor_id;
} __attribute__((__packed__));

/* ARMV8 Status Flags */

/** ARMV8 Set if the core is in WFE state */
#define TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_ARMV8_WFE         (0x00000001U)
/** ARMV8 Set if the core is in WFI state */
#define TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_ARMV8_WFI         (0x00000002U)
/** ARMV8 L2 Hardware Flush complete */
#define TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_ARMV8_L2F_DONE    (0x00000010U)
/** ARMV8 STANDBYWFIL2 WFI achieved */
#define TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_ARMV8_STANDBYWFIL2       (0x00000020U)

/* R5 Status Flags */

/** R5 Set if the core is in WFE state */
#define TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFE            (0x00000001U)
/** R5 Set if the core is in WFI state */
#define TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_WFI            (0x00000002U)
/** R5 Core Clock Stopped due to WFI or WFE state */
#define TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_CLK_GATED      (0x00000004U)
/** R5 Is Lockstep configuration permitted */
#define TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_R5_LOCKSTEP_PERMITTED     (0x00000100U)

/* M4F Status Flags */

/** M4F Set if the core is in WFI state */
#define TISCI_MSG_VAL_PROC_BOOT_STATUS_FLAG_M4F_WFI            (0x00000002U)

/**
 * \brief Processor Status Response
 * \param hdr Message header
 * \param processor_id ID of processor
 * \param bootvector_lo Lower 32bit (Little Endian) of boot vector
 * \param bootvector_hi Higher 32bit (Little Endian) of boot vector
 * \param config_flags_1 Optional Processor specific Config Flags set
 * \param control_flags_1 Optional Processor specific Control Flags set
 * \param status_flags_1 Optional Processor specific Status Flags set
 *
 * ACK Response: The host had control over the processor and requested
 * operation is successful
 *
 * NAK Response: The processor access is not permitted or the operation failed.
 *
 * IMPORTANT: Reason for failure is NOT provided to prevent security attacks
 * by scan. If permitted, System firmware logs shall provide relevant failure
 * information.
 */
struct tisci_msg_proc_get_status_resp {
	struct tisci_header	hdr;
	u8			processor_id;
	u32			bootvector_lo;
	u32			bootvector_hi;
	u32			config_flags_1;
	u32			control_flags_1;
	u32			status_flags_1;
} __attribute__((__packed__));

/**
 * \brief Processor Status Wait
 * \param hdr Message header
 * \param processor_id ID of processor
 * \param num_wait_iterations 1-255, Total number of iterations we will
 *	check before we will timeout and give up
 * \param num_match_iterations 1-255, How many iterations should we have
 *	continued status to account for status bits glitching. This is to
 *	make sure that match occurs for consecutive checks. This implies that
 *	the worst case should consider that the stable time should at the
 *	worst be num_wait_iterations num_match_iterations  to prevent timeout.
 * \param delay_per_iteration_us 0-255, Specifies how long to wait
 *	(in micro seconds) between each status checks. This is the minimum
 *	duration, and overhead of register reads and checks are on top of
 *	this and can vary based on varied conditions.
 * \param delay_before_iteration_loop_start_us 0-255, Specifies how long
 *	to wait (in micro seconds) before the very first check in the first
 *	iteration of status check loop. This is the minimum duration, and
 *	overhead of register reads and checks are
 * \param status_flags_1_set_all_wait  If non-zero, Specifies that all bits
 *	of the status matching this field requested MUST be '1'.
 * \param status_flags_1_set_any_wait  If non-zero, Specifies that at least
 *	one of the bits matching this field requested MUST be '1'.
 * \param status_flags_1_clr_all_wait If non-zero, Specifies that all bits
 *	of the status matching this field requested MUST be '0'.
 * \param status_flags_1_clr_any_wait If non-zero, Specifies that at least
 *	one of the bits matching this field requested MUST be '0'.
 */
struct tisci_msg_proc_status_wait_req {
	struct tisci_header	hdr;
	u8			processor_id;
	u8			num_wait_iterations;
	u8			num_match_iterations;
	u8			delay_per_iteration_us;
	u8			delay_before_iteration_loop_start_us;
	u32			status_flags_1_set_all_wait;
	u32			status_flags_1_set_any_wait;
	u32			status_flags_1_clr_all_wait;
	u32			status_flags_1_clr_any_wait;
} __attribute__((__packed__));

/**
 * \brief Processor Status Wait Response
 *
 * Although this message is essentially empty and contains only a header
 * a full data structure is created for consistency in implementation.
 *
 * \param hdr Generic TISCI message header.
 *
 * ACK Response: The status requested was achieved within the constraints provided in request.
 * NAK Response: The processor access is not permitted or operation failed or timedout.
 */
struct tisci_msg_proc_status_wait_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

#endif /* TISCI_SECURITY_H_ */
