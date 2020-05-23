/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef SYS_RESET_H
#define SYS_RESET_H

#include <types.h>
#include <types/sbool.h>
#include <types/domgrps.h>
#include <stddef.h>
#include <config.h>
#include <types/short_types.h>

/**
 * \brief Resets a domain group
 *
 * \param domain
 * The domain to be reset.
 *
 * \return SUCCESS if domain reset succeeds. Error value if fails.
 */
s32 system_reset(domgrp_t domain);

/**
 * \brief Register handler for the tisci system reset.
 *
 * \param handler Pointer to the tisci system reset handler function
 */
void sys_reset_handler_register(s32 (*handler)(domgrp_t domain));

#endif
