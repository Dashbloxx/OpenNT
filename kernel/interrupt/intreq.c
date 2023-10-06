#include "intreq.h"
#include "../general/registers.h"
#include "../io/port.h"
#include "../io/terminal.h"
#include "8259.h"

void handle_irq(registers_t registers)
{
    terminal_printf(current_terminal, "An interrupt was made!\nInterrupt number: %d.\n", registers.int_no);    
    pic8259_eoi(registers.int_no);
}