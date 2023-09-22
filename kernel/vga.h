#pragma once

#include <stdint.h>

void vga_movecursor(uint8_t x, uint8_t y);
void vga_scroll();
void vga_write(char character);
void vga_clear();