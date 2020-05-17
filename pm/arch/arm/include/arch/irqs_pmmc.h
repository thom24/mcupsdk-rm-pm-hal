/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef ARCH_IRQS_PMMC_H
#define ARCH_IRQS_PMMC_H

#define IRQ_PMMC_IO_SWAKEUP     0       /* Wakeup from IO Power Management */
#define IRQ_PMMC_TIMER1_T12     1       /* Interrupt from timer1 */
#define IRQ_PMMC_TIMER1_T34     2
#define IRQ_PMMC_TIMER2_T12     3       /* Interrupt from timer2 */
#define IRQ_PMMC_TIMER2_T34     4
#define IRQ_PMMC_FAULT_DET      5       /* Fault Detected Interrupt */
#define IRQ_PMMC_RTI_WWDT       6       /* RTI Watchdog interrupt */
#define IRQ_PMMC_RTI_REQ0       7       /* RTI Comparator interrupt 0 */
#define IRQ_PMMC_RTI_REQ1       8
#define IRQ_PMMC_RTI_REQ2       9
#define IRQ_PMMC_RTI_REQ3       10
#define IRQ_PMMC_EXT(N)         (24 + (N))      /* External interrupts */

#endif
