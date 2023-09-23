#pragma once

#include <stdint.h>

#define IDT_INTGATE 0x6
#define IDT_TRAPGATE 0x7
#define IDT_PRESENT 0x80
#define IDT_GATE32 0x8
#define IDT_DPL3 0x60
#define IDT_SIZE 256

typedef struct
{
    uint16_t base_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed)) idt_t;

typedef struct
{
    uint16_t limit;
    idt_t * base;
} __attribute__((packed)) idt_pointer_t;

void idt_register(uint8_t vecnum, uint8_t gatetype, void (* base)());
void idt_unregister(uint8_t vecnum);
void idt_initialize();