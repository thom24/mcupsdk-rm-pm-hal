/*
 * System Firmware Source File
 *
 * Host IDs for AM64X device
 *
 * Data version: 220401_092028
 *
 * Copyright (C) 2019-2022, Texas Instruments Incorporated
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
#ifndef AM64X_HOSTS_H
#define AM64X_HOSTS_H

/** DMSC(Secure): Device Management and Security Control */
#define HOST_ID_DMSC (0U)
/** MAIN_0_R5_0(Secure): Cortex R5_0 context 0 on Main island(BOOT) */
#define HOST_ID_MAIN_0_R5_0 (35U)
/** MAIN_0_R5_1(Non Secure): Cortex R5_0 context 1 on Main island */
#define HOST_ID_MAIN_0_R5_1 (36U)
/** MAIN_0_R5_2(Secure): Cortex R5_0 context 2 on Main island */
#define HOST_ID_MAIN_0_R5_2 (37U)
/** MAIN_0_R5_3(Non Secure): Cortex R5_0 context 3 on Main island */
#define HOST_ID_MAIN_0_R5_3 (38U)
/** A53_0(Secure): Cortex a53 context 0 on Main islana - ATF */
#define HOST_ID_A53_0 (10U)
/** A53_1(Non Secure): Cortex A53 context 1 on Main island - EL2/Hyp */
#define HOST_ID_A53_1 (11U)
/** A53_2(Non Secure): Cortex A53 context 2 on Main island - VM/OS1 */
#define HOST_ID_A53_2 (12U)
/** A53_3(Non Secure): Cortex A53 context 3 on Main island - VM2/OS2 */
#define HOST_ID_A53_3 (13U)
/** M4_0(Non Secure): M4 */
#define HOST_ID_M4_0 (30U)
/** MAIN_1_R5_0(Secure): Cortex R5_1 context 0 on Main island */
#define HOST_ID_MAIN_1_R5_0 (40U)
/** MAIN_1_R5_1(Non Secure): Cortex R5_1 context 1 on Main island */
#define HOST_ID_MAIN_1_R5_1 (41U)
/** MAIN_1_R5_2(Secure): Cortex R5_1 context 2 on Main island */
#define HOST_ID_MAIN_1_R5_2 (42U)
/** MAIN_1_R5_3(Non Secure): Cortex R5_1 context 3 on Main island */
#define HOST_ID_MAIN_1_R5_3 (43U)
/** ICSSG_0(Non Secure): ICSSG context 0 on Main island */
#define HOST_ID_ICSSG_0 (50U)

/**
 * Host catch all. Used in board configuration resource assignments to define
 * resource ranges useable by all hosts. Cannot be used
 */
#define HOST_ID_ALL (128U)

/** Number of unique hosts on the SoC */
#define HOST_ID_CNT (15U)

#endif /* AM64X_HOSTS_H */
