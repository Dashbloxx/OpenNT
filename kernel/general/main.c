#include <stddef.h>

#include "../interrupt/exception.h"
#include "../drivers/serial/serial.h"
#include "../io/terminal.h"
#include "../utility/multiboot.h"
#include "../interrupt/idt.h"
#include "main.h"
#include "../io/port.h"
#include "gdt.h"
#include "../interrupt/8259.h"
#include "../drivers/timer/pit.h"
#include "../interrupt/interrupt.h"

size_t installed_ram = 0;

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();

void main(multiboot_t * multiboot)
{
    ENABLE_INTERRUPTS;

    /* Initialize the GDT (Global Descriptor Table). This should be one of the very first things we set up here. */
    gdt_initialize();

    /*
     *  Let's calculate the amount of installed RAM, in bytes.
     *  The bootloader only tells us the size in KiB, so therefore we must multiply mem_lower & mem_upper by 1024, and then subtract
     *  around 1 megabyte to make sure we don't accidentally try to interact with memory outside of existing bounds. 
     */
    installed_ram = ((multiboot->mem_lower * 1024) + (multiboot->mem_upper * 1024) - (1024 * 1024));

    /* Initialize terminal(s)... */
    terminal_initialize();

    /* Initialize the IDT (Interrupt Descriptor Table)*/
    idt_initialize();

    /* Initialize the 8259 PIC. This allows us to specify when an interrupt has finished. */
    pic8259_setup();

    /* Register exceptions to the IDT. */
    idt_register(0, IDT_TRAPGATE, &isr0);
    idt_register(1, IDT_TRAPGATE, &isr1);
    idt_register(2, IDT_TRAPGATE, &isr2);
    idt_register(3, IDT_TRAPGATE, &isr3);
    idt_register(4, IDT_TRAPGATE, &isr4);
    idt_register(5, IDT_TRAPGATE, &isr5);
    idt_register(6, IDT_TRAPGATE, &isr6);
    idt_register(7, IDT_TRAPGATE, &isr7);
    idt_register(8, IDT_TRAPGATE, &isr8);
    idt_register(9, IDT_TRAPGATE, &isr9);
    idt_register(10, IDT_TRAPGATE, &isr10);
    idt_register(11, IDT_TRAPGATE, &isr11);
    idt_register(12, IDT_TRAPGATE, &isr12);
    idt_register(13, IDT_TRAPGATE, &isr13);
    idt_register(14, IDT_TRAPGATE, &isr14);
    idt_register(15, IDT_TRAPGATE, &isr15);
    idt_register(16, IDT_TRAPGATE, &isr16);
    idt_register(17, IDT_TRAPGATE, &isr17);
    idt_register(18, IDT_TRAPGATE, &isr18);
    idt_register(19, IDT_TRAPGATE, &isr19);
    idt_register(20, IDT_TRAPGATE, &isr20);
    idt_register(21, IDT_TRAPGATE, &isr21);
    idt_register(22, IDT_TRAPGATE, &isr22);
    idt_register(23, IDT_TRAPGATE, &isr23);
    idt_register(24, IDT_TRAPGATE, &isr24);
    idt_register(25, IDT_TRAPGATE, &isr25);
    idt_register(26, IDT_TRAPGATE, &isr26);
    idt_register(27, IDT_TRAPGATE, &isr27);
    idt_register(28, IDT_TRAPGATE, &isr28);
    idt_register(29, IDT_TRAPGATE, &isr29);
    idt_register(30, IDT_TRAPGATE, &isr30);
    idt_register(31, IDT_TRAPGATE, &isr31);
    idt_register(32, IDT_INTGATE, &irq0);

    pic8259_unmask(0);
    
    pit_setfreq(100);

    terminal_printf(current_terminal, "Copyright (C) Reapiu, hexOS.\r\nAll rights reserved.\r\n");

    DISABLE_INTERRUPTS;

    HALT;
}