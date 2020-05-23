/*
 * Proxy
 *
 * proxy management infrastructure
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_PROXY_H
#define RM_PROXY_H

#include <types/sbool.h>
#include <types/short_types.h>

/**
 * \brief Confirms managed resource assignment types for proxy driver
 *
 * Returns whether or not the provided board cfg resource assignment unique
 * type is managed by proxy driver.
 *
 * \param type Resource assignment unique type
 *
 * \return TRUE if resource type is managed by proxy driver, else FALSE
 */
sbool rm_proxy_is_managed_resasg_utype(u16 utype);

/**
 * \brief Initializes the proxy driver
 *
 * Initializes the proxy driver data structures
 *
 * \return
 *      SUCCESS - Initialization completed successfully
 *      -E... - Error occurred during initialization
 */
s32 rm_proxy_init(void);

/**
 * \brief Deinitializes the proxy driver for a device group
 *
 * Set the proxy driver's initialized flag to false
 *
 * \return
 *      SUCCESS - Deinitialized the chosen device group successfully
 *      -E... - Failed to deinitialize the chosen device group
 */
s32 rm_proxy_deinit(devgrp_t devgrp);

#endif /* RM_PROXY_H */
