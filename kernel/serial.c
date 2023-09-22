#include "serial.h"
#include "port.h"

/**
 *  @brief Initialize serial driver.
 *  @param serial_port Are we initializing port COM1, or which port?
 *  @return If return value is 0, then the initialization succedded, if -1 however, then the initialization failed. 
 */
int serial_initialize(serial_port_t serial_port)
{
    outb(serial_port + 1, 0x00);
    outb(serial_port + 3, 0x80);
    outb(serial_port + 0, 0x03);
    outb(serial_port + 1, 0x00);
    outb(serial_port + 3, 0x03);
    outb(serial_port + 2, 0xC7);
    outb(serial_port + 4, 0x0B);
    outb(serial_port + 4, 0x1E);
    outb(serial_port + 0, 0xAE);

    if(inb(serial_port + 0) != 0xAE)
    {
        return -1;
    }

    outb(serial_port + 4, 0x0F);
    return 0;
}

/**
 *  @brief Read a single character from a specific serial port.
 *  @param serial_port Which serial port are we reading from?
 *  @return The character that is read.
 */
char serial_read(serial_port_t serial_port)
{
    while (!(inb(serial_port + 5) & 0x01));
    return inb(serial_port);
}

/**
 *  @brief Write a character into a specific serial port.
 *  @param serial_port Which serial port are we going to write to?
 *  @param character What character are we going to write to the serial port?
 */
void serial_write(serial_port_t serial_port, char character)
{
    while (!(inb(serial_port + 5) & 0x20));
    outb(serial_port, character);
}