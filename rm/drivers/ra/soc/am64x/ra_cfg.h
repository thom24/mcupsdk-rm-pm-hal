/*
 * Ring Accelerator
 *
 * Ring accelerator SoC-specific configuration definitions
 *
 * Data version: 200505_104840
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef RA_CFG_H
#define RA_CFG_H

/**
 * DMASS0_RINGACC_0 total number of rings
 */
#define RA_DMASS0_RINGACC_0_MAX_INDEX (12U)
/**
 * Ring accelerator ring event index.
 */
#define RA_DMASS0_RINGACC_0_RING_OES_EVT_INDEX_OFFSET (0x14U)
/**
 * Ring accelerator global control error event index.  Must be greater than
 * the max of all SoC RAs max ring index to avoid event indexing conflicts.
 */
#define RA_GCFG_ERROR_EVT_INDEX (0x20U)

#endif /* RA_CFG_H */
