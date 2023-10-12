#include <stdarg.h>
#include <stddef.h>

#include "terminal.h"
#include "../drivers/serial/serial.h"
#include "../utility/string.h"
#include "../drivers/vga/vga.h"

terminal_t terminals[32];
terminal_t * current_terminal;

/**
 *  @brief Initialize the terminal manager. 
 */
void terminal_initialize()
{
    serial_initialize(COM1);
    vga_clear();
    terminals[0].read = &com1_read;
    terminals[0].write = &com1_write;
    terminals[1].read = NULL;
    terminals[1].write = &vga_write;
    current_terminal = &terminals[1];
}

/**
 *  @brief Print a single character to a terminal.
 *  @param terminal Which terminal to print to?
 *  @param character What character to print?
 */
void terminal_putc(terminal_t * terminal, char character) { terminal->write(character); }

/**
 *  @brief Input a single character from a terminal.
 *  @param terminal Which terminal to input character from?
 *  @return Returns the character that was inputted. 
 */
char terminal_getchar(terminal_t * terminal) { return terminal->read(); }

/**
 *  @brief Print text into a terminal with format abilities.
 *  @param terminal Which terminal to print to?
 */
void terminal_printf(terminal_t * terminal, const char * format, ...)
{
    va_list args;
    va_start(args, format);

    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            switch(*format)
            {
                case 'c':
                    char c = va_arg(args, int);
                    terminal_putc(terminal, c);
                    break;
                case 's':
                    char * string0 = va_arg(args, char *);
                    while(*string0 != '\0')
                    {
                        terminal_putc(terminal, *string0);
                        string0++;
                    }
                    break;
                case 'd':
                    int num0 = va_arg(args, int);
                    char buffer0[12];
                    itoa(num0, buffer0, 10);
                    char *string1 = buffer0;
                    while(*string1 != '\0')
                    {
                        terminal_putc(terminal, *string1);
                        string1++;
                    }
                    break;
                case 'b':
                    int num1 = va_arg(args, int);
                    char buffer1[33];
                    buffer1[32] = '\0';
                    for(int i = 31; i >= 0; i--)
                    {
                        buffer1[i] = (num1 & 1) ? '1' : '0';
                        num1 >>= 1;
                    }
                    char *string2 = buffer1;
                    while (*string2 != '\0')
                    {
                        terminal_putc(terminal, *string2);
                        string2++;
                    }
                    break;
                case 'x':
                    int num2 = va_arg(args, int);
                    char buffer2[9];
                    for(int i = 0; i < 8; i++)
                    {
                        int nibble = (num2 >> ((7 - i) * 4)) & 0xF;
                        buffer2[i] = (nibble < 10) ? ('0' + nibble) : ('a' + nibble - 10);
                    }
                    buffer2[8] = '\0';
                    char * string3 = buffer2;
                    while(*string3 != '\0')
                    {
                        terminal_putc(terminal, *string3);
                        string3++;
                    }
                    break;
                case 'l':
                    format++;
                    if (*format == 'l' && *(format + 1) == 'x') {
                        uint64_t num3 = va_arg(args, uint64_t);
                        for (int i = 0; i < 16; i++) {
                            int nibble = (num3 >> ((15 - i) * 4)) & 0xF;
                            char hex_char = (nibble < 10) ? ('0' + nibble) : ('a' + nibble - 10);
                            terminal_putc(terminal, hex_char);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        else
        {
            terminal_putc(terminal, *format);
        }
        format++;
    }

    va_end(args);
}