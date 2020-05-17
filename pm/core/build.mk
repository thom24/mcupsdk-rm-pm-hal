ifneq (,$(CONFIG_PM))
obj-y := init.o sleep.o wake.o sys-reset.o
else
obj-y := startup.o
endif
