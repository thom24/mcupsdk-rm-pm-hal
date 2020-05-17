ifneq ($(CONFIG_PM),)

obj-y := ilog.o div64.o
obj-y += notifier.o

else

obj-y := div64.o

endif
