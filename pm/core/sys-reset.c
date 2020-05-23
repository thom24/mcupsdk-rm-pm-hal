/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <sys-reset.h>
#include <types/short_types.h>
#include <types/errno.h>
#include <types/domgrps.h>
#include <clk.h>
#include <device.h>
#include <lib/trace.h>

static s32 (*sys_reset_handler)(domgrp_t domain);

s32 system_reset(domgrp_t domain)
{
	s32 ret = -ENODEV;

	if (sys_reset_handler) {
		ret = sys_reset_handler(domain);
	}

	return ret;
}

void sys_reset_handler_register(s32 (*handler)(domgrp_t domain))
{
	sys_reset_handler = handler;
}
