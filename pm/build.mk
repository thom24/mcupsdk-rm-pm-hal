obj-y := core/ soc/ lib/ drivers/
obj-$(CONFIG_ARM) += arch/

cppflags-y += -I$(srctree)/rm_pm_hal/pm/include -I$(srctree)/rm_pm_hal/pm/include
cppflags-y += -I$(ARM_CC_PATH)/include
