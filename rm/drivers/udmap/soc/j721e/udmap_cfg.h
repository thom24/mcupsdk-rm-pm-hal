/*
 * UDMAP
 *
 * UDMAP SoC-specific configuration definitions
 *
 * Data version: 190425_000000
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef UDMAP_CFG_H
#define UDMAP_CFG_H

/**
 * NAVSS0_UDMAP_0 total number of UDMAP transmit channels
 */
#define UDMAP_NAVSS0_UDMAP_0_TX_CHAN_MAX_INDEX (300U)
/**
 * NAVSS0_UDMAP_0 total number of UDMAP receive channels
 */
#define UDMAP_NAVSS0_UDMAP_0_RX_CHAN_MAX_INDEX (140U)
/**
 * NAVSS0_UDMAP_0 total number of UDMAP receive flows
 */
#define UDMAP_NAVSS0_UDMAP_0_RX_FLOW_MAX_INDEX (300U)
/**
 * MCU_NAVSS0_UDMAP_0 total number of UDMAP transmit channels
 */
#define UDMAP_MCU_NAVSS0_UDMAP_0_TX_CHAN_MAX_INDEX (48U)
/**
 * MCU_NAVSS0_UDMAP_0 total number of UDMAP receive channels
 */
#define UDMAP_MCU_NAVSS0_UDMAP_0_RX_CHAN_MAX_INDEX (48U)
/**
 * MCU_NAVSS0_UDMAP_0 total number of UDMAP receive flows
 */
#define UDMAP_MCU_NAVSS0_UDMAP_0_RX_FLOW_MAX_INDEX (96U)
/**
 * UDMAP transmit channel OES index offset
 */
#define UDMAP_TCHAN_OES_EVT_INDEX_OFFSET (0x0U)
/**
 * UDMAP transmit channel error OES index offset
 */
#define UDMAP_TCHAN_EOES_EVT_INDEX_OFFSET (0x200U)
/**
 * UDMAP receive channel OES index offset
 */
#define UDMAP_RCHAN_OES_EVT_INDEX_OFFSET (0x400U)
/**
 * UDMAP receive channel error OES index offset
 */
#define UDMAP_RCHAN_EOES_EVT_INDEX_OFFSET (0x500U)
/**
 * UDMAP invalid flow event index.  Must be greater than the max of all SoC
 * UDMAPs channel OES indexes to avoid event indexing conflicts.
 */
#define UDMAP_GCFG_INVALID_FLOW_EVT_INDEX (0x600U)

#endif /* UDMAP_CFG_H */
