# Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/ra/include
cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/ra/soc/$(TARGET_SOC)

obj-$(CONFIG_RM_RA) += rm_ra.o

obj-$(CONFIG_RM_RA) += soc/
