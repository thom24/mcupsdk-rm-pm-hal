/*
 * Interrupt Management
 *
 * Interrupt management driver instance data definition
 *
 * Data version: 200505_104840
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/array_size.h>
#include <devices.h>
#include <devices_internal.h>
#include <hosts.h>
#include <hosts_internal.h>
#include <soc/am64x/resasg_types.h>

#include "../../include/irq_resasg.h"

/*
 * SoC devices capable of sourcing global events
 */
const u16 evt_rt_srcs[] = {
	AM64X_DEV_DMASS0_INTAGGR_0,
	AM64X_DEV_DMASS0_RINGACC_0,
};

const u32 evt_rt_srcs_count = ARRAY_SIZE(evt_rt_srcs);

const struct irq_global_event_type irq_global_event_types[] = {
	{
		.start = 0U,
		.num = 1536U,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_INTAGGR_0, RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
	},
	{
		.start = 8192U,
		.num = 128U,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_INTAGGR_0, RESASG_SUBTYPE_GLOBAL_EVENT_MEVT),
	},
	{
		.start = 10240U,
		.num = 256U,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_INTAGGR_0, RESASG_SUBTYPE_GLOBAL_EVENT_GEVT),
	},
	{
		.start = 32768U,
		.num = 32U,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_INTAGGR_0, RESASG_SUBTYPE_GLOBAL_EVENT_LEVT),
	},
	{
		.start = 50176U,
		.num = 136U,
		.utype = RESASG_UTYPE(AM64X_DEV_DMASS0_BCDMA_0, RESASG_SUBTYPE_GLOBAL_EVENT_TRIGGER),
	},
};

const u16 irq_global_event_types_count = ARRAY_SIZE(irq_global_event_types);
