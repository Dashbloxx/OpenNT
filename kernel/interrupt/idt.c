#include <stdint.h>

#include "idt.h"
#include "../io/port.h"

/*
 *  Create an array of IDT entries, which contain the type of interrupt & the address to the
 *  interrupt handler.
 */
idt_t idt[IDT_SIZE];

/*
 *  Create a structure that serves as a pointer to the IDT entry array, which can be
 *  understood by the CPU.
 */
idt_pointer_t idt_pointer;

/**
 *  @brief Register an entry to the IDT.
 *  @param vecnum The vector number in the IDT array (which index to register to)
 *  @param gatetype What type of interrupt? It can be either IDT_INTGATE or IDT_TRAPGATE.
 *  @param base The function to be registered.
 */
void idt_register(uint8_t vecnum, uint8_t gatetype, void (* base)())
{
    idt_t * description = &idt[vecnum];
    description->selector = 8;
    description->base_low = (uint32_t)base & 0xffff;
    description->base_high = (uint32_t)base >> 16;
    description->reserved = 0;
    description->flags = gatetype | IDT_PRESENT | IDT_GATE32 | IDT_DPL3;
}

/**
 *  @brief Unregister an interrupt.
 *  @param vecnum Which interrupt are we going to unregister?
 */
void idt_unregister(uint8_t vecnum)
{
    idt[vecnum].flags = 0;
}

/**
 *  @brief Initialize the IDT pointer structure, point it to the IDT entry array, and
 *         feed it to the CPU.
 */
void idt_initialize() 
{
    for(int i = 0; i < IDT_SIZE; i++)
        idt_unregister(i);
    
    idt_pointer.limit = IDT_SIZE * sizeof(idt_t);
    idt_pointer.base = idt;
    asm volatile("lidt %0" ::"m"(idt_pointer) : "memory");
}
