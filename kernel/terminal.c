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