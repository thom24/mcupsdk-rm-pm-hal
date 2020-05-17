/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef ARCH_IRQ_H
#define ARCH_IRQ_H

#include <arch/interrupt.h>
#include <config.h>

#define ARCH_NR_IRQS    240
#define NR_IRQS         ARCH_NR_IRQS

#define local_irq_save(flags)						\
	do {								\
		flags = arch_local_irq_save();				\
	} while (0)

#define local_irq_restore       arch_local_irq_restore

extern const struct irq_drv arch_irq_driver;

#endif
