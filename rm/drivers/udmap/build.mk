# Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/udmap/include
cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/udmap/soc/$(TARGET_SOC)

obj-$(CONFIG_RM_UDMAP) += rm_udmap.o

obj-$(CONFIG_RM_UDMAP) += soc/
