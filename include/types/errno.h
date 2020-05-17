/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef ERRNO_H
#define ERRNO_H

/** Success */
#define SUCCESS         0
/** Error for permission */
#define EPERM           1
/** Verification Failed */
#define EFAILVERIFY     9
/** Try Again later */
#define EAGAIN          11
/** Device Busy */
#define EBUSY           16
/** No such device */
#define ENODEV          19
/** Invalid args */
#define EINVAL          22
/** Initialization failed */
#define EINIT           25
/** Deferred */
#define EDEFER          517
/** Timed out */
#define ETIMEDOUT       110
/** Operation failed */
#define EFAIL           427
/** Internal error due to corruption */
#define ECONFUSED       436

#endif
