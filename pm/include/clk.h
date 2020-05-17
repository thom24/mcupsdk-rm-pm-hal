/*
 * System Firmware
 *
 * Cortex-M3 (CM3) firmware for power management
 *
 * Copyright (C) 2015-2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef CLK_H
#define CLK_H

#include <types/sbool.h>
#include <stddef.h>
#include <types/short_types.h>
#include <types.h>
#include <pm_types.h>
#include <config.h>
#include <lib/bitops.h>

#define FREQ_GHZ(freq)  ((u32) (freq * 1000000000.0))
#define FREQ_MHZ(freq)  ((u32) (freq * 1000000.0))
#define FREQ_KHZ(freq)  ((u32) (freq * 1000.0))
#define FREQ_HZ(freq)   ((u32) (freq))

#define CLK_RANGE(id, min, max) [(id)] = \
{ .min_hz = (min), .max_hz = (max) }

#define CLK_DEFAULT(id, min, target, max) [(id)] = \
{ .min_hz = (min), .target_hz = (target), .max_hz = (max) }

#define CLK_RANGE_ANY 0

/* Type */
#define CLK_TYPE_CLK    0
#define CLK_TYPE_DIV    1
#define CLK_TYPE_MUX    2

/* clk_data flags */
#define CLK_DATA_FLAG_MODIFY_PARENT_FREQ        BIT(0)
#define CLK_DATA_FLAG_ALLOW_FREQ_CHANGE         BIT(1)

#define CLK_FLAG_PWR_UP_EN                      ((u8) BIT(0))
#define CLK_FLAG_PLL_BYPASS_FREQ                ((u8) BIT(1)) /* For PLLs */
#define CLK_FLAG_INITIALIZED                    ((u8) BIT(2))

/** set if a cached frequency is stored in freq_idx (used for PLLs) */
#define CLK_FLAG_CACHED                         ((u8) BIT(3))

#define CLK_HW_STATE_DISABLED   0
#define CLK_HW_STATE_ENABLED    1
#define CLK_HW_STATE_TRANSITION 2

#define CLK_ID_NONE ((clk_idx_t) (-1U))

struct clk_range {
	u32	min_hz;
	u32	max_hz;
};

struct clk_default {
	u32	min_hz;
	u32	target_hz;
	u32	max_hz;
};

struct clk {
	u8	ref_count;
	u8	ssc_block_count;
	u8	freq_change_block_count;
	u8	flags;
};

/* Only allows div up to 63, and clk_ids up to 1023 */
struct clk_parent {
	u16	clk : 10;
	u16	div : 6;
};

struct clk_drv_data {
};

struct clk_data {
	const struct clk_drv		*drv;
	const struct clk_drv_data	*data;
	struct clk_parent		parent;
	u16				freq_idx;
	u8				range_idx;
	u8				type : 2;
	u8				flags : 6;
};

struct clk_drv {
	/** Perform any necessary intitialization */
	s32 (*init)(struct clk *clk);

	/**
	 * \brief Set the current state of a clock.
	 *
	 * \param clk The clock to modify
	 * \param enabled True to enable, SFALSE to gate/power down
	 *
	 * \return STRUE if the action succeeded
	 */
	sbool (*set_state)(struct clk *clk, sbool enabled);

	/**
	 * \brief Get the current state of a clock.
	 *
	 * \param clk The clock to query
	 *
	 * \return STRUE if the clock is running
	 */
	u32 (*get_state)(struct clk *clk);

	/**
	 * \brief Program a clock to run at a given frequency. The minimum
	 * and maximum frequency parameters allow the best nearest match
	 * to be chosen. The clock tree is walked to accomplish this.
	 *
	 * \param clk The clock to modify/query
	 * \param target_hz The target frequency in Hz
	 * \param min_hz The minimum acceptable frequency
	 * \param max_hz The maximum acceptable frequency
	 * \param query STRUE to only determine what the result of the function
	 * would be if query were set to SFALSE, but do nothing.
	 *
	 * \return Best frequency found in Hz, returns 0 for failure
	 */
	u32 (*set_freq)(struct clk *clk, u32 target_hz, u32 min_hz, u32 max_hz, sbool query, sbool *changed);

	/**
	 * \brief Return the frequency this clock runs at.
	 *
	 * \param clk The clock to query
	 *
	 * \return The frequency in Hz
	 */
	u32 (*get_freq)(struct clk *clk);

	/**
	 * \brief Notify a clock that its parent frequency has changed.
	 *
	 * \param clk The clock to query
	 * \param parent_freq_hz The new parent frequency in Hz.
	 * \param query STRUE to only determine if the clock (and it's children)
	 * would accept this change, SFALSE to actually modify the clock tree.
	 *
	 * \return True if the change (would) succeed
	 */
	sbool (*notify_freq)(struct clk *clk, u32 parent_freq_hz, sbool query);
};

