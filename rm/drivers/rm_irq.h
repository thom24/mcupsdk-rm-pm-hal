/*
 * DMSC RM IRQ
 *
 * Resource Manager IRQ infrastructure APIs
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_IRQ_H
#define RM_IRQ_H

#include <types/short_types.h>
#include <types/map.h>
#include <soc_devgrps.h>

typedef s32 (*rm_irq_oes_get_func_t)(u8 host, u16 id, u16 irq, u16 *evt);
typedef s32 (*rm_irq_oes_set_func_t)(u8 host, u16 id, u16 irq, u16 evt);

/**
 * \brief Contains handlers needed to get/set device OES registers.
 *
 * \param oes_get Pointer to the OES register get function.  The function is
 *                passed the host making the request, the SoC Device ID, and the
 *                IRQ output from the device.  It returns the global event
 *                programmed into the device's output IRQ OES register.
 *
 * \param oes_set Pointer to the OES register set function.  The function is
 *                passed the host making the request, the SoC Device ID, the
 *                IRQ output from the device, and global event value to program
 *                into the device's output IRQ OES register.
 *
 * \param node Struct used in map implementation
 */
struct rm_irq_oes_src {
	rm_irq_oes_get_func_t	oes_get;
	rm_irq_oes_set_func_t	oes_set;
	struct map_node		node;
};

/**
 * \brief Confirms managed resource assignment types for IRQ management
 *
 * Returns whether or not the provided board cfg resource assignment unique
 * type is managed by drivers associated with IRQ management (IRQ driver,
 * IA driver, etc.).
 *
 * \param type Resource assignment unique type
 *
 * \return TRUE if resource type is managed by IRQ management, else FALSE
 */
sbool rm_irq_is_managed_resasg_utype(u16 utype);

/**
 * \brief Register a rm_irq_oes_src to handle OES register get/set for the SoC
 *        device mapped to id
 *
 * This function stores the rm_irq_oes_src in a map that is keyed on SoC device
 * id.
 *
 * \param id SoC device ID to be handled by the OES register handler that is
 *           provided.
 *
 * \param src Pointer to a static struct containing configuration for this
 *            SoC device.
 *
 * \return SUCCESS or error code otherwise.
 */
s32 rm_irq_oes_src_register(u16 id, struct rm_irq_oes_src *src);

/**
 * \brief RM IRQ init function
 *
 * Registers IRQ message handlers with the TISCI core infrastructure
 *
 * \return
 * Status of initialization
 *      SUCCESS - Initialization completed successfully
 *      -E... - Initialization completed unsuccessfully.
 */
s32 rm_irq_init(void);

/**
 * \brief RM IRQ deinit function
 *
 * Deinitializes IA and IR drivers in a device group
 *
 * \return
 * Status of initialization
 *      SUCCESS - Deinitialization completed successfully
 *      -E... - Deinitialization completed unsuccessfully.
 */
s32 rm_irq_deinit(devgrp_t devgrp);

#endif /* RM_IRQ_H */
