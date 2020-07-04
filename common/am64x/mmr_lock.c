/*
 * DMSC firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/array_size.h>
#include <lib/ioremap.h>
#include <lib/mmr_lock.h>
#include <lib/trace.h>
#include <osal/osal_hwi.h>

#define MAIN_CTRL_BASE                          (0x43000000UL)
#define MCU_CTRL_BASE                           (0x4500000UL)

#define CTRL_MMR0_PARTITION_SIZE                (0x4000U)

#define CTRLMMR_LOCK_KICK0                      (0x01008U)
#define CTRLMMR_LOCK_KICK0_UNLOCK_VAL           (0x68ef3490U)
#define CTRLMMR_LOCK_KICK0_LOCK_VAL             (0x0U)
#define CTRLMMR_LOCK_KICK0_UNLOCKED_MASK        BIT(0)
#define CTRLMMR_LOCK_KICK0_UNLOCKED_SHIFT       (0U)
#define CTRLMMR_LOCK_KICK1                      (0x0100cU)
#define CTRLMMR_LOCK_KICK1_UNLOCK_VAL           (0xd172bc5aU)
#define CTRLMMR_LOCK_KICK1_LOCK_VAL             (0x0U)

static volatile s32 mmr_lock_count = 0;
static void mmr_writel(u32 v, u32 a)
{
	writel(v, 0x60000000 + a);
}

static void mmr_unlock(u32 base, u32 partition)
{
	/* Translate the base address */
	u32 part_base = base + (partition * CTRL_MMR0_PARTITION_SIZE);

	/*
	 * Unlock the requested partition if locked using two-step sequence.
	 * This register does not read back the value written.
	 */
	mmr_writel(CTRLMMR_LOCK_KICK0_UNLOCK_VAL, part_base + CTRLMMR_LOCK_KICK0);
	mmr_writel(CTRLMMR_LOCK_KICK1_UNLOCK_VAL, part_base + CTRLMMR_LOCK_KICK1);
}

static void mmr_lock(u32 base, u32 partition)
{
	/* Translate the base address */
	u32 part_base = base + (partition * CTRL_MMR0_PARTITION_SIZE);

	/*
	 * Unlock the requested partition if locked using two-step sequence.
	 * This register does not read back the value written.
	 */
	mmr_writel(CTRLMMR_LOCK_KICK0_LOCK_VAL, part_base + CTRLMMR_LOCK_KICK0);
	mmr_writel(CTRLMMR_LOCK_KICK1_LOCK_VAL, part_base + CTRLMMR_LOCK_KICK1);
}

void mmr_unlock_all()
{
	u32 key = osal_hwip_disable();

	if (mmr_lock_count == 0) {
		/* Unlock CLKSEL MMR partitions */
		mmr_unlock(MAIN_CTRL_BASE, 2);
		/* Unlock RST_CTRL MMR partitions*/
		mmr_unlock(MAIN_CTRL_BASE, 6);
		/*
		 * We may not even have access to MCU island(warm reset) to lock the CTRL_BASE..
		 * However, we expect MCU island to self manage.
		 * TBD....
		 */
		mmr_unlock(MCU_CTRL_BASE, 2);
	}
	mmr_lock_count++;
	osal_hwip_restore(key);
}

void mmr_lock_all()
{
	u32 key = osal_hwip_disable();

	mmr_lock_count--;
	if (mmr_lock_count == 0) {
		/* Lock CLKSEL MMR partitions */
		mmr_lock(MAIN_CTRL_BASE, 2);
		/* lock RST_CTRL MMR partitions*/
		mmr_lock(MAIN_CTRL_BASE, 6);
		/*
		 * We may not even have access to MCU island(warm reset) to lock the CTRL_BASE..
		 * However, we expect MCU island to self manage. if we have to control
		 * MCU island is "unsafe".
		 * TBD....
		 */
		mmr_lock(MCU_CTRL_BASE, 2);
	}
	osal_hwip_restore(key);
}
