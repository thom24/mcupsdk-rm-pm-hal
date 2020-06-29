# Copyright (C) 2017-2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

obj-y := core/ soc/ lib/ drivers/
obj-$(CONFIG_ARM) += arch/


cppflags-y += -I$(srctree)/rm_pm_hal/pm/
cppflags-y += -I$(srctree)/rm_pm_hal/pm/include
cppflags-y += -I$(ARM_CC_PATH)/include
