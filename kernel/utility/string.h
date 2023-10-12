#pragma once

#include <stdint.h>

void reverse(char * string, int length);
void itoa(int num, char * string, int base);
void memcpy(uint8_t *dest, const uint8_t *src, uint8_t len);
void memset(uint8_t *dest, uint8_t val, uint32_t len);