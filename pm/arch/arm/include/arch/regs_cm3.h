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

#define SYS_CONTROL_BASE        0xE000E000U

#define SYS_ICTR                (SYS_CONTROL_BASE + 0x004U)
#define SYS_ACTLR               (SYS_CONTROL_BASE + 0x008U)
#define SYS_STCSR               (SYS_CONTROL_BASE + 0x010U)
#define SYS_STRVR               (SYS_CONTROL_BASE + 0x014U)
#define SYS_STCVR               (SYS_CONTROL_BASE + 0x018U)
#define SYS_STCR                (SYS_CONTROL_BASE + 0x01cU)
#define NVIC_ISER(N)            (SYS_CONTROL_BASE + 0x100U + ((unsigned) (N)) * 4U)
#define NVIC_ICER(N)            (SYS_CONTROL_BASE + 0x180U + ((unsigned) (N)) * 4U)
#define NVIC_ISPR(N)            (SYS_CONTROL_BASE + 0x200U + ((unsigned) (N)) * 4U)
#define NVIC_ICPR(N)            (SYS_CONTROL_BASE + 0x280U + ((unsigned) (N)) * 4U)
#define NVIC_IABR(N)            (SYS_CONTROL_BASE + 0x300U + ((unsigned) (N)) * 4U)
#define NVIC_IPR(N)             (SYS_CONTROL_BASE + 0x400U + ((unsigned) (N)) * 4U)
#define SYS_CPUID               (SYS_CONTROL_BASE + 0xd00U)
#define SYS_ICSR                (SYS_CONTROL_BASE + 0xd04U)
#define SYS_VTOR                (SYS_CONTROL_BASE + 0xd08U)
#define SYS_AIRCR               (SYS_CONTROL_BASE + 0xd0cU)

#define SYS_SCR                 (SYS_CONTROL_BASE + 0xd10U)
#define SYS_SCR_SD_OFFSET       0x2
#define SYS_SCR_SOE_OFFSET      0x1

#define SYS_CCR                 (SYS_CONTROL_BASE + 0xd14U)
#define SYS_SHPR1               (SYS_CONTROL_BASE + 0xd18U)
#define SYS_SHPR2               (SYS_CONTROL_BASE + 0xd1cU)
#define SYS_SHPR3               (SYS_CONTROL_BASE + 0xd20U)
#define SYS_SHCSR               (SYS_CONTROL_BASE + 0xd24U)
#define SYS_CFSR                (SYS_CONTROL_BASE + 0xd28U)
#define SYS_HFSR                (SYS_CONTROL_BASE + 0xd2cU)
#define SYS_DFSR                (SYS_CONTROL_BASE + 0xd30U)
#define SYS_MMFAR               (SYS_CONTROL_BASE + 0xd34U)
#define SYS_BFAR                (SYS_CONTROL_BASE + 0xd38U)
#define SYS_AFSR                (SYS_CONTROL_BASE + 0xd3cU)
#define SYS_PFR0                (SYS_CONTROL_BASE + 0xd40U)
#define SYS_PFR1                (SYS_CONTROL_BASE + 0xd44U)
#define SYS_DFR0                (SYS_CONTROL_BASE + 0xd48U)
#define SYS_AFR0                (SYS_CONTROL_BASE + 0xd4cU)
#define SYS_MMFR0               (SYS_CONTROL_BASE + 0xd50U)
#define SYS_MMFR1               (SYS_CONTROL_BASE + 0xd54U)
#define SYS_MMFR2               (SYS_CONTROL_BASE + 0xd58U)
#define SYS_MMFR3               (SYS_CONTROL_BASE + 0xd5cU)
#define SYS_ISAR0               (SYS_CONTROL_BASE + 0xd60U)
#define SYS_ISAR1               (SYS_CONTROL_BASE + 0xd64U)
#define SYS_ISAR2               (SYS_CONTROL_BASE + 0xd68U)
#define SYS_ISAR3               (SYS_CONTROL_BASE + 0xd6cU)
#define SYS_ISAR4               (SYS_CONTROL_BASE + 0xd70U)
#define SYS_CPACR               (SYS_CONTROL_BASE + 0xd88U)
#define SYS_STIR                (SYS_CONTROL_BASE + 0xf00U)

void scr_enable_sleepdeep(void);
void scr_enable_sleeponexit(void);

#endif
