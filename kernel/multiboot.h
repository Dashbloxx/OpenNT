#pragma once

#include <stdint.h>

/*
 *  This structure contains the layout of the multiboot info structure, which is given by the bootloader. Refer to this page (3.3):
 *  https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
 *  for more information.
 */

typedef struct
{
    uint32_t flags;
    uint32_t mem_lower, mem_upper;
    uint32_t boot_device;
    char * cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    char * bootloader;
    uint32_t apm_table;
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
} __attribute__((packed)) multiboot_t;