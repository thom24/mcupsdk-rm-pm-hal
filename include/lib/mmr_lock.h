/*
 * System Firmware Utility function
 *
 * Utility function for MMR Lock and Unlock
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */
#ifndef MMR_LOCK_H
#define MMR_LOCK_H

/** \brief Function to unlock the Control module MMRs needed for PM to
 *         function.
 */
void mmr_unlock_all(void);

/** \brief Function to lock the Control module MMRs needed for PM to
 *         ensure no other software entity can play around with these
 *         registers.
 */
void mmr_lock_all(void);

#endif /* MMR_LOCK_H */
