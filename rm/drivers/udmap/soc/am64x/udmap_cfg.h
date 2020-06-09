/*
 * UDMAP
 *
 * UDMAP SoC-specific configuration definitions
 *
 * Data version: 200505_104840
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef UDMAP_CFG_H
#define UDMAP_CFG_H

/**
 * DMASS0_BCDMA_0 total number of UDMAP transmit channels
 */
#define UDMAP_DMASS0_BCDMA_0_TX_CHAN_MAX_INDEX (20U)
/**
 * DMASS0_BCDMA_0 total number of UDMAP receive channels
 */
#define UDMAP_DMASS0_BCDMA_0_RX_CHAN_MAX_INDEX (20U)
/**
 * DMASS0_BCDMA_0 total number of block copy channels
 */
#define UDMAP_DMASS0_BCDMA_0_BC_CHAN_MAX_INDEX (28U)
/**
 * DMASS0_BCDMA_0 block copy channel offset
 */
#define UDMAP_DMASS0_BCDMA_0_BC_CHAN_OFFSET (32U)
/**
 * DMASS0_PKTDMA_0 total number of UDMAP transmit channels
 */
#define UDMAP_DMASS0_PKTDMA_0_TX_CHAN_MAX_INDEX (42U)
/**
 * DMASS0_PKTDMA_0 total number of UDMAP receive channels
 */
#define UDMAP_DMASS0_PKTDMA_0_RX_CHAN_MAX_INDEX (29U)
/**
 * DMASS0_PKTDMA_0 total number of UDMAP receive flows
 */
#define UDMAP_DMASS0_PKTDMA_0_RX_FLOW_MAX_INDEX (192U)

#endif /* UDMAP_CFG_H */
