/*
 * System Firmware TISCI RM UDMAP Messaging
 *
 * TISCI Protocol Definitions for UDMAP messages
 *
 * Copyright (C) 2018-2020, Texas Instruments Incorporated
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

#ifndef RM_TISCI_UDMAP_H
#define RM_TISCI_UDMAP_H

#include <tisci/tisci_protocol.h>

/* Common declarations */

/**
 * The tx_pause_on_err and rx_pause_on_err parameters are valid for RM UDMAP
 * tx and rx channel configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERR_VALID         ((u32) 1u << 0u)
/**
 * The tx_atype and rx_atype parameters are valid for RM UDMAP
 * tx and rx channel configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_VALID                ((u32) 1u << 1u)
/**
 * The tx_chan_type and rx_chan_type parameters are valid for RM UDMAP
 * tx and rx channel configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_CHAN_TYPE_VALID            ((u32) 1u << 2u)
/**
 * The tx_fetch_size and rx_fetch_size parameters are valid for RM UDMAP
 * tx and rx channel configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_FETCH_SIZE_VALID           ((u32) 1u << 3u)
/**
 * The txcq_qnum and rxcq_qnum parameters are valid for RM UDMAP
 * tx and rx channel configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_CQ_QNUM_VALID              ((u32) 1u << 4u)
/**
 * The tx_priority and rx_priority parameters are valid for RM UDMAP
 * tx and rx channel configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_PRIORITY_VALID             ((u32) 1u << 5u)
/**
 * The tx_qos and rx_qos parameters are valid for RM UDMAP
 * tx and rx channel configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_QOS_VALID                  ((u32) 1u << 6u)
/**
 * The tx_orderid and rx_orderid parameters are valid for RM UDMAP
 * tx and rx channel configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_ORDER_ID_VALID             ((u32) 1u << 7u)
/**
 * The tx_sched_priority and rx_sched_priority parameters are valid for RM UDMAP
 * tx and rx channel configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIORITY_VALID       ((u32) 1u << 8u)
/**
 * The tx_burst_size and rx_burst_size parameters are valid for RM UDMAP
 * tx and rx channel configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_VALID           ((u32) 1u << 14U)

/**
 * On error or exception the channel will drop current work and move on
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERROR_DISABLED    (0u)
/**
 * On error or exception the channel will pause and wait for software to
 * investigate and un-pause the channel.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERROR_ENABLED     (1u)

/**
 * Pointers are physical addresses configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_atype and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_atype parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_PHYS                 (0u)
/**
 * Pointers are intermediate addresses requiring intermediate to
 * physical translation before being decoded configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_atype and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_atype parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_INTERMEDIATE         (1u)
/**
 * Pointers are virtual addresses requiring virtual to physical
 * translation before being decoded configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_atype and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_atype parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_VIRTUAL              (2u)
/**
 * Used for all non-coherent traffic like accelerator and real-time IP
 * traffic.  Configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_atype and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_atype parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_NON_COHERENT         (3U)

/**
 * Channel performs packet oriented transfers using pass by reference
 * rings configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_chan_type and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_chan_type parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_PACKET                (2u)
/**
 * Channel performs packet oriented transfers using pass by reference
 * rings with single buffer packet mode enable configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_chan_type and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_chan_type parameters.
 *
 *  NOTE: This type is only valid for UDMAP receive channel
 *        configuration
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_PACKET_SINGLE_BUF     (3u)
/**
 * Channel performs Third Party DMA transfers using pass by reference
 * rings configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_chan_type and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_chan_type parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_DMA_REF            (10u)
/**
 * Channel performs Third Party DMA transfers using pass by value
 * rings configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_chan_type and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_chan_type parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_DMA_VAL            (11u)
/**
 * Channel performs Third Party Block Copy DMA transfers using pass by
 * reference rings configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_chan_type and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_chan_type parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_BLOCK_REF          (12u)
/**
 * Channel performs Third Party Block Copy DMA transfers using pass by
 * value rings configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_chan_type and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_chan_type parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_BLOCK_VAL          (13u)

/**
 * High priority scheduling priority configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_sched_priority and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_sched_priority parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_HIGH           (0u)
/**
 * Medium to high priority scheduling priority configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_sched_priority and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_sched_priority parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_MEDHIGH        (1u)
/**
 * Medium to low priority scheduling priority configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_sched_priority and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_sched_priority parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_MEDLOW         (2u)
/**
 * Low priority scheduling priority configuration for
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_sched_priority and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_sched_priority parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_LOW            (3u)

/**
 * Maximum value allowed in @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_fetch_size
 * and @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_fetch_size
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_FETCH_SIZE_MAX             (127u)
/**
 * Value used to suppress usage of ring-based UDMAP channel parameters
 */
#define TISCI_MSG_VALUE_RM_UDMAP_QNUM_SUPPRESS                 (0xFFFFu)
/**
 * Maximum value allowed in @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_priority
 * and @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_priority
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_PRIORITY_MAX               (7u)
/**
 * Maximum value allowed in @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_qos
 * and @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_qos
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_QOS_MAX                    (7u)
/**
 * Maximum value allowed in @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_orderid
 * and @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_orderid
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_ORDER_ID_MAX               (15u)

/**
 * Burst size of 64 bytes in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_burst_size
 * and @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_burst_size
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_64_BYTES        (1U)
/**
 * Burst size of 128 bytes in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_burst_size
 * and @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_burst_size
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_128_BYTES       (2U)
/**
 * Burst size of 256 bytes in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_burst_size
 * and @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_burst_size
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_256_BYTES       (3U)

/* UDMAP transmit channel declarations */

/**
 * The tx_filt_einfo parameter is valid for RM UDMAP tx channel configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TX_FILT_EINFO_VALID        ((u32) 1U << 9U)
/**
 * The tx_filt_pswords parameter is valid for RM UDMAP tx channel configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TX_FILT_PSWORDS_VALID      ((u32) 1U << 10U)
/**
 * The tx_supr_tdpkt parameter is valid for RM UDMAP tx channel configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TX_SUPR_TDPKT_VALID        ((u32) 1U << 11U)
/**
 * The tx_credit_count parameter is valid for RM UDMAP tx channel configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TX_CREDIT_COUNT_VALID      ((u32) 1U << 12U)
/**
 * The fdepth parameter is valid for RM UDMAP tx channel configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TX_FDEPTH_VALID            ((u32) 1U << 13U)
/**
 * The tdtype parameter is valid for RM UDMAP tx channel configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_TX_TDTYPE_VALID            ((u32) 1U << 15U)

/**
 * Descriptor extended packet info (if present) will be passed by the DMA
 * controller to the back end application for UDMAP transmit channels.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_TX_CH_FILT_EINFO_DISABLED        (0u)
/**
 * Descriptor extended packet info (if present) will be filtered by the DMA
 * controller for UDMAP transmit channels.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_TX_CH_FILT_EINFO_ENABLED         (1u)
/**
 * Descriptor protocol specific words (if present) will be passed by the DMA
 * controller to the back end application for UDMAP transmit channels.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_TX_CH_FILT_PSWORDS_DISABLED      (0u)
/**
 * Descriptor protocol specific words (if present) will be filtered by the DMA
 * controller for UDMAP transmit channels.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_TX_CH_FILT_PSWORDS_ENABLED       (1u)
/**
 * Do not suppress teardown packet generation by transmit channel
 */
