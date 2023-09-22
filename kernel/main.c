#include "serial.h"
#include "terminal.h"

void main()
{
    terminal_initialize();

    current_terminal->write('h');

    /* Initialize COM1 serial port, and then print the character 'a' to COM1... */
    serial_initialize(COM1);
    serial_write(COM1, 'a');

    while(1) { asm volatile("hlt"); }
}