struct clk_data_reg {
	struct clk_drv_data	data;
	u32			reg;
	u8			bit;
};

/** The table of dynamic clock data */
extern struct clk soc_clocks[];

/** The table of const clock data */
extern const struct clk_data soc_clock_data[];

/** The table of shared const clock ranges */
extern const struct clk_range soc_clock_ranges[];

/** The table of default frequencies */
extern const struct clk_default soc_clock_freq_defaults[];

/** The table of dynamic stored clock frequencies (for freq_idx) */
extern u32 soc_clock_values[];

/** The total number of SoC clocks */
extern const size_t soc_clock_count;

u32 clk_value_set_freq(struct clk *clk, u32 target_hz, u32 min_hz, u32 max_hz, sbool query, sbool *changed);
u32 clk_value_get_freq(struct clk *clk);

/**
 * \brief Determine if a clock ID is valid.
 *
 * \param id
 * The internal clock API ID.
 *
 * \return
 * True if the clock ID refers to a valid SoC clock, SFALSE otherwise
 */
static inline sbool clk_id_valid(clk_idx_t id)
{
	return id < soc_clock_count && soc_clock_data[id].drv;
}

/**
 * \brief Lookup an internal clock based on a clock ID
 *
 * This does a lookup of a clock based on the clock ID.
 *
 * \param id
 * The internal clock API ID.
 *
 * \return
 * The clock pointer, or NULL if the clock ID was not valid.
 */
static inline struct clk *clk_lookup(clk_idx_t id)
{
	return clk_id_valid(id) ? (soc_clocks + id) : NULL;
}

/**
 * \brief Return the clock ID based on a clock pointer.
 *
 * The clock pointer is just an index into the array of clocks. This is
 * used to return a clock ID. This function has no error checking for NULL
 * pointers.
 *
 * \param clk
 * The clock pointer.
 *
 * \return
 * The clock ID.
 */
static inline clk_idx_t clk_id(struct clk *clk)
{
	return clk - soc_clocks;
}

/**
 * \brief Return a shared clock range.
 *
 * The clock infrastructure contains a set of shared clock ranges. Many
 * clocks and PLLs have min/max ranges. However, these min/max ranges can
 * take up a significant amount of storage. As many clocks share the same
 * ranges, we use a shared table of ranges. The clocks can then index that
 * table with a small u8.
 *
 * \param idx
 * The index into the range table.
 *
 * \return
 * The range associated with the index, no error checking is performed.
 */
static inline const struct clk_range *clk_get_range(clk_idx_t idx)
{
	return soc_clock_ranges + idx;
}

/**
 * \brief Return the clk_data struct associated with a clock.
 *
 * The clock pointer is translated to a clock index based on it's position
 * in the soc_clocks array. That index is then used to find the correct
 * element within the soc_clock_data array.
 *
 * \param clk
 * The clock for which a clk_data struct should be returned.
 *
 * \return
 * The pointer to the clk_data struct. No error checking is performed.
 */
static inline const struct clk_data *clk_get_data(struct clk *clk)
{
	return soc_clock_data + clk_id(clk);
}

u32 clk_get_parent_freq(struct clk *clk);
sbool clk_notify_freq(struct clk *clk, u32 parent_freq_hz, sbool query);
sbool clk_notify_sibling_freq(struct clk *clk, struct clk *parent, u32 parent_freq, sbool query);
sbool clk_notify_children_freq(struct clk *parent, u32 parent_freq, sbool query);

u32 __clk_generic_set_freq(struct clk *clk, struct clk *parent, u32 target_hz, u32 min_hz, u32 max_hz, sbool query, sbool *changed, s32 div);
u32 clk_set_freq(struct clk *clk, u32 target_hz, u32 min_hz, u32 max_hz, sbool query, sbool *changed);
u32 clk_get_freq(struct clk *clk);
s32 clk_get_state(struct clk *clk);
sbool clk_set_state(struct clk *clk, sbool enable);
sbool clk_get(struct clk *clk);
void clk_put(struct clk *clk);
void clk_ssc_allow(struct clk *clk);
void clk_ssc_block(struct clk *clk);
void clk_freq_change_allow(struct clk *clk);
void clk_freq_change_block(struct clk *clk);

extern const struct clk_drv clk_drv_input;

s32 clk_init(void);

#ifdef CONFIG_CLOCK
void clk_drop_pwr_up_en(void);
#else
static inline void clk_drop_pwr_up_en(void)
{
}
#endif


#endif
