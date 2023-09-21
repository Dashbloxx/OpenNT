TOOLPREFIX = i686-elf-
CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)as
QEMU = qemu-system-i386
NASM = nasm
NASMFLAGS = -felf
CFLAGS = -std=gnu99 -ffreestanding -I.
LDFLAGS = -Tlinker.ld -ffreestanding -nostdlib -nostdinc

SRCS := $(wildcard kernel/*.c)
ASMS := $(wildcard kernel/*.S)
ARCH_SRCS := $(wildcard kernel/arch/i386/*.c)
ARCH_ASMS := $(wildcard kernel/arch/i386/*.S)
OBJS := $(ASMS:.S=.o) $(SRCS:.c=.o) $(ARCH_ASMS:.S=.o) $(ARCH_SRCS:.c=.o)

all: kernel.bin

kernel.bin: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.S
	$(AS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	qemu-system-i386 -kernel kernel.bin -m 512M

clean:
	rm -f kernel/*.o kernel/arch/i386/*.o kernel.bin

.PHONY run clean all