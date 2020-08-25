/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <config.h>
#include <lib/ioremap.h>
#include <drivers/rat.h>
#include <types/short_types.h>

u32 ioremap_internal(u32 a)
{
	u32 addr = a;
	u64 lowAddr, highAddr;
	s32 ret;

	/*
	 * The region from 0x0000_0000 to 0x5fff_ffff is remapped to the
	 * main SoC address space via IO windows. Fortunately, there is no
	 * overlap with the PMMC register space so we do not remap those
	 * addresses
	 *
	 * NOTE: we will misuse pm/soc/am6/dmsc.c configuration for now:
	 *
	 * ~~~
	 * Physical address | mapped address | Size
	 * ----------------------------------------
	 * 0x00000000ULL    | 0x60000000UL   | 512MB
	 * 0x20000000ULL    | 0x80000000UL   | 512MB
	 * 0x40000000ULL    | 0xa0000000UL   | 512MB
	 * ~~~
	 *
	 * *NOTE*: This wont work for firewall setup and separated ops.
	 */
	if (((a >= 0x100000U) && (a < 0x44000000U)) ||
	    ((a >= 0x46000000U) && (a < 0x60000000U))) {
		addr += CONFIG_ADDR_REMAP_OFFSET;
	}
	ret = rat_get_free_map_addr_range_user(&lowAddr, &highAddr);
	if (ret == SUCCESS) {
		if ((a >= soc_phys_low_u32(lowAddr)) && (a < soc_phys_low_u32(highAddr))) {
			addr += CONFIG_ADDR_REMAP_OFFSET;
		}
	}
	return addr;
}
