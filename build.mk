obj-y := pm/ utils/

cppflags-y += -I$(srctree)/rm_pm_hal/include
cppflags-y += -I$(srctree)/rm_pm_hal/include/soc/$(TARGET_SOC)
cppflags-y += -I$(TOOLCHAIN_PATH_M3)/include
