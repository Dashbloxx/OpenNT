#pragma once

typedef enum
{
    COM1 = 0x3F8,
    COM2 = 0x2F8
} serial_port_t;

int serial_initialize(serial_port_t serial_port);
char serial_read(serial_port_t serial_port);
void serial_write(serial_port_t serial_port, char character);

static char com1_read() { return serial_read(COM1); }
static void com1_write(char character) { serial_write(COM1, character); }