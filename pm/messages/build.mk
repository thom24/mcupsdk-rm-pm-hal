ifneq ($(CONFIG_PM),)

obj-y += clock.o
obj-y += device.o
obj-y += core.o
obj-y += device_prepare.o

endif
