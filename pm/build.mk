obj-y += soc/
obj-y += core/ 
obj-y += lib/
obj-y += drivers/
obj-y += messages/
obj-$(CONFIG_ARM) += arch/

cppflags-y += -I$(objtree)/rm_pm_hal/pm/include -I$(srctree)/rm_pm_hal/pm/include -I$(srcroot)/rm_pm_hal/pm/include
cppflags-y += -I$(ARM_CC_PATH)/include