#define TISCI_MSG_VALUE_RM_UDMAP_TX_CH_SUPPRESS_TD_DISABLED    (0u)
/**
 * Suppress teardown packet generation by transmit channel
 */
#define TISCI_MSG_VALUE_RM_UDMAP_TX_CH_SUPPRESS_TD_ENABLED     (1u)
/**
 * Maximum value allowed in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_credit_count
 */
#define TISCI_MSG_VALUE_RM_UDMAP_TX_CH_CREDIT_CNT_MAX          (7u)
/**
 * Teardown immediately once all traffic is complete in UDMA
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_tdtype
 */
#define TISCI_MSG_VALUE_RM_UDMAP_TX_CH_TDTYPE_IMMEDIATE        (0U)
/**
 * Wait to teardown until remote peer sends back completion message
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_tdtype
 */
#define TISCI_MSG_VALUE_RM_UDMAP_TX_CH_TDTYPE_WAIT             (1U)

/* UDMAP receive channel declarations */

/**
 * The flowid_start parameter is valid for RM UDMAP rx channel configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_RX_FLOWID_START_VALID      ((u32) 1u << 9u)
/**
 * The flowid_cnt parameter is valid for RM UDMAP rx channel configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_RX_FLOWID_CNT_VALID        ((u32) 1u << 10u)
/**
 * The rx_ignore_short parameter is valid for RM UDMAP rx channel configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_RX_IGNORE_SHORT_VALID      ((u32) 1u << 11u)
/**
 * The rx_ignore_long parameter is valid for RM UDMAP rx channel configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_CH_RX_IGNORE_LONG_VALID       ((u32) 1u << 12u)

/**
 * Packets are treated as exceptions and handled appropriately by UDMAP
 * receive channels.  Used to configured receive channel short and long
 * packet treatment via @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_ignore_short
 * and @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_ignore_long.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_CH_PACKET_EXCEPTION        (0u)
/**
 * Packets are ignored by UDMAP receive channels.  Used to configured receive
 * channel short and long packet treatment via
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_ignore_short and
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_ignore_long.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_CH_PACKET_IGNORED          (1u)
/**
 * Reset value for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::flowid_cnt
 * No flow IDs other than the default, statically mapped flow are used by the
 * UDMAP receive channel.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_CH_FLOW_CNT_NONE           (0u)

/* UDMAP receive flow declarations */

/**
 * The rx_einfo_present parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_EINFO_PRESENT_VALID      ((u32) 1u << 0u)
/**
 * The rx_psinfo_present parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_PSINFO_PRESENT_VALID     ((u32) 1u << 1u)
/**
 * The rx_error_handling parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_ERROR_HANDLING_VALID     ((u32) 1u << 2u)
/**
 * The rx_desc_type parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_DESC_TYPE_VALID          ((u32) 1u << 3u)
/**
 * The rx_sop_offset parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_SOP_OFFSET_VALID         ((u32) 1u << 4u)
/**
 * The rx_dest_qnum parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_QNUM_VALID          ((u32) 1u << 5u)
/**
 * The rx_src_tag_hi parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_HI_VALID         ((u32) 1u << 6u)
/**
 * The rx_src_tag_lo parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_LO_VALID         ((u32) 1u << 7u)
/**
 * The rx_dest_tag_hi parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_HI_VALID        ((u32) 1u << 8u)
/**
 * The rx_dest_tag_lo parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_LO_VALID        ((u32) 1u << 9u)
/**
 * The rx_src_tag_hi_sel parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_HI_SEL_VALID     ((u32) 1u << 10u)
/**
 * The rx_src_tag_lo_sel parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_LO_SEL_VALID     ((u32) 1u << 11u)
/**
 * The rx_dest_tag_hi_sel parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_HI_SEL_VALID    ((u32) 1u << 12u)
/**
 * The rx_dest_tag_lo_sel parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_LO_SEL_VALID    ((u32) 1u << 13u)
/**
 * The rx_fdq0_sz0_qnum parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ0_QNUM_VALID      ((u32) 1u << 14u)
/**
 * The rx_fdq1_qnum parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ1_QNUM_VALID          ((u32) 1u << 15u)
/**
 * The rx_fdq2_qnum parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ2_QNUM_VALID          ((u32) 1u << 16u)
/**
 * The rx_fdq3_qnum parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ3_QNUM_VALID          ((u32) 1u << 17u)
/**
 * The rx_ps_location parameter is valid for RM UDMAP rx flow configure
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_PS_LOCATION_VALID        ((u32) 1u << 18u)

/**
 * The rx_size_thresh0 parameter is valid for RM UDMAP rx flow size threshold
 * configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_SIZE_THRESH0_VALID       ((u32) 1u << 0u)
/**
 * The rx_size_thresh1 parameter is valid for RM UDMAP rx flow size threshold
 * configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_SIZE_THRESH1_VALID       ((u32) 1u << 1u)
/**
 * The rx_size_thresh2 parameter is valid for RM UDMAP rx flow size threshold
 * configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_SIZE_THRESH2_VALID       ((u32) 1u << 2u)
/**
 * The rx_fdq0_sz1_qnum parameter is valid for RM UDMAP rx flow size threshold
 * configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ1_QNUM_VALID      ((u32) 1u << 3u)
/**
 * The rx_fdq0_sz2_qnum parameter is valid for RM UDMAP rx flow size threshold
 * configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ2_QNUM_VALID      ((u32) 1u << 4u)
/**
 * The rx_fdq0_sz3_qnum parameter is valid for RM UDMAP rx flow size threshold
 * configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ3_QNUM_VALID      ((u32) 1u << 5u)
/**
 * The rx_size_thresh_en parameter is valid for RM UDMAP rx flow size threshold
 * configure TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_SIZE_THRESH_EN_VALID     ((u32) 1u << 6u)

/**
 * Configure receive flow to handle extended packet info not present in the
 * received packet descriptor.  See the UDMAP section of the TRM for more
 * information on this setting.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_EINFO_NOT_PRESENT     (0u)
/**
 * Configure receive flow to handle extended packet info present in the
 * received packet descriptor.  See the UDMAP section of the TRM for more
 * information on this setting.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_EINFO_PRESENT         (1u)
/**
 * Configure receive flow to handle PS words not present in the received packet
 * descriptor.  See the UDMAP section of the TRM for more information on this
 * setting.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_PSINFO_NOT_PRESENT    (0u)
/**
 * Configure receive flow to handle PS words present in the received packet
 * descriptor.  See the UDMAP section of the TRM for more information on this
 * setting.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_PSINFO_PRESENT        (1u)
/**
 * Drop the received packet on starvation error.  See the UDMAP section of the
 * TRM for more information on this setting.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_ERR_DROP              (0u)
/**
 * Re-try descriptor allocation operation on starvation error.  See the UDMAP
 * section of the TRM for more information on this setting.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_ERR_RETRY             (1u)
/**
 * Configure receive flow to place the PS words at the end of the packet
 * descriptor.  See the UDMAP section of the TRM for more information on this
 * setting.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_PS_END_PD             (0u)
/**
 * Configure receive flow to place the PS words at the beginning of the data
 * buffer.  See the UDMAP section of the TRM for more information on this
 * setting.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_PS_BEGIN_DB           (1u)

/**
 * Host descriptor configure for
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_desc_type
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DESC_HOST             (0u)
/**
 * Monolithic descriptor configure for
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_desc_type
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DESC_MONO             (2u)

/**
 * Do not overwrite.  Source tag byte selector configuration for
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_hi_sel and
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_lo_sel parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_NONE       (0u)
/**
 * Overwrite with value in rx_src_tag_hi or rx_src_tag_lo parameters
 * of tisci_msg_rm_udmap_flow_cfg_req for hi_sel
 * and lo_sel parameters, respectively.  Source tag byte
 * selector configuration for
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_hi_sel and
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_lo_sel parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_CFG_TAG    (1u)
/**
 * Overwrite with flow_id[7:0] from back end application.  Source tag
 * byte selector configuration for
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_hi_sel and
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_lo_sel parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_FLOW_ID    (2u)
/**
 * Overwrite with src_tag[7:0] from back end application.  Source tag
 * byte selector configuration for
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_hi_sel and
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_lo_sel parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_SRC_TAG    (4u)

/**
 * Do not overwrite destination tag byte selector configuration for
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_hi_sel and
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_lo_sel parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_NONE      (0u)
/**
 * Overwrite with value in rx_dest_tag_hi or rx_dest_tag_lo parameters of
 * tisci_msg_rm_udmap_flow_cfg_req for hi_sel and lo_sel parameters,
 * respectively.  Destination tag byte selector configuration for
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_hi_sel and
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_lo_sel parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_CFG_TAG   (1u)
/**
 * Overwrite with flow_id[7:0] from back end application destination tag
 * byte selector configuration for
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_hi_sel and
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_lo_sel parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_FLOW_ID   (2u)
/**
 * Overwrite with src_tag[7:0] from back end application destination tag
 * byte selector configuration for
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_hi_sel and
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_lo_sel parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_DEST_TAG_LO (4u)
/**
 * Overwrite with src_tag[15:8] from back end application destination tag
 * byte selector configuration for
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_hi_sel and
 * @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_lo_sel parameters.
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_DEST_TAG_HI (5u)

/**
 * The receive flow start of packet offset maximum byte offset
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SOP_MAX               (255u)
/**
 * Enable usage of size threshold 0 in
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::rx_size_thresh_en
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SIZE_THRESH_0_ENABLE  (1U)
/**
 * Enable usage of size threshold 1 in
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::rx_size_thresh_en
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SIZE_THRESH_1_ENABLE  (2U)
/**
 * Enable usage of size threshold 2 in
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::rx_size_thresh_en
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SIZE_THRESH_2_ENABLE  (4U)
/**
 * Maximum encoded size threshold setting in
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::rx_size_thresh_en
 */
