#include <stdint.h>

#include "vga.h"
#include "../../io/port.h"

uint16_t * vgabuffer = (uint16_t *)0xB8000;
uint8_t cursor_x = 0, cursor_y = 0;

/**
 *  @brief Move the cursor to a specific set of coordinates.
 *  @param x The X coordinate of where the cursor should go.
 *  @param y The Y coordinate of where the cursor should go.
 */
void vga_movecursor(uint8_t x, uint8_t y)
{
    uint16_t cursor_location = y * 80 + x;
    outb(0x3D4, 14);
    outb(0x3D5, cursor_location >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursor_location);
}

/**
 *  @brief Write a single character to VGA text-mode buffer. Shift text up by one if needed.
 *  @param character What character are we going to print?
 */
void vga_write(char character)
{
    uint8_t attribute_byte0 = (0 << 4) | (7 & 0x0F);
    uint16_t attribute = attribute_byte0 << 8;
    uint16_t * location;

    if(character == 0x08 && cursor_x)
    {
        cursor_x--;
    }
    else if(character == 0x09)
    {
        cursor_x = (cursor_x + 8) & ~(8 - 1);
    }
    else if(character == '\r')
    {
        cursor_x = 0;
    }
    else if(character == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else if(character >= ' ')
    {
        location = vgabuffer + (cursor_y * 80 + cursor_x);
        *location = character | attribute;
        cursor_x++;
    }


    if(cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
    }

    uint8_t attribute_byte1 = (0 << 4) | (7 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte1 << 8);

    if(cursor_y >= 25)
    {
        int i;
        for (i = 0 * 80; i < 24 * 80; i++)
        {
            vgabuffer[i] = vgabuffer[i + 80];
        }

        for (i = 24 * 80; i < 25 * 80; i++)
        {
            vgabuffer[i] = blank;
        }

        cursor_y = 24;
    }

    vga_movecursor(cursor_x, cursor_y);
} 

/**
 *  @brief Clear the VGA text-mode buffer.
 */
void vga_clear()
{
    uint8_t attribute_byte = (0 << 4) | (7 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);

    for(int i = 0; i < 80 * 25; i++)
    {
        vgabuffer[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    vga_movecursor(cursor_x, cursor_y);
}