/*
 * System Firmware Source File
 *
 * Software defined Device groups (devgrps) for J7200 device.
 *
 * Data version: 190425_000000
 *
 * Copyright (C) 2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef SOC_J7200_DOMGRPS_H
#define SOC_J7200_DOMGRPS_H

#include <types/domgrps.h>

/**
 * identifier for system reset. It's for backward compatibility of the sys_reset().
   It will reset the WKUP, MCU, MAIN domain.
 */
#define SOC_DOMGRP_J7200_SYSTEM DOMGRP_COMPATIBILITY

/**
 * identifier for MCU_RESETz reset. It affects all domains (WKUP, MCU, MAIN).
 */
#define SOC_DOMGRP_J7200_MCU DOMGRP_00

/**
 * identifier for RESET_REQz reset. It affects the MAIN domain
 */
#define SOC_DOMGRP_J7200_MAIN DOMGRP_01


#endif /* SOC_J7200_DOMGRPS_H */
