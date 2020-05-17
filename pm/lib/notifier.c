/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <notifier.h>

void notifier_call(struct list_head *head, void *data)
{
	struct notifier *n;
	struct notifier *next;

	/* *INDENT-OFF* */
	list_for_each_safe(head, n, next, node)
		n->fn(n, data);
	/* *INDENT-ON* */
}
