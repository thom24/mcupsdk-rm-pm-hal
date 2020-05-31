/*
 * DMSC RM
 *
 * Resource Manager core infrastructure APIs
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_H
#define RM_H

#include <config.h>
#include <types/short_types.h>
#include <types/address_types.h>
#include <types/errno.h>
#include <boardcfg/boardcfg_rm_data.h>
#include <soc_devgrps.h>

/**
 * \brief RM init function
 *
 * Initializes RM data structures and calls individual resource subsystem
 * initialization routines.
 *
 * \return
 * Status of initialization
 *      SUCCESS - Initialization completed successfully
 */
#ifdef CONFIG_RM
s32 rm_init(void);

/**
 * \brief RM deinit function
 *
 * Deinitializes RM data structures in a device group
 *
 * \return
 * Status of deinitialization
 *      SUCCESS - Deinitialization completed successfully
 */
s32 rm_deinit(devgrp_t devgrp);
#else
static inline s32 rm_init(void)
{
	return SUCCESS;
}

static inline s32 rm_deinit(devgrp_t devgrp __attribute__((unused)))
{
	return SUCCESS;
}
#endif

#endif /* RM_H */