#define TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SIZE_THRESH_MAX       (7u)

/* Flow delegation declarations */

/**
 * The delegated_host parameter is valid for RM UDMAP flow delegation
 * TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_DELEGATE_HOST_VALID      ((u32) 1U << 0U)
/**
 * The clear parameter is valid for RM UDMAP flow delegation TISCI message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_DELEGATE_CLEAR_VALID     ((u32) 1U << 1U)

/**
 * Clear flow delegation setting in
 * @ref tisci_msg_rm_udmap_flow_delegate_req::clear
 */
#define TISCI_MSG_VALUE_RM_UDMAP_FLOW_DELEGATE_CLEAR           (1U)

/* Global configuration declarations */

/**
 * The perf_ctrl register value is valid for UDMAP global configuration TISCI
 * message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_GCFG_PERF_CTRL_VALID          ((u32) 1U << 0U)
/**
 * The emu_ctrl register value is valid for UDMAP global configuration TISCI
 * message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_GCFG_EMU_CTRL_VALID           ((u32) 1U << 1U)
/**
 * The psil_to register value is valid for UDMAP global configuration TISCI
 * message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_GCFG_PSIL_TO_VALID            ((u32) 1U << 2U)
/**
 * The rflowfwstat register value is valid for UDMAP global configuration TISCI
 * message
 */
#define TISCI_MSG_VALUE_RM_UDMAP_GCFG_RFLOWFWSTAT_VALID        ((u32) 1U << 3U)

/**
 * \brief Configures a Navigator Subsystem UDMAP global configuration region.
 * Configures the non-real-time registers of a Navigator Subsystem UDMAP
 * global configuration region.  The GCFG region being programmed  must be
 * assigned to the host defined in the TISCI header via the RM board
 * configuration resource assignment array.  Individual fields for registers
 * specified as valid are not checked for correctness.  It is the application's
 * responsibility to verify if the register fields are being set according to
 * the device specification.
 *
 * \param hdr
 * Standard TISCI header
 *
 * \param valid_params
 * Bitfield defining validity of global configuration parameters.  The
 * configuration fields are not valid, and will not be used for global
 * configuration, if their corresponding valid bit is zero.  Valid bit usage:
 *    0 - Valid bit for @ref tisci_msg_rm_udmap_gcfg_cfg_req::perf_ctrl
 *    1 - Valid bit for @ref tisci_msg_rm_udmap_gcfg_cfg_req::emu_ctrl
 *    2 - Valid bit for @ref tisci_msg_rm_udmap_gcfg_cfg_req::psil_to
 *    3 - Valid bit for @ref tisci_msg_rm_udmap_gcfg_cfg_req::rflowfwstat
 *
 * \param nav_id
 * SoC device ID of Navigator Subsystem where global configuration is located
 *
 * \param perf_ctrl
 * Configures the performance control register.
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_GCFG_PERF_CTRL_VALID is set in
 * @ref tisci_msg_rm_udmap_gcfg_cfg_req::valid_params.
 *
 * \param emu_ctrl
 * Configures the emulation control register.
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_GCFG_EMU_CTRL_VALID is set in
 * @ref tisci_msg_rm_udmap_gcfg_cfg_req::valid_params.
 *
 * \param psil_to
 * Configures the PSI-L proxy timeout register.
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_GCFG_PSIL_TO_VALID is set in
 * @ref tisci_msg_rm_udmap_gcfg_cfg_req::valid_params.
 *
 * \param rflowfwstat
 * Writes the rx flow ID firewall status register.
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_GCFG_RFLOWFWSTAT_VALID is set in
 * @ref tisci_msg_rm_udmap_gcfg_cfg_req::valid_params.
 */
