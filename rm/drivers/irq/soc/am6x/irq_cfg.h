/*
 * IRQ SoC configuration
 *
 * Defines the SoC-specific configuration of the IRQ architecture
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef IRQ_CFG_H
#define IRQ_CFG_H

/**
 * Maximum depth, or number of nodes minus one, between the IRQ source and
 * destination subsystems.  The routing algorithm does not push a node for
 * the final destination host processor so only the peripheral and intermediate
 * routing subsystems need to be accounted for in the maximum route depth
 * calculation.
 *
 * For AM65X it's: peripheral --> IR --> IR --> host processor
 */
#define IRQ_MAX_ROUTE_DEPTH   (3u)

/**
 * Extern for IRQ event source devices array
 */
extern const u16 evt_rt_srcs[];

/**
 * Extern for number of elements in IRQ event source devices array
 */
extern const u32 evt_rt_srcs_count;

#endif /* IRQ_CFG_H */
