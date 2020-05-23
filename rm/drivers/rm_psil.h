/*
 * PSI-L
 *
 * PSI-L management infrastructure
 *
 * Copyright (C) 2018-2019 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RM_PSIL_H
#define RM_PSIL_H

#include <types/short_types.h>

/**
 * \brief Retrieve the SoC's DRU channel 0 destination thread offset
 *
 * \param nav_id SoC device ID of Navigator instance
 *
 * \param dru_dst_offset Returns the DRU channel 0 destination offset
 *
 * \return SUCCESS if PSI-L DRU ch offset is returned, else -EINVAL
 */
s32 rm_psil_get_dru_dst_offset(u16 nav_id, u16 *dru_dst_offset);

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