struct tisci_msg_rm_udmap_gcfg_cfg_req {
	struct tisci_header	hdr;
	u32			valid_params;
	u16			nav_id;
	u32			perf_ctrl;
	u32			emu_ctrl;
	u32			psil_to;
	u32			rflowfwstat;
} __attribute__((__packed__));

/**
 * \brief Response to configuring UDMAP global configuration.
 *
 * \param hdr
 * Standard TISCI header
 */
struct tisci_msg_rm_udmap_gcfg_cfg_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Configures a Navigator Subsystem UDMAP transmit channel
 *
 * Configures the non-real-time registers of a Navigator Subsystem UDMAP
 * transmit channel.  The channel index must be assigned to the host defined
 * in the TISCI header via the RM board configuration resource assignment
 * range list.
 *
 * \param hdr
 * Standard TISCI header
 *
 * \param valid_params
 * Bitfield defining validity of tx channel configuration parameters.  The
 * tx channel configuration fields are not valid, and will not be used for ch
 * configuration, if their corresponding valid bit is zero.  Valid bit usage:
 *    0 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_pause_on_err
 *    1 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_atype
 *    2 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_chan_type
 *    3 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_fetch_size
 *    4 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::txcq_qnum
 *    5 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_priority
 *    6 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_qos
 *    7 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_orderid
 *    8 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_sched_priority
 *    9 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_filt_einfo
 *   10 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_filt_pswords
 *   11 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_supr_tdpkt
 *   12 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_credit_count
 *   13 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::fdepth
 *   14 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_burst_size
 *   15 - Valid bit for @ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_tdtype
 *
 * \param nav_id
 * SoC device ID of Navigator Subsystem where tx channel is located
 *
 * \param index
 * UDMAP transmit channel index.
 *
 * \param tx_pause_on_err
 * UDMAP transmit channel pause on error configuration to be programmed into the
 * tx_pause_on_err field of the channel's TCHAN_TCFG register.  Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERROR_DISABLED
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERROR_ENABLED
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERR_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_filt_einfo
 * UDMAP transmit channel extended packet information passing configuration to
 * be programmed into the tx_filt_einfo field of the channel's TCHAN_TCFG
 * register.  Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_TX_CH_FILT_EINFO_DISABLED
 * @ref TISCI_MSG_VALUE_RM_UDMAP_TX_CH_FILT_EINFO_ENABLED
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TX_FILT_EINFO_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_filt_pswords
 * UDMAP transmit channel protocol specific word passing configuration to be
 * programmed into the tx_filt_pswords field of the channel's TCHAN_TCFG
 * register.  Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_TX_CH_FILT_PSWORDS_DISABLED
 * @ref TISCI_MSG_VALUE_RM_UDMAP_TX_CH_FILT_PSWORDS_ENABLED
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TX_FILT_PSWORDS_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_atype
 * UDMAP transmit channel non Ring Accelerator access pointer interpretation
 * configuration to be programmed into the tx_atype field of the channel's
 * TCHAN_TCFG register.  Can be set to
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_PHYS
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_INTERMEDIATE
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_VIRTUAL
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_NON_COHERENT
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_chan_type
 * UDMAP transmit channel functional channel type and work passing mechanism
 * configuration to be programmed into the tx_chan_type field of the channel's
 * TCHAN_TCFG register.  Can be set to
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_PACKET
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_DMA_REF
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_DMA_VAL
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_BLOCK_REF
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_BLOCK_VAL
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_CHAN_TYPE_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_supr_tdpkt
 * UDMAP transmit channel teardown packet generation suppression configuration
 * to be programmed into the tx_supr_tdpkt field of the channel's TCHAN_TCFG
 * register.  Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_TX_CH_SUPPRESS_TD_DISABLED
 * @ref TISCI_MSG_VALUE_RM_UDMAP_TX_CH_SUPPRESS_TD_ENABLED
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TX_SUPR_TDPKT_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_fetch_size
 * UDMAP transmit channel number of 32-bit descriptor words to fetch
 * configuration to be programmed into the tx_fetch_size field of the channel's
 * TCHAN_TCFG register.  The user must make sure to set the maximum word count
 * that can pass through the channel for any allowed descriptor type.  Cannot
 * be greater than @ref TISCI_MSG_VALUE_RM_UDMAP_CH_FETCH_SIZE_MAX
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_FETCH_SIZE_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_credit_count
 * UDMAP transmit channel transfer request credit count configuration to be
 * programmed into the count field of the TCHAN_TCREDIT register.  Specifies how
 * many credits for complete TRs are available.  This field is only used when
 * configuring a transmit channel of external type and cannot be greater than
 * @ref TISCI_MSG_VALUE_RM_UDMAP_TX_CH_CREDIT_CNT_MAX
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TX_CREDIT_COUNT_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param txcq_qnum
 * UDMAP transmit channel completion queue configuration to be programmed into
 * the txcq_qnum field of the TCHAN_TCQ register.  The specified completion
 * queue must be assigned to the host, or a subordinate of the host, requesting
 * configuration of the transmit channel.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_CQ_QNUM_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_priority
 * UDMAP transmit channel transmit priority value to be programmed into the
 * priority field of the channel's TCHAN_TPRI_CTRL register.  This parameter
 * cannot be greater than @ref TISCI_MSG_VALUE_RM_UDMAP_CH_PRIORITY_MAX.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_PRIORITY_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_qos
 * UDMAP transmit channel transmit qos value to be programmed into the
 * qos field of the channel's TCHAN_TPRI_CTRL register.  This parameter
 * cannot be greater than @ref TISCI_MSG_VALUE_RM_UDMAP_CH_QOS_MAX.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_QOS_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_orderid
 * UDMAP transmit channel bus order id value to be programmed into the
 * orderid field of the channel's TCHAN_TPRI_CTRL register.  This parameter
 * cannot be greater than @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ORDER_ID_MAX.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ORDER_ID_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param fdepth
 * UDMAP transmit channel FIFO depth configuration to be programmed into the
 * fdepth field of the TCHAN_TFIFO_DEPTH register.  Sets the number of Tx
 * FIFO bytes which are allowed to be stored for the channel.  This field is
 * not supported for external channels.  The TISCI message is rejected if a
 * non-zero, valid, value is provided during external channel configuration.
 * Check the UDMAP section of the TRM for restrictions regarding this parameter.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TX_FDEPTH_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_sched_priority
 * UDMAP transmit channel tx scheduling priority configuration to be programmed
 * into the priority field of the channel's TCHAN_TST_SCHED register.  Can be
 * set to
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_HIGH
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_MEDHIGH
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_MEDLOW
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_LOW
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIORITY_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.
 *
 * \param tx_burst_size
 * UDMAP transmit channel burst size configuration to be programmed
 * into the tx_burst_size field of the TCHAN_TCFG register.  Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_64_BYTES
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_128_BYTES
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_256_BYTES
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.  This field is not
 * supported on some SoCs.  On SoCs that do not support this field the input
 * is quietly ignored even if the valid bit is set.
 *
 * \param tx_tdtype
 * UDMAP transmit channel teardown type configuration to be programmed
 * into the tdtype field of the TCHAN_TCFG register.  Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_TX_CH_TDTYPE_IMMEDIATE
 * @ref TISCI_MSG_VALUE_RM_UDMAP_TX_CH_TDTYPE_WAIT
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TX_TDTYPE_VALID is set in
 * @ref tisci_msg_rm_udmap_tx_ch_cfg_req::valid_params.  This field is not
 * supported on some SoCs.  On SoCs that do not support this field the input
 * is quietly ignored even if the valid bit is set.
 */
