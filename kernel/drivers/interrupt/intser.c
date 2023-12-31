#include "intser.h"
#include "../../io/terminal.h"
#include "../../general/main.h"
#include "../../general/registers.h"
#include "interrupt.h"

char * exception_messages[32] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void handle_isr(registers_t registers)
{
    /* Let's make sure to disable interrupts & then call a halt loop! */
    DISABLE_INTERRUPTS;

    if(registers.interrupt == 14)
    {
        uint32_t fault_origin;
        asm volatile("mov %%cr2, %0" : "=r"(fault_origin));

        /* Let's print the exception number, and the faulting address!s */
        terminal_printf(current_terminal, "Exception triggered!\r\nException number: %d.\r\nException message: %s!\r\nOrigin of page fault: %x.\r\nError code: %d.\r\n", registers.interrupt, exception_messages[registers.interrupt], fault_origin, registers.error);
    }
    else
    {
        /* Let's print the exception number! */
        terminal_printf(current_terminal, "Exception triggered!\r\nException number: %d.\r\nException message: %s!\r\n", registers.interrupt, exception_messages[registers.interrupt]);
    }

    HALT;
}