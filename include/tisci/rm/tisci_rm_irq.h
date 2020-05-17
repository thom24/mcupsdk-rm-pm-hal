/*
 * System Firmware TISCI RM IRQ Messaging
 *
 * TISCI Protocol Definitions for RM IRQ messages
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_TISCI_IRQ_H
#define RM_TISCI_IRQ_H

#include <tisci/tisci_protocol.h>
#include <tisci/rm/tisci_rm_shared.h>

/**
 * The dst_id parameter is valid for any RM IRQ TISCI message
 * modifying interrupt routers.
 */
#define TISCI_MSG_VALUE_RM_DST_ID_VALID                (1u << 0u)
/**
 * The dst_host_irq parameter is valid for any RM IRQ TISCI message
 * modifying interrupt routers.
 */
#define TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID          (1u << 1u)
/**
 * The ia_id parameter is valid for any RM IRQ TISCI message
 * modifying routes through an interrupt aggregator virtual interrupt.
 */
#define TISCI_MSG_VALUE_RM_IA_ID_VALID                 (1u << 2u)
/**
 * The vint parameter is valid for any RM IRQ TISCI message
 * modifying routes through an interrupt aggregator virtual interrupt.
 */
#define TISCI_MSG_VALUE_RM_VINT_VALID                  (1u << 3u)
/**
 * The global_event parameter is valid for any RM IRQ TISCI message
 * modifying routes through an interrupt aggregator virtual interrupt.
 */
#define TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID          (1u << 4u)
/**
 * The vint_status_bit_index parameter is valid for any RM IRQ TISCI message
 * modifying routes through an interrupt aggregator virtual interrupt.
 */
#define TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID (1u << 5u)

/**
 * \brief Configures peripherals within the interrupt subsystem according to the
 * valid configuration provided.  The following
 * @ref tisci_msg_rm_irq_set_req::valid_params valid bit combinations are
 * allowed:
 * Interrupt Router Mux Configuration - Configures an IR input to output mux
 *                                      connection where the IR input is the
 *                                      src_index and the IR output is the
 *                                      dst_host_irq.  Both the src_id and the
 *                                      dst_id must be the device ID of the
 *                                      IR being configured.
 *   @ref tisci_msg_rm_irq_set_req::dst_id valid bit == STRUE
 *   @ref tisci_msg_rm_irq_set_req::dst_host_irq valid bit == STRUE
 *   @ref tisci_msg_rm_irq_set_req::ia_id valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_set_req::vint valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_set_req::global_event valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_set_req::vint_status_bit_index valid bit == SFALSE
 * Event to VINT Mapping Only - Configure peripheral OES register and add an
 *                              event mapping to an IA VINT
 *   @ref tisci_msg_rm_irq_set_req::dst_id valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_set_req::dst_host_irq valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_set_req::ia_id valid bit == STRUE
 *   @ref tisci_msg_rm_irq_set_req::vint valid bit == STRUE
 *   @ref tisci_msg_rm_irq_set_req::global_event valid bit == STRUE
 *   @ref tisci_msg_rm_irq_set_req::vint_status_bit_index valid bit == STRUE
 * OES Register Programming Only - Only programs the OES register of the
 *                                 source.  Useful for setting UDMAP trigger
 *                                 events and any other events that are not
 *                                 translated to the interrupt domain:
 *   @ref tisci_msg_rm_irq_set_req::dst_id valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_set_req::dst_host_irq valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_set_req::ia_id valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_set_req::vint valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_set_req::global_event valid bit == STRUE
 *   @ref tisci_msg_rm_irq_set_req::vint_status_bit_index valid bit == SFALSE
 *
 * \param hdr
 * Standard TISCI header
 *
 * \param valid_params
 * Bitfield defining validity of interrupt route set parameters.  The
 * interrupt route set fields are not valid, and will not be used for route
 * set, if their corresponding valid bit is zero.  Valid bit usage:
 *   0 - Valid bit for @ref tisci_msg_rm_irq_set_req::dst_id
 *   1 - Valid bit for @ref tisci_msg_rm_irq_set_req::dst_host_irq
 *   2 - Valid bit for @ref tisci_msg_rm_irq_set_req::ia_id
 *   3 - Valid bit for @ref tisci_msg_rm_irq_set_req::vint
 *   4 - Valid bit for @ref tisci_msg_rm_irq_set_req::global_event
 *   5 - Valid bit for @ref tisci_msg_rm_irq_set_req::vint_status_bit_index
 *  31 - Valid bit for @ref tisci_msg_rm_irq_set_req::secondary_host
 *
 * \param src_id
 * ID of interrupt source peripheral
 *
 * \param src_index
 * Interrupt source index within source peripheral
 *
 * \param dst_id
 * SoC IR device ID when the valid_params bits are set to configure an IR
 * mux connection.  This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_DST_ID_VALID is set in
 * @ref tisci_msg_rm_irq_set_req::valid_params.
 *
 * \param dst_host_irq
 * SoC IR output index when the valid_params are set to configure an IR
 * mux connection.  This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID is set in
 * @ref tisci_msg_rm_irq_set_req::valid_params.
 *
 * \param ia_id
 * Device ID of interrupt aggregator in which the virtual interrupt resides.
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_IA_ID_VALID is set in
 * @ref tisci_msg_rm_irq_set_req::valid_params.
 *
 * \param vint
 * Virtual interrupt number when configuring an interrupt aggregator.  This
 * field is only valid if
 * @ref TISCI_MSG_VALUE_RM_VINT_VALID is set in
 * @ref tisci_msg_rm_irq_set_req::valid_params.
 *
 * \param global_event
 * Global event mapped to interrupt aggregator virtual interrupt status bit.
 * The event is programmed into the OES register of the interrupt source.  This
 * field is only applicable for interrupt source's capable of generating
 * global events.  This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID is set in
 * @ref tisci_msg_rm_irq_set_req::valid_params.
 *
 * \param vint_status_bit_index
 * Virtual interrupt status bit to set if the interrupt route utilizes an
 * interrupt aggregator virtual interrupt.  The host processor uses the status
 * bit value within the interrupt aggregator vint status register to find the
 * source event which triggered the interrupt.  This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID is set in
 * @ref tisci_msg_rm_irq_set_req::valid_params.
 *
 * \param secondary_host
 * The interrupt route destination is the specified secondary host if the
 * secondary_host's corresponding valid bit is set in
 * @ref tisci_msg_rm_irq_set_req::valid_params.  Otherwise, the host within the
 * TISCI message header is the route destination.
 */