struct tisci_msg_rm_udmap_tx_ch_cfg_req {
	struct tisci_header	hdr;
	u32			valid_params;
	u16			nav_id;
	u16			index;
	u8			tx_pause_on_err;
	u8			tx_filt_einfo;
	u8			tx_filt_pswords;
	u8			tx_atype;
	u8			tx_chan_type;
	u8			tx_supr_tdpkt;
	u16			tx_fetch_size;
	u8			tx_credit_count;
	u16			txcq_qnum;
	u8			tx_priority;
	u8			tx_qos;
	u8			tx_orderid;
	u16			fdepth;
	u8			tx_sched_priority;
	u8			tx_burst_size;
	u8			tx_tdtype;
} __attribute__((__packed__));

/**
 * \brief Response to configuring a UDMAP transmit channel.
 *
 * \param hdr
 * Standard TISCI header
 */
struct tisci_msg_rm_udmap_tx_ch_cfg_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Configures a Navigator Subsystem UDMAP receive channel
 *
 * Configures the non-real-time registers of a Navigator Subsystem UDMAP
 * receive channel.  The channel index must be assigned to the host defined
 * in the TISCI header via the RM board configuration resource assignment
 * range list.
 *
 * \param hdr
 * Standard TISCI header
 *
 * \param valid_params
 * Bitfield defining validity of rx channel configuration parameters.  The
 * rx channel configuration fields are not valid, and will not be used for ch
 * configuration, if their corresponding valid bit is zero.  Valid bit usage:
 *    0 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_pause_on_err
 *    1 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_atype
 *    2 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_chan_type
 *    3 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_fetch_size
 *    4 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rxcq_qnum
 *    5 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_priority
 *    6 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_qos
 *    7 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_orderid
 *    8 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_sched_priority
 *    9 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::flowid_start
 *   10 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::flowid_cnt
 *   11 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_ignore_short
 *   12 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_ignore_long
 *   14 - Valid bit for @ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_burst_size
 *
 * \param nav_id
 * SoC device ID of Navigator Subsystem where rx channel is located
 *
 * \param index
 * UDMAP receive channel index.
 *
 * \param rx_fetch_size
 * UDMAP receive channel number of 32-bit descriptor words to fetch
 * configuration to be programmed into the rx_fetch_size field of the channel's
 * RCHAN_RCFG register.  The user must make sure to set the maximum word count
 * that can pass through the channel for any allowed descriptor type.  Cannot
 * be greater than @ref TISCI_MSG_VALUE_RM_UDMAP_CH_FETCH_SIZE_MAX
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_FETCH_SIZE_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param rxcq_qnum
 * UDMAP receive channel completion queue configuration to be programmed into
 * the rxcq_qnum field of the RCHAN_RCQ register.  The specified completion
 * queue must be assigned to the host, or a subordinate of the host, requesting
 * configuration of the receive channel.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_CQ_QNUM_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param rx_priority
 * UDMAP receive channel receive priority value to be programmed into the
 * priority field of the channel's RCHAN_RPRI_CTRL register.  This parameter
 * cannot be greater than @ref TISCI_MSG_VALUE_RM_UDMAP_CH_PRIORITY_MAX.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_PRIORITY_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param rx_qos
 * UDMAP receive channel receive qos value to be programmed into the
 * qos field of the channel's RCHAN_RPRI_CTRL register.  This parameter
 * cannot be greater than @ref TISCI_MSG_VALUE_RM_UDMAP_CH_QOS_MAX.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_QOS_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param rx_orderid
 * UDMAP receive channel bus order id value to be programmed into the
 * orderid field of the channel's RCHAN_RPRI_CTRL register.  This parameter
 * cannot be greater than @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ORDER_ID_MAX.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ORDER_ID_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param rx_sched_priority
 * UDMAP receive channel rx scheduling priority configuration to be programmed
 * into the priority field of the channel's RCHAN_RST_SCHED register.  Can be
 * set to
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_HIGH
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_MEDHIGH
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_MEDLOW
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIOR_LOW
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_SCHED_PRIORITY_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param flowid_start
 * UDMAP receive channel additional flows starting index configuration to
 * program into the flow_start field of the RCHAN_RFLOW_RNG register.  Specifies
 * the starting index for flow IDs the receive channel is to make use of beyond
 * the default flow.  flowid_start and @ref flowid_cnt must be set as valid and
 * configured together.  The starting flow ID set by @ref flowid_cnt must be a
 * flow index within the Navigator Subsystem's subset of flows beyond the
 * default flows statically mapped to receive channels.  The additional flows
 * must be assigned to the host, or a subordinate of the host, requesting
 * configuration of the receive channel.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_RX_FLOWID_START_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param flowid_cnt
 * UDMAP receive channel additional flows count configuration to program into
 * the flowid_cnt field of the RCHAN_RFLOW_RNG register.  This field specifies
 * how many flow IDs are in the additional contiguous range of legal flow IDs
 * for the channel.  @ref flowid_start and flowid_cnt must be set as valid and
 * configured together.  Disabling the valid_params field bit for flowid_cnt
 * indicates no flow IDs other than the default are to be allocated and used by
 * the receive channel.  @ref flowid_start plus flowid_cnt cannot be greater
 * than the number of receive flows in the receive channel's Navigator
 * Subsystem.  The additional flows must be assigned to the host, or a
 * subordinate of the host, requesting configuration of the receive channel.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_RX_FLOWID_CNT_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param rx_pause_on_err
 * UDMAP receive channel pause on error configuration to be programmed into the
 * rx_pause_on_err field of the channel's RCHAN_RCFG register.  Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERROR_DISABLED
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERROR_ENABLED
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERR_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param rx_atype
 * UDMAP receive channel non Ring Accelerator access pointer interpretation
 * configuration to be programmed into the rx_atype field of the channel's
 * RCHAN_RCFG register.  Can be set to
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_PHYS
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_INTERMEDIATE
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_VIRTUAL
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_NON_COHERENT
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param rx_chan_type
 * UDMAP receive channel functional channel type and work passing mechanism
 * configuration to be programmed into the rx_chan_type field of the channel's
 * RCHAN_RCFG register.  Can be set to
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_PACKET
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_PACKET_SINGLE_BUF
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_DMA_REF
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_DMA_VAL
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_BLOCK_REF
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_TYPE_3P_BLOCK_VAL
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_CHAN_TYPE_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param rx_ignore_short
 * UDMAP receive channel short packet treatment configuration to be programmed
 * into the rx_ignore_short field of the RCHAN_RCFG register.  Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_CH_PACKET_EXCEPTION
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_CH_PACKET_IGNORED
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_RX_IGNORE_SHORT_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param rx_ignore_long
 * UDMAP receive channel long packet treatment configuration to be programmed
 * into the rx_ignore_long field of the RCHAN_RCFG register.  Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_CH_PACKET_EXCEPTION
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_CH_PACKET_IGNORED
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_RX_IGNORE_LONG_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.
 *
 * \param rx_burst_size
 * UDMAP receive channel burst size configuration to be programmed
 * into the rx_burst_size field of the RCHAN_RCFG register.  Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_64_BYTES
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_128_BYTES
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_256_BYTES
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_VALID is set in
 * @ref tisci_msg_rm_udmap_rx_ch_cfg_req::valid_params.  This field is not
 * supported on some SoCs.  On SoCs that do not support this field the input
 * is quietly ignored even if the valid bit is set.
 */
