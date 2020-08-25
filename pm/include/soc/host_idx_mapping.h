/*
 * System Firmware Source File
 *
 * Host ID/index mapping for J721E device
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef SOC_HOST_IDX_MAPPING_H
#define SOC_HOST_IDX_MAPPING_H

#include <types/short_types.h>

#define HOST_IDX_NONE 255U

extern const u8 soc_host_indexes[];
extern const u8 soc_host_indexes_sz;

static inline u8 host_idx_lookup(u8 host_id)
{
	return (host_id < soc_host_indexes_sz) ? soc_host_indexes[host_id] : HOST_IDX_NONE;
}

#endif
