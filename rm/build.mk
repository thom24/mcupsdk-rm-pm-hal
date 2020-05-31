# Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

cppflags-y += -I$(srctree)/rm_pm_hal/rm/
cppflags-y += -I$(srctree)/rm_pm_hal/rm/include
cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers

cppflags-y += -I$(srctree)/rm_pm_hal/include/soc/$(TARGET_SOC)

obj-y := core/ drivers/
