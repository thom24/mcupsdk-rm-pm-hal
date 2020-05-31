/*
 * Interrupt Management
 *
 * Data version: 000000_000000
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef IRQ_CFG_H
#define IRQ_CFG_H

/**
 * Maximum depth, or number of nodes minus one, between the IRQ source and
 * destination subsystems.  The routing algorithm does not push a node for the
 * final destination host processor so only the peripheral and intermediate
 * routing subsystems need to be accounted for in the maximum route depth
 * calculation.
 */
#define IRQ_MAX_ROUTE_DEPTH (3U)

/**
 * Extern for IRQ event source devices array
 */
extern const u16 evt_rt_srcs[];

/**
 * Extern for number of IRQ event source devices
 */
extern const u32 evt_rt_srcs_count;


#endif /* IRQ_CFG_H */
