#include <stddef.h>

#include "exception.h"
#include "serial.h"
#include "terminal.h"
#include "multiboot.h"
#include "idt.h"
#include "main.h"

size_t installed_ram = 0;

extern void wrapper0();
extern void wrapper1();
extern void wrapper2();
extern void wrapper3();
extern void wrapper4();
extern void wrapper5();
extern void wrapper6();
extern void wrapper7();
extern void wrapper8();
extern void wrapper9();
extern void wrapper10();
extern void wrapper11();
extern void wrapper12();
extern void wrapper13();
extern void wrapper14();
extern void wrapper15();
extern void wrapper16();
extern void wrapper17();
extern void wrapper18();
extern void wrapper19();
extern void wrapper20();
extern void wrapper21();
extern void wrapper22();
extern void wrapper23();
extern void wrapper24();
extern void wrapper25();
extern void wrapper26();
extern void wrapper27();
extern void wrapper28();
extern void wrapper29();
extern void wrapper30();
extern void wrapper31();

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
    idt_register(1, IDT_TRAPGATE, &wrapper1);
    idt_register(2, IDT_TRAPGATE, &wrapper2);
    idt_register(3, IDT_TRAPGATE, &wrapper3);
    idt_register(4, IDT_TRAPGATE, &wrapper4);
    idt_register(5, IDT_TRAPGATE, &wrapper5);
    idt_register(6, IDT_TRAPGATE, &wrapper6);
    idt_register(7, IDT_TRAPGATE, &wrapper7);
    idt_register(8, IDT_TRAPGATE, &wrapper8);
    idt_register(9, IDT_TRAPGATE, &wrapper9);
    idt_register(10, IDT_TRAPGATE, &wrapper10);
    idt_register(11, IDT_TRAPGATE, &wrapper11);
    idt_register(12, IDT_TRAPGATE, &wrapper12);
    idt_register(13, IDT_TRAPGATE, &wrapper13);
    idt_register(14, IDT_TRAPGATE, &wrapper14);
    idt_register(15, IDT_TRAPGATE, &wrapper15);
    idt_register(16, IDT_TRAPGATE, &wrapper16);
    idt_register(17, IDT_TRAPGATE, &wrapper17);
    idt_register(18, IDT_TRAPGATE, &wrapper18);
    idt_register(19, IDT_TRAPGATE, &wrapper19);
    idt_register(20, IDT_TRAPGATE, &wrapper20);
    idt_register(21, IDT_TRAPGATE, &wrapper21);
    idt_register(22, IDT_TRAPGATE, &wrapper22);
    idt_register(23, IDT_TRAPGATE, &wrapper23);
    idt_register(24, IDT_TRAPGATE, &wrapper24);
    idt_register(25, IDT_TRAPGATE, &wrapper25);
    idt_register(26, IDT_TRAPGATE, &wrapper26);
    idt_register(27, IDT_TRAPGATE, &wrapper27);
    idt_register(28, IDT_TRAPGATE, &wrapper28);
    idt_register(29, IDT_TRAPGATE, &wrapper29);
    idt_register(30, IDT_TRAPGATE, &wrapper30);
    idt_register(31, IDT_TRAPGATE, &wrapper31);

    int i = 0 / 2;
    int j = 0;
    j = i / 0;
    i = j / 0;

    HALT;
}