struct tisci_msg_rm_udmap_rx_ch_cfg_req {
	struct tisci_header	hdr;
	u32			valid_params;
	u16			nav_id;
	u16			index;
	u16			rx_fetch_size;
	u16			rxcq_qnum;
	u8			rx_priority;
	u8			rx_qos;
	u8			rx_orderid;
	u8			rx_sched_priority;
	u16			flowid_start;
	u16			flowid_cnt;
	u8			rx_pause_on_err;
	u8			rx_atype;
	u8			rx_chan_type;
	u8			rx_ignore_short;
	u8			rx_ignore_long;
	u8			rx_burst_size;
} __attribute__((__packed__));

/**
 * \brief Response to configuring a UDMAP receive channel.
 *
 * \param hdr
 * Standard TISCI header
 */
struct tisci_msg_rm_udmap_rx_ch_cfg_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Configures a Navigator Subsystem UDMAP receive flow
 *
 * Configures a Navigator Subsystem UDMAP receive flow's registers.
 * Configuration does not include the flow registers which handle size-based
 * free descriptor queue routing.  The
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req message is used to
 * configure register fields related to size based free descriptor queues.
 *
 * The flow index must be assigned to the host defined in the TISCI header via
 * the RM board configuration resource assignment range list.
 *
 * It's the user's responsibility to make sure any receive channels using the
 * flow are disabled when changing the receive flow configuration.  Otherwise,
 * unknown operation may occur.
 *
 * \param hdr
 * Standard TISCI header
 *
 * \param valid_params
 * Bitfield defining validity of rx flow configuration parameters.  The
 * rx flow configuration fields are not valid, and will not be used for flow
 * configuration, if their corresponding valid bit is zero.  Valid bit usage:
 *     0 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_einfo_present
 *     1 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_psinfo_present
 *     2 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_error_handling
 *     3 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_desc_type
 *     4 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_sop_offset
 *     5 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_qnum
 *     6 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_hi
 *     7 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_lo
 *     8 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_hi
 *     9 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_lo
 *    10 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_hi_sel
 *    11 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_src_tag_lo_sel
 *    12 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_hi_sel
 *    13 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_dest_tag_lo_sel
 *    14 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_fdq0_sz0_qnum
 *    15 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_fdq1_qnum
 *    16 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_fdq2_qnum
 *    17 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_fdq3_qnum
 *    18 - Valid bit for
 *         @ref tisci_msg_rm_udmap_flow_cfg_req::rx_ps_location
 *
 * \param nav_id
 * SoC device ID of Navigator Subsystem from which the receive flow is
 * allocated
 *
 * \param flow_index
 * UDMAP receive flow index for non-optional configuration.
 *
 * \param rx_einfo_present
 * UDMAP receive flow extended packet info present configuration to be
 * programmed into the rx_einfo_present field of the flow's RFLOW_RFA register.
 * Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_EINFO_NOT_PRESENT
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_EINFO_PRESENT
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_EINFO_PRESENT_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_psinfo_present
 * UDMAP receive flow PS words present configuration to be programmed into the
 * rx_psinfo_present field of the flow's RFLOW_RFA register. Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_PSINFO_NOT_PRESENT
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_PSINFO_PRESENT
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_PSINFO_PRESENT_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_error_handling
 * UDMAP receive flow error handling configuration to be programmed into the
 * rx_error_handling field of the flow's RFLOW_RFA register.  Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_ERR_DROP
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_ERR_RETRY
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_ERROR_HANDLING_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_desc_type
 * UDMAP receive flow descriptor type configuration to be programmed into the
 * rx_desc_type field field of the flow's RFLOW_RFA register.  Can be set to
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DESC_HOST
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DESC_MONO
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_DESC_TYPE_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_sop_offset
 * UDMAP receive flow start of packet offset configuration to be programmed
 * into the rx_sop_offset field of the RFLOW_RFA register.  See the UDMAP
 * section of the TRM for more information on this setting.  Valid values for
 * this field are 0-255 bytes.  The allocation request will be NACK'd if
 * specified offset is greater than @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SOP_MAX.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_SOP_OFFSET_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_dest_qnum
 * UDMAP receive flow destination queue configuration to be programmed into the
 * rx_dest_qnum field of the flow's RFLOW_RFA register.  The specified
 * destination queue must be valid within the Navigator Subsystem and must be
 * owned by the host, or a subordinate of the host, requesting allocation and
 * configuration of the receive flow.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_QNUM_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_src_tag_hi
 * UDMAP receive flow source tag high byte constant configuration to be
 * programmed into the rx_src_tag_hi field of the flow's RFLOW_RFB register.
 * See the UDMAP section of the TRM for more information on this setting.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_HI_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_src_tag_lo
 * UDMAP receive flow source tag low byte constant configuration to be
 * programmed into the rx_src_tag_lo field of the flow's RFLOW_RFB register.
 * See the UDMAP section of the TRM for more information on this setting.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_LO_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_dest_tag_hi
 * UDMAP receive flow destination tag high byte constant configuration to be
 * programmed into the rx_dest_tag_hi field of the flow's RFLOW_RFB register.
 * See the UDMAP section of the TRM for more information on this setting.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_HI_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_dest_tag_lo
 * UDMAP receive flow destination tag low byte constant configuration to be
 * programmed into the rx_dest_tag_lo field of the flow's RFLOW_RFB register.
 * See the UDMAP section of the TRM for more information on this setting.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_LO_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_src_tag_hi_sel
 * UDMAP receive flow source tag high byte selector configuration to be
 * programmed into the rx_src_tag_hi_sel field of the RFLOW_RFC register.  See
 * the UDMAP section of the TRM for more information on this setting.  Can be
 * set to
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_NONE
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_CFG_TAG
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_FLOW_ID
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_SRC_TAG
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_HI_SEL_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_src_tag_lo_sel
 * UDMAP receive flow source tag low byte selector configuration to be
 * programmed into the rx_src_tag_lo_sel field of the RFLOW_RFC register.  See
 * the UDMAP section of the TRM for more information on this setting.  Can be
 * set to
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_NONE
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_CFG_TAG
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_FLOW_ID
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SRC_SELECT_SRC_TAG
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_LO_SEL_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_dest_tag_hi_sel
 * UDMAP receive flow destination tag high byte selector configuration to be
 * programmed into the rx_dest_tag_hi_sel field of the RFLOW_RFC register.  See
 * the UDMAP section of the TRM for more information on this setting.  Can be
 * set to
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_NONE
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_CFG_TAG
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_FLOW_ID
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_DEST_TAG_LO
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_DEST_TAG_HI
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_HI_SEL_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_dest_tag_lo_sel
 * UDMAP receive flow destination tag low byte selector configuration to be
 * programmed into the rx_dest_tag_lo_sel field of the RFLOW_RFC register.  See
 * the UDMAP section of the TRM for more information on this setting.  Can be
 * set to
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_NONE
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_CFG_TAG
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_FLOW_ID
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_DEST_TAG_LO
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_DEST_SELECT_DEST_TAG_HI
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_LO_SEL_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_fdq0_sz0_qnum
 * UDMAP receive flow free descriptor queue 0 configuration to be programmed
 * into the rx_fdq0_sz0_qnum field of the flow's RFLOW_RFD register.  See the
 * UDMAP section of the TRM for more information on this setting.  The specified
 * free queue must be valid within the Navigator Subsystem and must be owned
 * by the host, or a subordinate of the host, requesting allocation and
 * configuration of the receive flow.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ0_QNUM_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_fdq1_qnum
 * UDMAP receive flow free descriptor queue 1 configuration to be programmed
 * into the rx_fdq1_qnum field of the flow's RFLOW_RFD register.  See the
 * UDMAP section of the TRM for more information on this setting.  The specified
 * free queue must be valid within the Navigator Subsystem and must be owned
 * by the host, or a subordinate of the host, requesting allocation and
 * configuration of the receive flow.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ1_QNUM_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_fdq2_qnum
 * UDMAP receive flow free descriptor queue 2 configuration to be programmed
 * into the rx_fdq2_qnum field of the flow's RFLOW_RFE register.  See the
 * UDMAP section of the TRM for more information on this setting.  The specified
 * free queue must be valid within the Navigator Subsystem and must be owned
 * by the host, or a subordinate of the host, requesting allocation and
 * configuration of the receive flow.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ2_QNUM_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_fdq3_qnum
 * UDMAP receive flow free descriptor queue 3 configuration to be programmed
 * into the rx_fdq3_qnum field of the flow's RFLOW_RFE register.  See the
 * UDMAP section of the TRM for more information on this setting.  The specified
 * free queue must be valid within the Navigator Subsystem and must be owned
 * by the host, or a subordinate of the host, requesting allocation and
 * configuration of the receive flow.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ3_QNUM_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 *
 * \param rx_ps_location
 * UDMAP receive flow PS words location configuration to be programmed into the
 * rx_ps_location field of the flow's RFLOW_RFA register. Can be set to:
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_PS_END_PD
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_PS_BEGIN_DB
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_PS_LOCATION_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_cfg_req::valid_params.
 */
