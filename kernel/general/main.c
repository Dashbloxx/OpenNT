#include <stddef.h>

#include "../drivers/interrupt/intser.h"
#include "../drivers/serial/serial.h"
#include "../io/terminal.h"
#include "../utility/multiboot.h"
#include "../drivers/interrupt/idt.h"
#include "main.h"
#include "../io/port.h"
#include "gdt.h"
#include "../drivers/interrupt/8259.h"
#include "../drivers/timer/pit.h"
#include "../drivers/interrupt/interrupt.h"
#include "../memory/physmem.h"
#include "../memory/free.h"

extern uint8_t __kernel_section_start;
extern uint8_t __kernel_section_end;
extern uint8_t __kernel_text_section_start;
extern uint8_t __kernel_text_section_end;
extern uint8_t __kernel_data_section_start;
extern uint8_t __kernel_data_section_end;
extern uint8_t __kernel_rodata_section_start;
extern uint8_t __kernel_rodata_section_end;
extern uint8_t __kernel_bss_section_start;
extern uint8_t __kernel_bss_section_end;

free_memory_t free_memory;

extern void interrupt0();
extern void interrupt1();
extern void interrupt2();
extern void interrupt3();
extern void interrupt4();
extern void interrupt5();
extern void interrupt6();
extern void interrupt7();
extern void interrupt8();
extern void interrupt9();
extern void interrupt10();
extern void interrupt11();
extern void interrupt12();
extern void interrupt13();
extern void interrupt14();
extern void interrupt15();
extern void interrupt16();
extern void interrupt17();
extern void interrupt18();
extern void interrupt19();
extern void interrupt20();
extern void interrupt21();
extern void interrupt22();
extern void interrupt23();
extern void interrupt24();
extern void interrupt25();
extern void interrupt26();
extern void interrupt27();
extern void interrupt28();
extern void interrupt29();
extern void interrupt30();
extern void interrupt31();
extern void interrupt32();

void main(multiboot_t * multiboot)
{
    DISABLE_INTERRUPTS;

    /* Initialize the GDT (Global Descriptor Table). This should be one of the very first things we set up here. */
    gdt_initialize();

    /* Initialize terminal(s)... */
    terminal_initialize();

    terminal_printf(current_terminal, "Searching for the right memory map...\r\n");
    for(int i = 0; i < multiboot->mmap_length; i += sizeof(multiboot_mmap_t))
    {
        multiboot_mmap_t * mmap = (multiboot_mmap_t *)(multiboot->mmap_addr + i);
        if(mmap->type != MMT_AVAILABLE)
        {
            terminal_printf(current_terminal, "Found memory map entry, but it's not about avaliable memory...\r\n");
            continue;
        }
        if(mmap->addr_low == (uint32_t)&__kernel_text_section_start)
        {
            free_memory.start_address = (uint32_t)&__kernel_section_end + 1024 * 1024;
            free_memory.end_address = mmap->addr_low + mmap->len_low;
            free_memory.size = free_memory.end_address - free_memory.start_address;
            terminal_printf(current_terminal, "Found available memory map entry!\r\nStart address of free memory: %x.\r\nEnd address of free memory: %x.\r\nSize of free memory: %x.\r\n", free_memory.start_address, free_memory.end_address, free_memory.size);
        }
    }

    terminal_printf(current_terminal, "Finished scanning memory map entries!\r\nAmount of free RAM: %d!\r\n", free_memory.size);

    /* Initialize the IDT (Interrupt Descriptor Table)*/
    idt_initialize();

    /* Initialize the 8259 PIC. This allows us to specify when an interrupt has finished. */
    pic8259_setup();

    /* Register exceptions to the IDT. */
    idt_register(0, IDT_TRAPGATE, &interrupt0);
    idt_register(1, IDT_TRAPGATE, &interrupt1);
    idt_register(2, IDT_TRAPGATE, &interrupt2);
    idt_register(3, IDT_TRAPGATE, &interrupt3);
    idt_register(4, IDT_TRAPGATE, &interrupt4);
    idt_register(5, IDT_TRAPGATE, &interrupt5);
    idt_register(6, IDT_TRAPGATE, &interrupt6);
    idt_register(7, IDT_TRAPGATE, &interrupt7);
    idt_register(8, IDT_TRAPGATE, &interrupt8);
    idt_register(9, IDT_TRAPGATE, &interrupt9);
    idt_register(10, IDT_TRAPGATE, &interrupt10);
    idt_register(11, IDT_TRAPGATE, &interrupt11);
    idt_register(12, IDT_TRAPGATE, &interrupt12);
    idt_register(13, IDT_TRAPGATE, &interrupt13);
    idt_register(14, IDT_TRAPGATE, &interrupt14);
    idt_register(15, IDT_TRAPGATE, &interrupt15);
    idt_register(16, IDT_TRAPGATE, &interrupt16);
    idt_register(17, IDT_TRAPGATE, &interrupt17);
    idt_register(18, IDT_TRAPGATE, &interrupt18);
    idt_register(19, IDT_TRAPGATE, &interrupt19);
    idt_register(20, IDT_TRAPGATE, &interrupt20);
    idt_register(21, IDT_TRAPGATE, &interrupt21);
    idt_register(22, IDT_TRAPGATE, &interrupt22);
    idt_register(23, IDT_TRAPGATE, &interrupt23);
    idt_register(24, IDT_TRAPGATE, &interrupt24);
    idt_register(25, IDT_TRAPGATE, &interrupt25);
    idt_register(26, IDT_TRAPGATE, &interrupt26);
    idt_register(27, IDT_TRAPGATE, &interrupt27);
    idt_register(28, IDT_TRAPGATE, &interrupt28);
    idt_register(29, IDT_TRAPGATE, &interrupt29);
    idt_register(30, IDT_TRAPGATE, &interrupt30);
    idt_register(31, IDT_TRAPGATE, &interrupt31);
    idt_register(32, IDT_INTGATE, &interrupt32);

    /*
     *  The minimum frequency for the PIT is 4Hz. We want things to tick slowly
     *  so that we can tell what's going on. We don't need context switches to
     *  happen that fast anyways, right?
     */
    pit_setfreq(4);

    physmem_initialize(free_memory.start_address, free_memory.size);

    ENABLE_INTERRUPTS;

    while(1);

    DISABLE_INTERRUPTS;

    HALT;
}