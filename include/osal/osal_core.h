/*
 * System Firmware OSAL Core APIs
 *
 * OSAL Core Public APIs used for intialization and firmware control
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef OSAL_CORE_H
#define OSAL_CORE_H

#include <types/short_types.h>
#include <types/sbool.h>

#define SUBSYSTEM_ENABLED       ((u32) 0xAu)

#define SUBSYSTEM_BP_MASK       0x0000000Fu
#define SUBSYSTEM_BP_SHIFT      0u
#define SUBSYSTEM_BP            (SUBSYSTEM_ENABLED << SUBSYSTEM_BP_SHIFT)

#define SUBSYSTEM_SEC_MASK      0x000000F0u
#define SUBSYSTEM_SEC_SHIFT     4u
#define SUBSYSTEM_SEC           (SUBSYSTEM_ENABLED << SUBSYSTEM_SEC_SHIFT)

#define SUBSYSTEM_RM_MASK       0x00000F00u
#define SUBSYSTEM_RM_SHIFT      8u
#define SUBSYSTEM_RM            (SUBSYSTEM_ENABLED << SUBSYSTEM_RM_SHIFT)

#define SUBSYSTEM_PM_MASK       0x0000F000u
#define SUBSYSTEM_PM_SHIFT      12u
#define SUBSYSTEM_PM            (SUBSYSTEM_ENABLED << SUBSYSTEM_PM_SHIFT)

void osal_subsystem_set_init(u32 subsystem);

sbool osal_subsystem_check_init(u32 subsystem);
/**
 * \brief To be invoked after boardcfg is received to allow OSAL to
 *        reconfigure itself as needed when boardcfg data is available.
 *
 * \return Error code on failure, SUCCESS otherwise.
 */
s32 osal_core_post_config_init(void);

s32 osal_core_verify_host_id(u8 host_id);

/**
 * \brief Raw buffer output function for use with low level rtos printing.
 *
 * \param buf Pointer to collection of character to be output.
 * \param len Number of characters to be output.
 */
void osal_trace_print_output(u8 *buf, u32 len);

#endif /* OSAL_CORE_H */
