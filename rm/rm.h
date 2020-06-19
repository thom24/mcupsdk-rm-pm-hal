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

#ifdef CONFIG_RM_IRQ
/**
 * \brief IRQ set message handler
 *
 * \param msg_recv Received TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
s32 rm_irq_set(u32 *msg_recv);

/**
 * \brief IRQ release message handler
 *
 * \param msg_recv Received TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
s32 rm_irq_release(u32 *msg_recv);
#else
static inline s32 rm_irq_set(u32 *msg_recv __attribute__((unused)))
{
	return -EINIT;
}

static inline s32 rm_irq_release(u32 *msg_recv __attribute__((unused)))
{
	return -EINIT;
}
#endif

#ifdef CONFIG_RM_PROXY
/**
 * \brief proxy configure message handler
 *
 * \param msg_recv Received TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
s32 rm_proxy_cfg(u32 *msg_recv);
#else
static inline s32 rm_proxy_cfg(u32 *msg_recv __attribute__((unused)))
{
	return -EINIT;
}
#endif

#ifdef CONFIG_RM_PSIL
/**
 * \brief PSI-L thread pairing message handler
 *
 * \param msg_recv TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
s32 rm_psil_pair(u32 *msg_recv);

/**
 * \brief PSI-L thread unpairing message handler
 *
 * \param msg_recv TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
s32 rm_psil_unpair(u32 *msg_recv);

/**
 * \brief PSI-L thread read message handler
 *
 * \param msg_recv TISCI message
 *
 * \param msg_resp Response TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
s32 rm_psil_read(u32 *msg_recv, u32 *msg_resp);

/**
 * \brief PSI-L thread write message handler
 *
 * \param msg_recv TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
s32 rm_psil_write(u32 *msg_recv);
#else
static inline s32 rm_psil_pair(u32 *msg_recv __attribute__((unused)))
{
	return -EINIT;
}

static inline s32 rm_psil_unpair(u32 *msg_recv __attribute__((unused)))
{
	return -EINIT;
}

static inline s32 rm_psil_read(u32	*msg_recv __attribute__((unused)),
			       u32	*msg_resp __attribute__((unused)))
{
	return -EINIT;
}

static inline s32 rm_psil_write(u32 *msg_recv __attribute__((unused)))
{
	return -EINIT;
}
#endif

#ifdef CONFIG_RM_RA
/**
 * \brief Ring accelerator configure message handler
 *
 * \param msg_recv TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
s32 rm_ra_cfg(u32 *msg_recv);

/**
 * \brief Ring accelerator monitor configure message handler
 *
 * \param msg_recv TISCI message
 *
 * \return SUCCESS if message processed successfully, else error
 */
s32 rm_ra_mon_cfg(u32 *msg_recv);
#else
static inline s32 rm_ra_cfg(u32 *msg_recv __attribute__((unused)))
{
	return -EINIT;
}
static inline s32 rm_ra_mon_cfg(u32 *msg_recv __attribute__((unused)))
{
	return -EINIT;
}
#endif

#endif /* RM_H */
