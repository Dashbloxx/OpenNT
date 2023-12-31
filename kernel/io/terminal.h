#pragma once

typedef struct
{
    char (* read)();
    void (* write)(char character);
} terminal_t;

extern terminal_t terminals[];
extern terminal_t * current_terminal;

void terminal_initialize();
void terminal_putc(terminal_t * terminal, char character);
char terminal_getchar(terminal_t * terminal);
void terminal_printf(terminal_t * terminal, const char * format, ...);