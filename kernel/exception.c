#include "exception.h"
#include "terminal.h"

void interrupt0()
{
    terminal_printf(current_terminal, "Division by zero attempted!\r\nProcessor halted.\r\n");

    while(1) { asm volatile("hlt"); }
}