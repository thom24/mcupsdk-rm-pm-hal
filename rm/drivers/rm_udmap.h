/*
 * UDMAP
 *
 * UDMAP management infrastructure
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_UDMAP_H
#define RM_UDMAP_H

#include <types/sbool.h>
#include <types/short_types.h>

/**
 * Reset value of UDMAP channel's THRD_ID register
 */
#define RM_UDMAP_THRD_ID_RESETVAL    (0x0000u)

/**
 * \brief Confirms managed resource assignment types for UDMAP driver
 *
 * Returns whether or not the provided board cfg resource assignment unique
 * type is managed by UDMAP driver.
 *
 * \param type Resource assignment unique type
 *
 * \return TRUE if resource type is managed by UDMAP driver, else FALSE
 */
sbool rm_udmap_is_managed_resasg_utype(u16 utype);

/**
 * \brief Initializes the UDMAP driver
 *
 * Initializes the UDMAP driver data structures
 *
 * \return
 *      SUCCESS - Initialization completed successfully
 *      -E... - Error occurred during initialization
 */
s32 rm_udmap_init(void);

/**
 * \brief Deinitializes the UDMAP driver for a device group
 *
 * Set the UDMAP driver's initialized flag to false
 *
 * \return
 *      SUCCESS - Deinitialized the chosen device group successfully
 *      -E... - Failed to deinitialize the chosen device group
 */
s32 rm_udmap_deinit(devgrp_t devgrp);

/**
 * \brief Programs a UDMAP channel's THRD_ID register
 *
 * Programs a UDMAP transmit or receive channel's TCHAN_THRD_ID or
 * RCHAN_THRD_ID register, respectively.  The channel does not have to be
 * allocated for the THRD_ID register to be programmed.  This prevents
 * ordering issues when allocating/freeing channels and pairing/unpairing
 * PSI-L threads.
 *
 * \param id SoC device ID of in which the DMA channel is located
 *
 * \param index UDMAP channel index.
 *
 * \param tx_ch Transmit channel if STRUE, Receive channel if SFALSE
 *
 * \param thread_id PSI-L thread ID to program into the channel's THRD_ID
 *                  register
 *
 * \return SUCCESS if THRD_ID register programmed successfully, else error
 */
s32 rm_udmap_set_thrd_id(u16 id, u16 index, sbool tx_ch, u32 thread_id);

#endif /* RM_UDMAP_H */
