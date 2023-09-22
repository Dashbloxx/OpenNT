#include <stdarg.h>

#include "terminal.h"
#include "serial.h"

terminal_t terminals[32];
terminal_t * current_terminal;

/**
 *  @brief Initialize the terminal manager. 
 */
void terminal_initialize()
{
    terminals[0].read = &com1_read;
    terminals[0].write = &com1_write;
    current_terminal = &terminals[0];
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
                    char * string = va_arg(args, char *);
                    while(*string != '\0')
                    {
                        terminal_putc(terminal, *string);
                        string++;
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