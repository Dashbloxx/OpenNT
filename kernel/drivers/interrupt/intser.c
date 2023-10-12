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

    /* Let's print the exception number! */
    terminal_printf(current_terminal, "Exception triggered!\r\nException number: %d.\r\nException message: %s!\r\n", registers.interrupt, exception_messages[registers.interrupt]);

    HALT;
}