struct tisci_msg_rm_udmap_flow_cfg_req {
	struct tisci_header	hdr;
	u32			valid_params;
	u16			nav_id;
	u16			flow_index;
	u8			rx_einfo_present;
	u8			rx_psinfo_present;
	u8			rx_error_handling;
	u8			rx_desc_type;
	u16			rx_sop_offset;
	u16			rx_dest_qnum;
	u8			rx_src_tag_hi;
	u8			rx_src_tag_lo;
	u8			rx_dest_tag_hi;
	u8			rx_dest_tag_lo;
	u8			rx_src_tag_hi_sel;
	u8			rx_src_tag_lo_sel;
	u8			rx_dest_tag_hi_sel;
	u8			rx_dest_tag_lo_sel;
	u16			rx_fdq0_sz0_qnum;
	u16			rx_fdq1_qnum;
	u16			rx_fdq2_qnum;
	u16			rx_fdq3_qnum;
	u8			rx_ps_location;
} __attribute__((__packed__));

/**
 * \brief Response to configuring a Navigator Subsystem UDMAP receive flow
 *
 * \param hdr
 * Standard TISCI header
 */
struct tisci_msg_rm_udmap_flow_cfg_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Configures a Navigator Subsystem UDMAP receive flow's size threshold
 *        fields.
 *
 * Configures a Navigator Subsystem UDMAP receive flow's size threshold fields
 *
 * The flow index must be assigned to the host defined in the TISCI header via
 * the RM board configuration resource assignment range list.
 *
 * It's the user's responsibility to make sure any receive channels using the
 * flow are disabled when changing the receive flow configuration.  Otherwise,
 * unknown operation may occur.
 *
 * \param hdr
 * Standard TISCI header
 *
 * \param valid_params
 * Bitfield defining validity of rx flow configuration parameters.  The
 * rx flow configuration fields are not valid, and will not be used for flow
 * configuration, if their corresponding valid bit is zero.  Valid bit usage:
 *    0 - Valid bit for
 *        @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::rx_size_thresh0
 *    1 - Valid bit for
 *        @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::rx_size_thresh1
 *    2 - Valid bit for
 *        @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::rx_size_thresh2
 *    3 - Valid bit for
 *        @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::rx_fdq0_sz1_qnum
 *    4 - Valid bit for
 *        @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::rx_fdq0_sz2_qnum
 *    5 - Valid bit for
 *        @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::rx_fdq0_sz3_qnum
 *    6 - Valid bit for
 *        @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::rx_size_thresh_en
 *
 * \param nav_id
 * SoC device ID of Navigator Subsystem from which the receive flow is
 * allocated
 *
 * \param flow_index
 * UDMAP receive flow index for optional configuration.
 *
 * \param rx_size_thresh0
 * UDMAP receive flow packet size threshold 0 configuration to be programmed
 * into the rx_size_thresh0 field of the flow's RFLOW_RFF register.  The
 * value must be provided in 32-byte units due to a 5-bit left shift performed
 * by the hardware prior to comparison to packet size.  See the UDMAP section
 * of the TRM for more information on this setting and the shift on comparison.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_SIZE_THRESH0_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::valid_params.
 *
 * \param rx_size_thresh1
 * UDMAP receive flow packet size threshold 1 configuration to be programmed
 * into the rx_size_thresh1 field of the flow's RFLOW_RFF register.  The
 * value must be provided in 32-byte units due to a 5-bit left shift performed
 * by the hardware prior to comparison to packet size.  See the UDMAP section
 * of the TRM for more information on this setting and the shift on comparison.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_SIZE_THRESH1_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::valid_params.
 *
 * \param rx_size_thresh2
 * UDMAP receive flow packet size threshold 2 configuration to be programmed
 * into the rx_size_thresh2 field of the flow's RFLOW_RFG register.  The
 * value must be provided in 32-byte units due to a 5-bit left shift performed
 * by the hardware prior to comparison to packet size.  See the UDMAP section
 * of the TRM for more information on this setting and the shift on comparison.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_SIZE_THRESH2_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::valid_params.
 *
 * \param rx_fdq0_sz1_qnum
 * UDMAP receive flow free descriptor queue for size threshold 1 configuration
 * to be programmed into the rx_fdq0_sz1_qnum field of the flow's RFLOW_RFG
 * register.  See the UDMAP section of the TRM for more information on this
 * setting.  The specified free queue must be valid within the Navigator
 * Subsystem and must be owned by the host, or a subordinate of the host, who
 * owns the receive flow index and who is making the optional configuration
 * request.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ1_QNUM_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::valid_params.
 *
 * \param rx_fdq0_sz2_qnum
 * UDMAP receive flow free descriptor queue for size threshold 2 configuration
 * to be programmed into the rx_fdq0_sz2_qnum field of the flow's RFLOW_RFH
 * register.  See the UDMAP section of the TRM for more information on this
 * setting.  The specified free queue must be valid within the Navigator
 * Subsystem and must be owned by the host, or a subordinate of the host, who
 * owns the receive flow index and who is making the optional configuration
 * request.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ2_QNUM_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::valid_params.
 *
 * \param rx_fdq0_sz3_qnum
 * UDMAP receive flow free descriptor queue for size threshold 3 configuration
 * to be programmed into the rx_fdq0_sz3_qnum field of the flow's RFLOW_RFH
 * register.  See the UDMAP section of the TRM for more information on this
 * setting.  The specified free queue must be valid within the Navigator
 * Subsystem and must be owned by the host, or a subordinate of the host, who
 * owns the receive flow index and who is making the optional configuration
 * request.
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ3_QNUM_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::valid_params.
 *
 * \param rx_size_thresh_en
 * UDMAP receive flow packet size based free buffer queue enable configuration
 * to be programmed into the rx_size_thresh_en field of the RFLOW_RFC register.
 * See the UDMAP section of the TRM for more information on this setting.
 * This parameter can be no greater than
 * @ref TISCI_MSG_VALUE_RM_UDMAP_RX_FLOW_SIZE_THRESH_MAX
 *
 * This field is only valid if
 * @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_SIZE_THRESH_EN_VALID is set in
 * @ref tisci_msg_rm_udmap_flow_size_thresh_cfg_req::valid_params.
 */
