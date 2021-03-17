/*
 * DM Stub Firmware
 *
 * DM Stub main low power functionality
 *
 * Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
static void wait_for_debug(void)
{
	volatile unsigned long x = 0x12341234;

	while (x) {
	}
}

void dm_stub_entry(void)
{
	wait_for_debug();
}
