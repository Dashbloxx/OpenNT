#pragma once

#include <stdint.h>

extern uint16_t * vgabuffer;

void vga_movecursor(uint8_t x, uint8_t y);
void vga_write(char character);
void vga_clear();