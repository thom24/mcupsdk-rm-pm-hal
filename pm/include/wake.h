/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef WAKE_H
#define WAKE_H

#include <types.h>
#include <types/sbool.h>
#include <stddef.h>
#include <config.h>
#include <types/short_types.h>

struct sleep_mode;
struct resource_irq;

s32 wake_finish(void);
void wake_check(void);
void wake_notify_mode(const struct sleep_mode *mode);
const struct sleep_mode *wake_deepest_mode(void);
s32 wake_init(void);

s32 wake_sources_assign(const struct resource_irq *irq, size_t n);

void wake_arm(s32 host);

#endif
