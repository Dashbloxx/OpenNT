#include "serial.h"
#include "terminal.h"

void main()
{
    /* Initialize terminal(s)... */
    terminal_initialize();

    /* Print some basic text... */
    terminal_printf(current_terminal, "Hello, world!\r\nHere's a number: %d!\r\n", 123456789);

    while(1) { asm volatile("hlt"); }
}