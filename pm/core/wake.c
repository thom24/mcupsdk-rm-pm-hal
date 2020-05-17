/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <wake.h>
#include <types/short_types.h>
#include <types/array_size.h>
#include <lib/ioremap.h>
#include <lib/io.h>
#include <lib/trace.h>
#include <remote.h>
#include <types/errno.h>
#include <lib/bitops.h>
#include <sleep.h>

#include <tisci/pm/tisci_pm_core.h>

/*
 * Wake interrupts are not for waking the PMMC, they are for removing the ARM
 * from disabled state. Its likely that each master will need its own set of
 * wake interrupts.
 */

/* FIXME: Wake sources will likely need to be tracked per device */

s32 wake_finish(void)
{
	return -ENODEV;
}

void wake_check(void)
{
}

void wake_notify_mode(const struct sleep_mode *mode __attribute__((unused)))
{
}

const struct sleep_mode *wake_deepest_mode(void)
{
	return NULL;
}

void wake_arm(s32 host __attribute__((unused)))
{
}

s32 wake_sources_assign(const struct resource_irq *irq __attribute__((unused)), size_t n __attribute__((unused)))
{
	return -ENODEV;
}
