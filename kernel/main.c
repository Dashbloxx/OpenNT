#include "serial.h"
#include "terminal.h"

void main()
{
    /* Initialize terminal(s)... */
    terminal_initialize();

    /* Print some basic text... */
    terminal_printf(current_terminal, "Hello, world!\r\n");

    while(1) { asm volatile("hlt"); }
}