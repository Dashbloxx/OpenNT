#pragma once

#include <stdint.h>

typedef struct
{
    uint16_t limit_lo : 16;
    uint16_t base_lo : 16;
    uint8_t base_mid : 8;
    uint8_t access : 8;
    uint8_t limit_hi : 4;
    uint8_t flags : 4;
    uint8_t base_hi : 8;
} __attribute__((packed)) gdt_t;

typedef struct
{
    uint16_t limit : 16;
    uint32_t base : 32;
} __attribute__((packed)) gdt_pointer_t;

typedef struct
{
    uint32_t prev_tss;
    uint32_t esp0, ss0, esp1, ss1, esp2, ss2;
    uint32_t cr3;
    uint32_t eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
    uint32_t es, cs, ss, ds, fs, gs;
    uint32_t ldt;
    uint16_t trap, iomap_base;
} __attribute__((packed)) tss_t;

void gdt_register(unsigned int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
void gdt_initialize();