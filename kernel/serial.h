#pragma once

typedef enum
{
    COM1 = 0x3F8,
    COM2 = 0x2F8
} serial_port_t;

int serial_initialize(serial_port_t serial_port);
char serial_read(serial_port_t serial_port);
void serial_write(serial_port_t serial_port, char character);