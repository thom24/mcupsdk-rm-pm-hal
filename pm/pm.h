/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef PM_H
#define PM_H

#include <types/short_types.h>

/**
 *  \brief  Set Clock Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 set_clock_handler(u32 *msg_recv);

/**
 *  \brief  Get Clock Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 get_clock_handler(u32 *msg_recv);

/**
 *  \brief  Set Clock Parent Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 set_clock_parent_handler(u32 *msg_recv);

/**
 *  \brief  Get Clock Parent Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 get_clock_parent_handler(u32 *msg_recv);

/**
 *  \brief  Get Number of Clock Parents Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 get_num_clock_parents_handler(u32 *msg_recv);

/**
 *  \brief  Set clock frequency Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 set_freq_handler(u32 *msg_recv);

/**
 *  \brief  Query clock frequency Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 query_freq_handler(u32 *msg_recv);

/**
 *  \brief  Get clock frequency Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 get_freq_handler(u32 *msg_recv);

/**
 *  \brief  Set Device State Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 set_device_handler(u32 *msg_recv);

/**
 *  \brief  Get Device State Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 get_device_handler(u32 *msg_recv);

/**
 *  \brief  Set Device Resets Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 set_device_resets_handler(u32 *msg_recv);

/**
 *  \brief  Drop Device Ref counts Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 device_drop_powerup_ref_handler(u32 *msg_recv);

/**
 *  \brief  Wake up reason Get Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 wake_reason_handler(u32 *msg_recv);

/**
 *  \brief  Wake reset Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 wake_reset_handler(u32 *msg_recv);

/**
 *  \brief  Enable WDT Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 enable_wdt_handler(u32 *msg_recv);

/**
 *  \brief  Device Goodbye Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 goodbye_handler(u32 *msg_recv);

/**
 *  \brief  System Reset Handler PM Function.
 *
 *  \param  msg_recv Pointer to the recieved and returned message. Same buffer
 *                   used.
 *  \return ret      SUCCESS if the API executed successfully.
 *                   EFAIL   if the API failed to execute.
 */
s32 sys_reset_handler(u32 *msg_recv);

/**
 *  \brief  PM Send a secure Proxy response API
 *
 *  \param  resp    Pointer to Response message Header
 *  \param  flags   Flags set by the caller for AOP.
 *  \param  size    Size of the full response message.
 *  \param  status  Status returned by the message handler called before calling
 *                  this function.
 *  \return ret     SUCCESS if the API executed successfully.
 *                  EFAIL   if the API failed to execute.
 */
s32 pm_send_response(struct tisci_header *resp, u32 flags, u32 size, s32 status);

#endif /* PM_H */