struct tisci_msg_rm_udmap_flow_size_thresh_cfg_req {
	struct tisci_header	hdr;
	u32			valid_params;
	u16			nav_id;
	u16			flow_index;
	u16			rx_size_thresh0;
	u16			rx_size_thresh1;
	u16			rx_size_thresh2;
	u16			rx_fdq0_sz1_qnum;
	u16			rx_fdq0_sz2_qnum;
	u16			rx_fdq0_sz3_qnum;
	u8			rx_size_thresh_en;
} __attribute__((__packed__));

/**
 * \brief Response to configuring a Navigator Subsystem UDMAP receive flow's
 *	  size threshold fields.
 *
 * \param hdr
 * Standard TISCI header
 */
struct tisci_msg_rm_udmap_flow_size_thresh_cfg_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

/**
 * \brief Delegates the specified flow to another host for configuration.  Only
 *        the original owner of the flow, as specified in the RM board
 *        configuration resource entries, can delegate an additional host as
 *        able to configure the flow.  A flow's delegation can be cleared by
 *        the original owner of the flow using the clear parameter.
 *
 * \param hdr Standard TISCI header
 *
 * \param valid_params Bitfield defining validity of flow delegation parameters.
 *                     The flow delegation fields are not valid, and will not be
 *                     used, if their corresponding valid bit is zero.  Valid
 *                     bit usage:
 *                     0 - Valid bit for
 *                         @ref tisci_msg_rm_udmap_flow_delegate_req::delegated_host
 *                     1 - Valid bit for
 *                         @ref tisci_msg_rm_udmap_flow_delegate_req::clear
 *
 * \param dev_id SoC device ID of DMA in which the common flow exists.
 *
 * \param flow_index DMA common flow being delegated for configuration.
 *
 * \param delegated_host The host delegated configuration access to the flow.
 *                       The host must be a valid host within the SoC.  This
 *                       field is only valid if
 *                       @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_DELEGATE_HOST_VALID
 *                       is set in
 *                       @ref tisci_msg_rm_udmap_flow_delegate_req::valid_params.
 *
 * \param clear Clears the flow delegation when enabled.  Set this parameter
 *              to @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_DELEGATE_CLEAR.  This
 *              field is only valid if
 *              @ref TISCI_MSG_VALUE_RM_UDMAP_FLOW_DELEGATE_CLEAR_VALID is
 *              set in @ref tisci_msg_rm_udmap_flow_delegate_req::valid_params.
 */
struct tisci_msg_rm_udmap_flow_delegate_req {
	struct tisci_header	hdr;
	u32			valid_params;
	u16			dev_id;
	u16			flow_index;
	u8			delegated_host;
	u8			clear;
} __attribute__((__packed__));

/**
 * \brief Response to delegating a flow to another host for configuration.
 *
 * \param hdr
 * Standard TISCI header
 */
struct tisci_msg_rm_udmap_flow_delegate_resp {
	struct tisci_header hdr;
} __attribute__((__packed__));

#endif /* RM_TISCI_UDMAP_H */
