/*
 * UDMAP SoC configuration
 *
 * Defines the SoC-specific configuration of the UDMAP architecture
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef UDMAP_CFG_H
#define UDMAP_CFG_H

/**
 * AM6 Main Navigator Subsystem total number of UDMAP transmit channels
 */
#define AM6_MAIN_NAVSS_UDMAP_TX_CHAN_MAX_INDEX    (152u)

/**
 * AM6 Main Navigator Subsystem total number of UDMAP receive channels
 */
#define AM6_MAIN_NAVSS_UDMAP_RX_CHAN_MAX_INDEX    (150u)

/**
 * AM6 Main Navigator Subsystem total number of UDMAP receive flows
 */
#define AM6_MAIN_NAVSS_UDMAP_RX_FLOW_MAX_INDEX    (300u)

/**
 * AM6 MCU Navigator Subsystem total number of UDMAP transmit channels
 */
#define AM6_MCU_NAVSS_UDMAP_TX_CHAN_MAX_INDEX     (48u)

/**
 * AM6 MCU Navigator Subsystem total number of UDMAP receive channels
 */
#define AM6_MCU_NAVSS_UDMAP_RX_CHAN_MAX_INDEX     (48u)

/**
 * AM6 MCU Navigator Subsystem total number of UDMAP receive flows
 */
#define AM6_MCU_NAVSS_UDMAP_RX_FLOW_MAX_INDEX     (96u)

/**
 * UDMAP transmit channel OES index offset
 */
#define UDMAP_TCHAN_OES_EVT_INDEX_OFFSET (0x0U)
/**
 * UDMAP transmit channel error OES index offset
 */
#define UDMAP_TCHAN_EOES_EVT_INDEX_OFFSET (0x100U)
/**
 * UDMAP receive channel OES index offset
 */
#define UDMAP_RCHAN_OES_EVT_INDEX_OFFSET (0x200U)
/**
 * UDMAP receive channel error OES index offset
 */
#define UDMAP_RCHAN_EOES_EVT_INDEX_OFFSET (0x300U)
/**
 * UDMAP invalid flow event index.  Must be greater than the max of all SoC
 * UDMAPs channel OES indexes to avoid event indexing conflicts.
 */
#define UDMAP_GCFG_INVALID_FLOW_EVT_INDEX (0x400U)

#endif /* UDMAP_CFG_H */
