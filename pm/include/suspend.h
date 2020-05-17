/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef SUSPEND_H
#define SUSPEND_H

s32 suspend(void);
s32 suspend_enter(void);
s32 arch_suspend(void);
s32 arch_resume(void);

#endif
