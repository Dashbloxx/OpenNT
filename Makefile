TOOLPREFIX = i686-elf-
CC = $(TOOLPREFIX)gcc
AS = $(TOOLPREFIX)as
QEMU = qemu-system-i386
CFLAGS = -std=gnu99 -ffreestanding -I. -g
LDFLAGS = -Tlinker.ld -ffreestanding -nostdlib -nostdinc -g

SRCS := $(wildcard kernel/**/*.c)
ASMS := $(wildcard kernel/**/*.S)
OBJS := $(patsubst %.S,%.o,$(shell find kernel -name '*.S')) $(patsubst %.c,%.o,$(shell find kernel -name '*.c'))

all: kernel.bin

kernel.bin: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.S
	$(AS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	qemu-system-i386 -kernel kernel.bin -m 512M

debug:
	qemu-system-i386 -s -S -kernel kernel.bin -m 512M

clean:
	find kernel -name "*.o" -type f -delete
	rm -f kernel.bin

.PHONY: run debug clean all