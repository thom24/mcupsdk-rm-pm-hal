/*
 * System Firmware OSAL Messaging layer
 *
 * OSAL Core Messaging layer APIs
 *
 * Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef OSAL_MSG_H
#define OSAL_MSG_H

#include <types/short_types.h>

/**
 * \brief Retrieve message data associated with the current message being
 *	  processed by the current task.
 *
 * \param host Pointer to store the host for the message being processed.
 *
 * \param is_secure Pointer to flag indicating whether the current
 * message is received from current thread.
 *
 */
s32 osal_get_current_task_msg_data(u8 *host, u8 *is_secure);

/**
 * \brief Send a response back through the messaging hardware which will be
 *	  routed based on the OSALs knowledge of where the message came from.
 *
 * \param response Buffer containing the full TISCI response to send.
 * \param size Size of the message in bytes.
 *
 * \return 0 on success, error code otherwise.
 *
 */
s32 osal_msg_response(u32 *response, u32 size);

/**
 * \brief Send a message directly to a host using the messaging hardware
 *	  using a notification queue.
 *
 * \param host A host ID indicating which host's notification queue to use.
 * \param msg Buffer containing the full TISCI message to send.
 * \param size Size of the message in bytes.
 *
 * \return 0 on success, error code otherwise.
 *
 */
s32 osal_msg_send_notification(u8 host, u32 *msg, u32 size);

#endif  /* OSAL_MSG_H */
