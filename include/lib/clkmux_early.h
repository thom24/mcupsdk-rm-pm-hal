/*
 * System Firmware Early Clock Mux init code
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef CLKMUX_EARLY_H
#define CLKMUX_EARLY_H
#include <types/short_types.h>
#include <types/devgrps.h>

/**
 * \brief Contains functions for any clockmuxes that need to be initialized.
 *
 * \param devgrp devgrp being currently initialized
 *
 * \return SUCCESS on success, error code otherwise
 */
s32 clkmux_early_config(devgrp_t devgrp);

#endif /* CLKMUX_EARLY_H */
