/*
 * Interrupt Management
 *
 * Interrupt management driver instance data definition
 *
 * Data version: 200730_091422
 *
 * Copyright (C) 2019-2021 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#include <types/short_types.h>
#include <types/array_size.h>
#include <devices.h>
#include <devices_internal.h>
#include <hosts.h>
#include <hosts_internal.h>
#include <soc/j7200/resasg_types.h>

#include "../../include/irq_resasg.h"
#include <irq_cfg.h>

/*
 * SoC devices capable of sourcing global events
 */
const u16 evt_rt_srcs[] = {
	J7200_DEV_NAVSS0_PROXY_0,
	J7200_DEV_NAVSS0_RINGACC_0,
	J7200_DEV_NAVSS0_TIMERMGR_0,
	J7200_DEV_NAVSS0_TIMERMGR_1,
	J7200_DEV_NAVSS0_UDMAP_0,
	J7200_DEV_NAVSS0_UDMASS_INTA_0,
	J7200_DEV_MCU_NAVSS0_PROXY0,
	J7200_DEV_MCU_NAVSS0_RINGACC0,
	J7200_DEV_MCU_NAVSS0_UDMAP_0,
	J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0,
};

const u32 evt_rt_srcs_count = ARRAY_SIZE(evt_rt_srcs);

const struct irq_global_event_type irq_global_event_types[] = {
	{
		.start = 0U,
		.num = 4608U,
		.utype = RESASG_UTYPE(J7200_DEV_NAVSS0_UDMASS_INTA_0, RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
	},
	{
		.start = 16384U,
		.num = 1536U,
		.utype = RESASG_UTYPE(J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0, RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
	},
	{
		.start = 20480U,
		.num = 1024U,
		.utype = RESASG_UTYPE(J7200_DEV_NAVSS0_MODSS_INTA_0, RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
	},
	{
		.start = 22528U,
		.num = 1024U,
		.utype = RESASG_UTYPE(J7200_DEV_NAVSS0_MODSS_INTA_1, RESASG_SUBTYPE_GLOBAL_EVENT_SEVT),
	},
	{
		.start = 32768U,
		.num = 512U,
		.utype = RESASG_UTYPE(J7200_DEV_NAVSS0_UDMASS_INTA_0, RESASG_SUBTYPE_GLOBAL_EVENT_MEVT),
	},
	{
		.start = 34816U,
		.num = 128U,
		.utype = RESASG_UTYPE(J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0, RESASG_SUBTYPE_GLOBAL_EVENT_MEVT),
	},
	{
		.start = 36864U,
		.num = 512U,
		.utype = RESASG_UTYPE(J7200_DEV_NAVSS0_UDMASS_INTA_0, RESASG_SUBTYPE_GLOBAL_EVENT_GEVT),
	},
	{
		.start = 39936U,
		.num = 256U,
		.utype = RESASG_UTYPE(J7200_DEV_MCU_NAVSS0_UDMASS_INTA_0, RESASG_SUBTYPE_GLOBAL_EVENT_GEVT),
	},
	{
		.start = 49152U,
		.num = 1024U,
		.utype = RESASG_UTYPE(J7200_DEV_NAVSS0_UDMAP_0, RESASG_SUBTYPE_GLOBAL_EVENT_TRIGGER),
	},
	{
		.start = 56320U,
		.num = 256U,
		.utype = RESASG_UTYPE(J7200_DEV_MCU_NAVSS0_UDMAP_0, RESASG_SUBTYPE_GLOBAL_EVENT_TRIGGER),
	},
};

const u16 irq_global_event_types_count = ARRAY_SIZE(irq_global_event_types);
