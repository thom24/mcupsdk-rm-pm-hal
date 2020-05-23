obj-y := core/ soc/ lib/ drivers/
obj-$(CONFIG_ARM) += arch/
obj-y += messages/

cppflags-y += -I$(objtree)/rm_pm_hal/pm/include -I$(srctree)/rm_pm_hal/pm/include -I$(srcroot)/rm_pm_hal/pm/include
cppflags-y += -I$(srcroot)/security/include
cppflags-y += -I$(srcroot)/security/include/config/$(TARGET_SOC)
cppflags-y += -I$(ARM_CC_PATH)/include
