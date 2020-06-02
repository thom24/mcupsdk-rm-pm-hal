/*
 * Proxy
 *
 * Proxy SoC-specific configuration definitions
 *
 * Data version: 200529_213657
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef PROXY_CFG_H
#define PROXY_CFG_H

/**
 * NAVSS0_PROXY_0 total number of proxies
 */
#define PROXY_NAVSS0_PROXY_0_PROXY_MAX_INDEX (64U)
/**
 * MCU_NAVSS0_PROXY0 total number of proxies
 */
#define PROXY_MCU_NAVSS0_PROXY0_PROXY_MAX_INDEX (64U)
/**
 * Number of unique Proxy instances
 */
#define PROXY_INST_COUNT (2U)
/**
 * Extern for proxy subsystem instance array
 */
extern struct proxy_instance proxy_inst[PROXY_INST_COUNT];


#endif /* PROXY_CFG_H */
