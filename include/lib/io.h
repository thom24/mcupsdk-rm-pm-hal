/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef IO_H
#define IO_H

#include <types/errno.h>
#include <types/short_types.h>
#include <types/address_types.h>

#ifndef ioremap
static inline local_phys_addr_t ioremap(local_phys_addr_t a)
{
	return a;
}
#endif

/**
 * \brief provide a simplified read u32 operation
 * \param a address to write to
 *
 * \return u32 value at the address pointed by a
 */
static inline u32 readl(local_phys_addr_t a)
{
	return *(volatile u32 *) (ioremap(a));
}

/**
 * \brief provide a simplified write u32 operation
 * \param v value
 * \param a address to write to
 */
static inline void writel(u32 v, local_phys_addr_t a)
{
	*(volatile u32 *) (ioremap(a)) = v;
}

/**
 * \brief provide a verified write u32 operation
 * \param v value
 * \param a address to write to
 *
 * \return SUCCESS if we readback the same value we wrote, else return
 * EFAILVERIFY
 */
static inline s32 writel_verified(u32 v, local_phys_addr_t a)
{
	u32 readback_val;
	s32 ret = SUCCESS;

	/* First write the value */
	writel(v, a);

	/* Read it back */
	readback_val = readl(a);

	if (readback_val != v) {
		ret = -EFAILVERIFY;
	}
	return ret;
}

/**
 * \brief provide a simplified read u16 operation
 * \param a address to write to
 *
 * \return u16 value at the address pointed by a
 */
static inline u16 readw(local_phys_addr_t a)
{
	return *(volatile u16 *) (ioremap(a));
}

/**
 * \brief provide a simplified write u16 operation
 * \param v value
 * \param a address to write to
 */
static inline void writew(u16 v, local_phys_addr_t a)
{
	*(volatile u16 *) (ioremap(a)) = v;
}

/**
 * \brief provide a verified write u16 operation
 * \param v value
 * \param a address to write to
 *
 * \return SUCCESS if we readback the same value we wrote, else return
 * EFAILVERIFY
 */
static inline s32 writew_verified(u16 v, local_phys_addr_t a)
{
	u16 readback_val;
	s32 ret = SUCCESS;

	/* First write the value */
	writew(v, a);

	/* Read it back */
	readback_val = readw(a);

	if (readback_val != v) {
		ret = -EFAILVERIFY;
	}
	return ret;
}

/**
 * \brief provide a simplified read u8 operation
 * \param a address to write to
 *
 * \return u8 value at the address pointed by a
 */
static inline u8 readb(local_phys_addr_t a)
{
	return *(volatile u8 *) (ioremap(a));
}

/**
 * \brief provide a simplified write u8 operation
 * \param v value
 * \param a address to write to
 */
static inline void writeb(u8 v, local_phys_addr_t a)
{
	*(volatile u8 *) (ioremap(a)) = v;
}

/**
 * \brief provide a verified write u8 operation
 * \param v value
 * \param a address to write to
 *
 * \return SUCCESS if we readback the same value we wrote, else return
 * EFAILVERIFY
 */
static inline s32 writeb_verified(u8 v, local_phys_addr_t a)
{
	u8 readback_val;
	s32 ret = SUCCESS;

	/* First write the value */
	writeb(v, a);

	/* Read it back */
	readback_val = readb(a);

	if (readback_val != v) {
		ret = -EFAILVERIFY;
	}
	return ret;
}

#endif
