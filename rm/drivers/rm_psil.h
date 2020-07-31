/*
 * PSI-L
 *
 * PSI-L management infrastructure
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_PSIL_H
#define RM_PSIL_H

#include <types/short_types.h>

/**
 * \brief Initializes the PSIL driver
 *
 * Initializes the PSIL driver data structures
 *
 * \return
 *      SUCCESS - Initialization completed successfully
 *      -E... - Error occurred during initialization
 */
s32 rm_psil_init(void);

#endif /* RM_PSIL_H */
