/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef ARCH_BARRIER_H
#define ARCH_BARRIER_H

#include <arch/irq.h>

#define dsb()           asm (" dsb")
#define isb()           asm (" isb")
#define wfi()           asm (" wfi")
#define wfe()           asm (" wfe")
#define sev()           asm (" sev")

static inline void cpu_idle(void)
{
	wfi();
	unmask_interrupts();
}

#define barrier()       asm (" ")

#endif
