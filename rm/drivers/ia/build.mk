# Copyright (C) 2018-2020 Texas Instruments Incorporated - http://www.ti.com/
# ALL RIGHTS RESERVED

cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/ia/include
cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/irq/include
cppflags-y += -I$(srctree)/rm_pm_hal/rm/drivers/ia/soc/$(TARGET_SOC)/

obj-$(CONFIG_RM_IRQ) += rm_ia.o

obj-$(CONFIG_RM_IRQ) += soc/