struct tisci_msg_rm_irq_set_req {
	struct tisci_header	hdr;
	u32			valid_params;
	u16			src_id;
	u16			src_index;
	u16			dst_id;
	u16			dst_host_irq;
	u16			ia_id;
	u16			vint;
	u16			global_event;
	u8			vint_status_bit_index;
	u8			secondary_host;
} __attribute__((__packed__));

/**
 * \brief Response to setting a peripheral to processor interrupt.
 *
 * \param hdr
 * Standard TISCI header
 */
struct tisci_msg_rm_irq_set_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Releases interrupt peripheral resources according to the valid
 * configuration provided.  The following
 * @ref tisci_msg_rm_irq_release_req::valid_params valid bit combinations are
 * allowed:
 * Interrupt Router Mux Release - Release an IR input to output mux
 *                                connection where the IR input is the
 *                                src_index and the IR output is the
 *                                dst_host_irq.  Both the src_id and the
 *                                dst_id must be the device ID of the
 *                                IR being configured.
 *   @ref tisci_msg_rm_irq_release_req::dst_id valid bit == STRUE
 *   @ref tisci_msg_rm_irq_release_req::dst_host_irq valid bit == STRUE
 *   @ref tisci_msg_rm_irq_release_req::ia_id valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_release_req::vint valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_release_req::global_event valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_release_req::vint_status_bit_index valid bit == SFALSE
 * Event to VINT Unmap Only - Clear only peripheral OES register and event to
 *                            VINT status bit mapping
 *   @ref tisci_msg_rm_irq_release_req::dst_id valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_release_req::dst_host_irq valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_release_req::ia_id valid bit == STRUE
 *   @ref tisci_msg_rm_irq_release_req::vint valid bit == STRUE
 *   @ref tisci_msg_rm_irq_release_req::global_event valid bit == STRUE
 *   @ref tisci_msg_rm_irq_release_req::vint_status_bit_index valid bit == STRUE
 * OES Register Programming Only - Only clears the OES register of the
 *                                 source.  Useful for clearing UDMAP trigger
 *                                 events and any other events that are not
 *                                 translated to the interrupt domain:
 *   @ref tisci_msg_rm_irq_release_req::dst_id valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_release_req::dst_host_irq valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_release_req::ia_id valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_release_req::vint valid bit == SFALSE
 *   @ref tisci_msg_rm_irq_release_req::global_event valid bit == STRUE
 *   @ref tisci_msg_rm_irq_release_req::vint_status_bit_index valid bit == SFALSE
 *
 * \param hdr
 * Standard TISCI header
 *
 * \param valid_params
 * Bitfield defining validity of interrupt route release parameters.  The
 * interrupt route release fields are not valid, and will not be used
 * for route release, if their corresponding valid bit is zero.  Valid bit
 * usage:
 *   0 - Valid bit for @ref tisci_msg_rm_irq_release_req::dst_id
 *   1 - Valid bit for @ref tisci_msg_rm_irq_release_req::dst_host_irq
 *   2 - Valid bit for @ref tisci_msg_rm_irq_release_req::ia_id
 *   3 - Valid bit for @ref tisci_msg_rm_irq_release_req::vint
 *   4 - Valid bit for @ref tisci_msg_rm_irq_release_req::global_event
 *   5 - Valid bit for @ref tisci_msg_rm_irq_release_req::vint_status_bit_index
 *  31 - Valid bit for @ref tisci_msg_rm_irq_release_req::secondary_host
 *
 * \param src_id
 * ID of interrupt source peripheral
 *
 * \param src_index
 * Interrupt source index within source peripheral
 *
 * \param dst_id
 * SoC IR device ID when the valid_params bits are set to release an IR
 * mux connection.  This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_DST_ID_VALID is set in
 * @ref tisci_msg_rm_irq_release_req::valid_params.
 *
 * \param dst_host_irq
 * SoC IR output index when the valid_params are set to release an IR
 * mux connection.  This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID is set in
 * @ref tisci_msg_rm_irq_release_req::valid_params.
 *
 * \param ia_id
 * Device ID of interrupt aggregator in which the virtual interrupt resides.
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_IA_ID_VALID is set in
 * @ref tisci_msg_rm_irq_release_req::valid_params.
 *
 * \param vint
 * Virtual interrupt number if the interrupt route is through an
 * interrupt aggregator.  This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_VINT_VALID is set in
 * @ref tisci_msg_rm_irq_release_req::valid_params.
 *
 * \param global_event
 * Global event mapped to interrupt aggregator virtual interrupt status bit.
 * The event is cleared from the OES register of the interrupt source.  This
 * field is only applicable for interrupt source's capable of generating
 * global events.  This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID is set in
 * @ref tisci_msg_rm_irq_release_req::valid_params.
 *
 * \param vint_status_bit_index
 * Virtual interrupt status bit to release if the interrupt route utilizes an
 * interrupt aggregator virtual interrupt.  This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID is set in
 * @ref tisci_msg_rm_irq_release_req::valid_params.
 *
 * \param secondary_host
 * The interrupt route destination is the specified secondary host if the
 * secondary_host's corresponding valid bit is set in
 * @ref tisci_msg_rm_irq_release_req::valid_params.  Otherwise, the host within
 * the TISCI message header is the route destination.
 */
struct tisci_msg_rm_irq_release_req {
	struct tisci_header	hdr;
	u32			valid_params;
	u16			src_id;
	u16			src_index;
	u16			dst_id;
	u16			dst_host_irq;
	u16			ia_id;
	u16			vint;
	u16			global_event;
	u8			vint_status_bit_index;
	u8			secondary_host;
} __attribute__((__packed__));

/**
 * \brief Response to releasing a peripheral to processor interrupt.
 *
 * \param hdr
 * Standard TISCI header
 */
struct tisci_msg_rm_irq_release_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

#endif /* RM_TISCI_IRQ_H */
