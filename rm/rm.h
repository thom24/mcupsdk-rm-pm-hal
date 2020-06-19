/*
 * RM
 *
 * Resource Manager APIs
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

#ifdef CONFIG_RM
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
s32 rm_init(void);

/**
 * \brief RM de-init function
 *
 * De-initializes RM data structures in a device group
 *
 * \return
 * Status of de-initialization
 *      SUCCESS - De-initialization completed successfully
 */
s32 rm_deinit(devgrp_t devgrp);

/**
 * \brief Resource range retrieval
 *
 * \param msg_recv Received TISCI message
 *
 * \param msg_resp Response TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
s32 rm_core_get_resource_range(u32 *msg_recv, u32 *msg_resp);
#else
static inline s32 rm_init(void)
{
	return SUCCESS;
}

static inline s32 rm_deinit(devgrp_t devgrp __attribute__((unused)))
{
	return SUCCESS;
}

static inline s32 rm_core_get_resource_range(u32	*msg_recv __attribute__((unused)),
					     u32	*msg_resp __attribute__((unused)))
{
	return -EINIT;
}
#endif

#endif /* RM_H */
