#include <stddef.h>

#include "exception.h"
#include "serial.h"
#include "terminal.h"
#include "multiboot.h"
#include "idt.h"

size_t installed_ram = 0;

void main(multiboot_t * multiboot)
{
    /*
     *  Let's calculate the amount of installed RAM, in bytes.
     *  The bootloader only tells us the size in KiB, so therefore we must multiply mem_lower & mem_upper by 1024, and then subtract
     *  around 1 megabyte to make sure we don't accidentally try to interact with memory outside of existing bounds. 
     */
    installed_ram = ((multiboot->mem_lower * 1024) + (multiboot->mem_upper * 1024) - (1024 * 1024));

    /* Initialize terminal(s)... */
    terminal_initialize();

    idt_initialize();
    idt_register(0, IDT_TRAPGATE, &wrapper0);

    while(1) { asm volatile("hlt"); }
}