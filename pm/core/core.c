/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#include <lib/str.h>
#include <lib/strncpy.h>
#include <lib/mmr_lock.h>
#include <osal/osal_core.h>
#include <sleep.h>
#include <startup.h>
#include <tisci/tisci_protocol.h>
#include <tisci/pm/tisci_pm_core.h>
#include <types/errno.h>
#include <wake.h>
#include <osal/osal_clock.h>
#include <sys-reset.h>
/* This header is in awkward place, but moving it breaks sysfw build */
#include <../pm/pm.h>

s32 wake_reason_handler(u32 *msg_recv)
{
	struct tisci_msg_wake_reason_resp *resp =
		(struct tisci_msg_wake_reason_resp *) msg_recv;
	const struct sleep_mode *mode;
	const char *reason = "unk";
	s32 time_ms;
	s32 ret = SUCCESS;

	mmr_unlock_all();
	time_ms = 0;
	mode = wake_deepest_mode();

	resp->hdr.flags = 0U;


	resp->time_ms = time_ms;
	if (mode != NULL) {
		lib_strncpy(resp->mode, mode->name, sizeof(resp->mode));
	}
	lib_strncpy(resp->reason, reason, sizeof(resp->reason));

	mmr_lock_all();

	return ret;
}

s32 wake_reset_handler(u32 *msg_recv)
{
	s32 ret = SUCCESS;
	struct tisci_msg_wake_reset_req *req =
		(struct tisci_msg_wake_reset_req *) msg_recv;
	struct tisci_msg_wake_reset_resp *resp =
		(struct tisci_msg_wake_reset_resp *) msg_recv;
	u8 host = req->hdr.host;

	resp->hdr.flags = 0U;

	mmr_unlock_all();

	if (ret == SUCCESS) {
		wake_arm(host);
	}

	mmr_lock_all();

	return ret;
}

s32 enable_wdt_handler(u32 *msg_recv)
{
	struct tisci_msg_enable_wdt_resp *resp =
		(struct tisci_msg_enable_wdt_resp *) msg_recv;
	s32 ret = EFAIL;

	resp->hdr.flags = 0U;

	return ret;
}

s32 goodbye_handler(u32 *msg_recv)
{
	struct tisci_msg_goodbye_resp *resp =
		(struct tisci_msg_goodbye_resp *) msg_recv;
	s32 ret = EFAIL;

	resp->hdr.flags = 0U;

	return ret;
}

s32 sys_reset_handler(u32 *msg_recv)
{
	struct tisci_msg_sys_reset_req *req =
		(struct tisci_msg_sys_reset_req *) msg_recv;
	struct tisci_msg_sys_reset_resp *resp =
		(struct tisci_msg_sys_reset_resp *) msg_recv;
	domgrp_t domain = req->domain;
	s32 ret = SUCCESS;

	mmr_unlock_all();

	resp->hdr.flags = 0U;
	ret = system_reset(domain);

	mmr_lock_all();

	return ret;
}
