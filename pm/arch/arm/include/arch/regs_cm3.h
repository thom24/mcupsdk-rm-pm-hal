/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef ARCH_REGS_CM3_H
#define ARCH_REGS_CM3_H

#define SYS_CONTROL_BASE        0xE000E000

#define SYS_ICTR                (SYS_CONTROL_BASE + 0x004)
#define SYS_ACTLR               (SYS_CONTROL_BASE + 0x008)
#define SYS_STCSR               (SYS_CONTROL_BASE + 0x010)
#define SYS_STRVR               (SYS_CONTROL_BASE + 0x014)
#define SYS_STCVR               (SYS_CONTROL_BASE + 0x018)
#define SYS_STCR                (SYS_CONTROL_BASE + 0x01c)
#define NVIC_ISER(N)            (SYS_CONTROL_BASE + 0x100 + (N) * 4)
#define NVIC_ICER(N)            (SYS_CONTROL_BASE + 0x180 + (N) * 4)
#define NVIC_ISPR(N)            (SYS_CONTROL_BASE + 0x200 + (N) * 4)
#define NVIC_ICPR(N)            (SYS_CONTROL_BASE + 0x280 + (N) * 4)
#define NVIC_IABR(N)            (SYS_CONTROL_BASE + 0x300 + (N) * 4)
#define NVIC_IPR(N)             (SYS_CONTROL_BASE + 0x400 + (N) * 4)
#define SYS_CPUID               (SYS_CONTROL_BASE + 0xd00)
#define SYS_ICSR                (SYS_CONTROL_BASE + 0xd04)
#define SYS_VTOR                (SYS_CONTROL_BASE + 0xd08)
#define SYS_AIRCR               (SYS_CONTROL_BASE + 0xd0c)

#define SYS_SCR                 (SYS_CONTROL_BASE + 0xd10)
#define SYS_SCR_SD_OFFSET       0x2
#define SYS_SCR_SOE_OFFSET      0x1

#define SYS_CCR                 (SYS_CONTROL_BASE + 0xd14)
#define SYS_SHPR1               (SYS_CONTROL_BASE + 0xd18)
#define SYS_SHPR2               (SYS_CONTROL_BASE + 0xd1c)
#define SYS_SHPR3               (SYS_CONTROL_BASE + 0xd20)
#define SYS_SHCSR               (SYS_CONTROL_BASE + 0xd24)
#define SYS_CFSR                (SYS_CONTROL_BASE + 0xd28)
#define SYS_HFSR                (SYS_CONTROL_BASE + 0xd2c)
#define SYS_DFSR                (SYS_CONTROL_BASE + 0xd30)
#define SYS_MMFAR               (SYS_CONTROL_BASE + 0xd34)
#define SYS_BFAR                (SYS_CONTROL_BASE + 0xd38)
#define SYS_AFSR                (SYS_CONTROL_BASE + 0xd3c)
#define SYS_PFR0                (SYS_CONTROL_BASE + 0xd40)
#define SYS_PFR1                (SYS_CONTROL_BASE + 0xd44)
#define SYS_DFR0                (SYS_CONTROL_BASE + 0xd48)
#define SYS_AFR0                (SYS_CONTROL_BASE + 0xd4c)
#define SYS_MMFR0               (SYS_CONTROL_BASE + 0xd50)
#define SYS_MMFR1               (SYS_CONTROL_BASE + 0xd54)
#define SYS_MMFR2               (SYS_CONTROL_BASE + 0xd58)
#define SYS_MMFR3               (SYS_CONTROL_BASE + 0xd5c)
#define SYS_ISAR0               (SYS_CONTROL_BASE + 0xd60)
#define SYS_ISAR1               (SYS_CONTROL_BASE + 0xd64)
#define SYS_ISAR2               (SYS_CONTROL_BASE + 0xd68)
#define SYS_ISAR3               (SYS_CONTROL_BASE + 0xd6c)
#define SYS_ISAR4               (SYS_CONTROL_BASE + 0xd70)
#define SYS_CPACR               (SYS_CONTROL_BASE + 0xd88)
#define SYS_STIR                (SYS_CONTROL_BASE + 0xf00)

void scr_enable_sleepdeep(void);
void scr_enable_sleeponexit(void);

#endif
