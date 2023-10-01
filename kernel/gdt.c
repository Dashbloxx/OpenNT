#include "gdt.h"

gdt_t gdt[6];
gdt_pointer_t gdt_pointer;
tss_t tss;

void gdt_register(unsigned int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    gdt_t * entry = gdt + idx;

    entry->base_lo = base & 0xFFFF;
    entry->base_mid = (base >> 16) & 0xFF;
    entry->base_hi = (base >> 24) & 0xFF;

    entry->limit_lo = limit & 0xFFFF;
    entry->limit_hi = (limit >> 16) & 0xF;

    entry->access = access;
    entry->flags = flags & 0xF;
}

void gdt_initialize()
{
    gdt_pointer.limit = 6 * sizeof(gdt_t) - 1;
    gdt_pointer.base = (unsigned int)&gdt;

    gdt_register(0, 0, 0, 0, 0);
    gdt_register(1, 0, 0xfffff, 0x9a, 0xc);
    gdt_register(2, 0, 0xfffff, 0x92, 0xc);
    gdt_register(3, 0, 0xfffff, 0xfa, 0xc);
    gdt_register(4, 0, 0xfffff, 0xf2, 0xc);
    gdt_register(5, (unsigned int)&tss, sizeof(tss_t), 0xe9, 0);

    tss.ss0 = 0x10;
    tss.cs = 0x8 | 3;
    tss.ss = tss.ds = tss.es = tss.fs = tss.gs = 0x10 | 3;
    tss.iomap_base = sizeof(tss_t);

    asm volatile("lgdt %0\n"
                "movw %%ax, %%ds\n"
                "movw %%ax, %%es\n"
                "movw %%ax, %%fs\n"
                "movw %%ax, %%gs\n"
                "movw %%ax, %%ss\n"
                "ljmpl $0x8, $1f\n"
                "1:" ::"m"(gdt_pointer),
                "a"(0x10));

    asm volatile("ltr %%ax" ::"a"(0x2b));
}