ifneq ($(CONFIG_PM),)

obj-$(CONFIG_UDELAY) +=		udelay_m3.o

obj-y +=			cm3.o

endif

obj-y += lib/

CROSS_COMPILE ?= arm-linux-gnueabihf-

__src := $(src)

cppflags-y += -I$(__src)/include

cflags-y += --unaligned_access=off
cflags-y += --silicon_version=7M3 --code_state=16 --little_endian

aflags-y += --silicon_version=7M3 --code_state=16 --little_endian

ldflags-y += --disable_auto_rts

LD_SCRIPT = $(objtree)/app/linkercmd/arm.ld
extra-y += $(LD_SCRIPT)

TARGET = ti-sci-user-firmware.elf
