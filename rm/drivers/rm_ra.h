/*
 * Ring Accelerator
 *
 * Ring Accelerator management infrastructure
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_RA_H
#define RM_RA_H

#include <types/sbool.h>
#include <types/short_types.h>

/**
 * \brief Validate ring index
 *
 * Verifies the ring index is valid for the Navigator RA ID and for the
 * resource assignment data
 *
 * \param nav_id RA device ID
 *
 * \param host Host ID
 *
 * \param index Ring index
 *
 * \return SUCCESS if ring index is valid, else -EINVAL
 */
s32 rm_ra_validate_ring_index(u16 nav_id, u8 host, u16 index);

/**
 * \brief Confirms managed resource assignment types for RA driver
 *
 * Returns whether or not the provided board cfg resource assignment unique
 * type is managed by RA driver.
 *
 * \param type Resource assignment unique type
 *
 * \return TRUE if resource type is managed by RA driver, else FALSE
 */
sbool rm_ra_is_managed_resasg_utype(u16 utype);

/**
 * \brief Initializes the RA driver
 *
 * Initializes the RA driver data structures
 *
 * \return
 *      SUCCESS - Initialization completed successfully
 *      -E... - Error occurred during initialization
 */
s32 rm_ra_init(void);

/**
 * \brief Deinitializes the RA driver for a device group
 *
 * Set the RA driver's initialized flag to false
 *
 * \return
 *      SUCCESS - Deinitialized the chosen device group successfully
 *      -E... - Failed to deinitialize the chosen device group
 */
s32 rm_ra_deinit(devgrp_t devgrp);

#endif /* RM_RA_H */
