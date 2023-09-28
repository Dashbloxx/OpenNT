#include "exception.h"
#include "terminal.h"

void exception_handler(int exception)
{
    terminal_printf(current_terminal, "Exception triggered!\r\nHere's the exception number: %d\r\n", exception);

    while(1) { asm volatile("hlt"); }
}