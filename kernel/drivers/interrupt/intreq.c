#include "intreq.h"
#include "../../general/registers.h"
#include "../../io/port.h"
#include "../../io/terminal.h"
#include "8259.h"
#include "../../context/thread.h"

uint32_t time = 0;

void handle_irq(registers_t registers)
{
    if(registers.interrupt == 32)
    {
        time++;
        terminal_printf(&terminals[0], "%d\r\n", time);
    }
    else
    {
        terminal_printf(current_terminal, "An interrupt was made!\nInterrupt number: %d.\n", registers.interrupt);
    }

    pic8259_eoi(registers.interrupt);
}