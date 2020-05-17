/*
 * DMSC firmware
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef RAT_H
#define RAT_H

#include <config.h>
#include <types/short_types.h>
#include <types/errno.h>

void rat_set_mapping(s32 window, u32 base, u64 address, u32 order);
void rat_disable_mapping(s32 window);

/**
 * \brief Allow limited mapping scheme using a spare memory window we can use
 *
 * Objective of this API is a limited usage scenario where there is absolutely
 * no chance of contention. There are no lock protection mechanisms provided.
 *
 * \param addr - SoC physical address we want to map back in. MUST be 512MB
 *	aligned. must check against RAT_TMP_REGION_INVAL_ADDR_MASK
 *	The provided address also acts as a "cookie" or identifier when freeing
 *	the map.
 * \param mapped_addr - if all is valid, returns a mapped address back
 *
 * \return SUCCESS if all went fine, else returns corresponding error value.
 */
s32 rat_map_tmp_region(u64 addr, u32 *mapped_addr);

/**
 * \brief Free and disable a mapping done by rat_map_tmp_region
 *
 * Objective of this API is a limited usage scenario where there is absolutely
 * no chance of contention. There are no lock protection mechanisms provided.
 *
 * \param addr provide the exact address parameter provided to rat_map_tmp_region
 *
 * \return SUCCESS if all went fine, else returns corresponding error value.
 */
s32 rat_unmap_tmp_region(u64 addr);

#define RAT_TMP_REGION_INVAL_ADDR_MASK  (0x1FFFFFFFU)

#ifdef CONFIG_RAT
extern s32 rat_init(void);
#else
static inline s32 rat_init(void)
{
	return SUCCESS;
}
#endif

#endif
