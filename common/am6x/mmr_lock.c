/*
 * DMSC firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/array_size.h>
#include <lib/ioremap.h>
#include <lib/mmr_lock.h>
#include <osal/osal_hwi.h>

#define MAIN_CTRL_BASE  0x00100000
#define WKUP_CTRL_BASE  0x43000000
#define MCU_CTRL_BASE   0x40f00000

#define CTRL_MMR0_PARTITION_SIZE                        0x4000

#define CTRLMMR_LOCK_KICK0                              0x01008
#define CTRLMMR_LOCK_KICK0_UNLOCK_VAL                   0x68ef3490
#define CTRLMMR_LOCK_KICK0_LOCK_VAL                     0x0
#define CTRLMMR_LOCK_KICK0_UNLOCKED_MASK                BIT(0)
#define CTRLMMR_LOCK_KICK0_UNLOCKED_SHIFT               0
#define CTRLMMR_LOCK_KICK1                              0x0100c
#define CTRLMMR_LOCK_KICK1_UNLOCK_VAL                   0xd172bc5a
#define CTRLMMR_LOCK_KICK1_LOCK_VAL                     0x0

static volatile s32 mmr_lock_count = 0;

static void mmr_unlock(u32 base, u32 partition)
{
	/* Translate the base address */
	u32 part_base = base + partition * CTRL_MMR0_PARTITION_SIZE;

	/* Unlock the requested partition if locked using two-step sequence */
	writel(CTRLMMR_LOCK_KICK0_UNLOCK_VAL, part_base + CTRLMMR_LOCK_KICK0);
	writel(CTRLMMR_LOCK_KICK1_UNLOCK_VAL, part_base + CTRLMMR_LOCK_KICK1);
}

static void mmr_lock(u32 base, u32 partition)
{
	/* Translate the base address */
	u32 part_base = base + partition * CTRL_MMR0_PARTITION_SIZE;

	/* Unlock the requested partition if locked using two-step sequence */
	writel(CTRLMMR_LOCK_KICK0_LOCK_VAL, part_base + CTRLMMR_LOCK_KICK0);
	writel(CTRLMMR_LOCK_KICK1_LOCK_VAL, part_base + CTRLMMR_LOCK_KICK1);
}

void mmr_lock_all()
{
	u32 key = osal_hwip_disable();

	mmr_lock_count--;
	if (mmr_lock_count == 0) {
		/* lock CLKSEL MMR partitions */
		mmr_lock(WKUP_CTRL_BASE, 2);
		mmr_lock(MCU_CTRL_BASE, 2);
		mmr_lock(MAIN_CTRL_BASE, 2);
		/* lock WKUP_MCU_WARM_RST_CTRL MMR partitions*/
		mmr_lock(WKUP_CTRL_BASE, 6);
	}
	osal_hwip_restore(key);
}

void mmr_unlock_all()
{
	u32 key = osal_hwip_disable();

	if (mmr_lock_count == 0) {
		/* Unlock CLKSEL MMR partitions */
		mmr_unlock(WKUP_CTRL_BASE, 2);
		mmr_unlock(MCU_CTRL_BASE, 2);
		mmr_unlock(MAIN_CTRL_BASE, 2);
		/* Unlock WKUP_MCU_WARM_RST_CTRL MMR partitions*/
		mmr_unlock(WKUP_CTRL_BASE, 6);
	}
	mmr_lock_count++;
	osal_hwip_restore(key);
}
