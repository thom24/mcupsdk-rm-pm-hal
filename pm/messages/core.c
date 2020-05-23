/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#if defined (__TI_ARM_V7M3__)
#include <lib/str.h>
#include <lib/strncpy.h>
#include <msg/msg.h>
#include <osal/osal_core.h>
#include <osal/osal_msg.h>
#include <sleep.h>
#include <startup.h>
#include <tisci_provider/tisci.h>
#include <tisci/tisci_protocol.h>
#include <tisci/pm/tisci_pm_core.h>
#include <types/errno.h>
#include <wake.h>
#include <osal/osal_clock.h>
#include <sys-reset.h>

static s32 tisci_msg_wake_reason_handler(u32 *msg_recv)
{
	struct tisci_msg_wake_reason_req *req =
		(struct tisci_msg_wake_reason_req *) msg_recv;
	const struct sleep_mode *mode;
	const char *reason = "unk";
	s32 time_ms;
	s32 ret = SUCCESS;
	u32 flags = req->hdr.flags;

	time_ms = 0;
	mode = wake_deepest_mode();

	if ((flags & TISCI_MSG_FLAG_AOP) != 0UL) {
		struct tisci_msg_wake_reason_resp *resp =
			(struct tisci_msg_wake_reason_resp *) msg_recv;

		tisci_msg_clear_flags(&resp->hdr);

		resp->time_ms = time_ms;
		if (mode != NULL) {
			lib_strncpy(resp->mode, mode->name, sizeof(resp->mode));
		}
		lib_strncpy(resp->reason, reason, sizeof(resp->reason));

		tisci_msg_set_ack_resp(&resp->hdr);
		ret = osal_msg_response((u32 *) resp, sizeof(*resp));
	}

	return ret;
}

static struct tisci_client tisci_msg_wake_reason = {
	.handler	= tisci_msg_wake_reason_handler,
	.subsystem	= SUBSYSTEM_PM,
};

static s32 tisci_msg_wake_reset_handler(u32 *msg_recv)
{
	s32 ret = SUCCESS;
	struct tisci_msg_wake_reset_req *req =
		(struct tisci_msg_wake_reset_req *) msg_recv;
	struct tisci_msg_wake_reset_resp *resp =
		(struct tisci_msg_wake_reset_resp *) msg_recv;
	u32 flags = req->hdr.flags;
	u8 host = req->hdr.host;

	tisci_msg_clear_flags(&resp->hdr);

	if (ret == SUCCESS) {
		wake_arm(host);
	}

	if ((ret == SUCCESS) && (flags & TISCI_MSG_FLAG_AOP) != 0UL) {
		tisci_msg_set_ack_resp(&resp->hdr);
		ret = osal_msg_response((u32 *) resp, sizeof(*resp));
	}

	return ret;
}

static struct tisci_client tisci_msg_wake_reset = {
	.handler	= tisci_msg_wake_reset_handler,
	.subsystem	= SUBSYSTEM_PM,
};

static s32 tisci_msg_enable_wdt_handler(u32 *msg_recv)
{
	struct tisci_msg_enable_wdt_req *req =
		(struct tisci_msg_enable_wdt_req *) msg_recv;
	u32 flags = req->hdr.flags;
	s32 ret = SUCCESS;

	if ((flags & TISCI_MSG_FLAG_AOP) != 0UL) {
		struct tisci_msg_enable_wdt_resp *resp =
			(struct tisci_msg_enable_wdt_resp *) msg_recv;
		tisci_msg_clear_flags(&resp->hdr);
		tisci_msg_set_nak_resp(&resp->hdr);

		ret = osal_msg_response((u32 *) resp, sizeof(*resp));
	}

	return ret;
}

static struct tisci_client tisci_msg_enable_wdt = {
	.handler	= tisci_msg_enable_wdt_handler,
	.subsystem	= SUBSYSTEM_PM,
};

static s32 tisci_msg_goodbye_handler(u32 *msg_recv)
{
	struct tisci_msg_goodbye_req *req =
		(struct tisci_msg_goodbye_req *) msg_recv;
	u32 flags = req->hdr.flags;
	s32 ret = SUCCESS;

	if ((flags & TISCI_MSG_FLAG_AOP) != 0UL) {
		struct tisci_msg_goodbye_resp *resp =
			(struct tisci_msg_goodbye_resp *) msg_recv;

		tisci_msg_clear_flags(&resp->hdr);
		tisci_msg_set_nak_resp(&resp->hdr);

		ret = osal_msg_response((u32 *) resp, sizeof(*resp));
	}

	return ret;
}

static struct tisci_client tisci_msg_goodbye = {
	.handler	= tisci_msg_goodbye_handler,
	.subsystem	= SUBSYSTEM_PM,
};

static s32 tisci_msg_sys_reset_handler(u32 *msg_recv)
{
	struct tisci_msg_sys_reset_req *req =
		(struct tisci_msg_sys_reset_req *) msg_recv;
	struct tisci_msg_sys_reset_resp *resp =
			(struct tisci_msg_sys_reset_resp *) msg_recv;
	u32 flags = req->hdr.flags;
	domgrp_t domain = req->domain;
	s32 ret = SUCCESS;

	ret = system_reset(domain);

	if ((flags & TISCI_MSG_FLAG_AOP) != 0UL) {
		if (ret == SUCCESS) {
			tisci_msg_set_ack_resp(&resp->hdr);
		} else {
			tisci_msg_set_nak_resp(&resp->hdr);
		}
		ret = osal_msg_response((u32 *) resp, sizeof(*resp));
	}

	return ret;
}

static struct tisci_client tisci_msg_sys_reset = {
	.handler	= tisci_msg_sys_reset_handler,
	.subsystem	= SUBSYSTEM_PM,
};

s32 pm_core_message_init(void)
{
	s32 ret;

	ret = tisci_user_client_register(TISCI_MSG_WAKE_RESET,
					 &tisci_msg_wake_reset);

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_ENABLE_WDT,
						 &tisci_msg_enable_wdt);
	}

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_GOODBYE,
						 &tisci_msg_goodbye);
	}

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_SYS_RESET,
						 &tisci_msg_sys_reset);
	}

	if (ret == SUCCESS) {
		ret = tisci_user_client_register(TISCI_MSG_WAKE_REASON,
						 &tisci_msg_wake_reason);
	}

	return ret;
}
#endif
