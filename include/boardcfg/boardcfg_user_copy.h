/*
 * System Firmware Source File
 *
 * Board configuration internal copy API on HS devices
 *
 * Copyright (C) 2019-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef BOARDCFG_COPY_USER_H
#define BOARDCFG_COPY_USER_H

#include <config.h>
#include <types/address_types.h>

/**
 * \brief on GP, copy the boardcfg after size check. On HS, validate the binary and copy to destination.
 *
 * \param host ID of the host sending the message
 * \param to address in DMSC IRAM where the boardcfg needs to be copied to
 * \param from SOC address from which boardcfg needs to be picked up
 * \param size Size of the board configuration to be copied
 * \param max_size maximum size of board configuration buffer
 *
 * \return SUCCESS on pass, error code on fail
 */
s32 boardcfg_memcpy_rm(u8 host, local_phys_addr_t to, soc_phys_addr_t from, u32 size, u32 max_size);

#endif
