/*
 * Array Size support Macro
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef ARRAY_SIZE_H
#define ARRAY_SIZE_H

/**
 * ARRAY_SIZE - get the number of elements in a visible array
 * \param arr the array whose size you want.
 * WARNING: There is no type checking of any form
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#endif /* ARRAY_SIZE_H */
