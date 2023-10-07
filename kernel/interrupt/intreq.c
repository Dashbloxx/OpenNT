#include "intreq.h"
#include "../general/registers.h"
#include "../io/port.h"
#include "../io/terminal.h"
#include "8259.h"

uint32_t time = 0;

void handle_irq(registers_t registers)
{
    if(registers.int_no == 32)
    {
        time++;
        terminal_printf(current_terminal, "%d\n", time);
    }
    else
    {
        terminal_printf(current_terminal, "An interrupt was made!\nInterrupt number: %d.\n", registers.int_no);
    }

    pic8259_eoi(registers.int_no);
}