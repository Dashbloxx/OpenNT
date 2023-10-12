#include <stdint.h>

#include "string.h"

void reverse(char * string, int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        char temp = string[start];
        string[start] = string[end];
        string[end] = temp;
        start++;
        end--;
    }
}

void itoa(int num, char * string, int base)
{
    int i = 0;
    int is_negative = 0;

    if(num == 0)
    {
        string[i++] = '0';
        string[i] = '\0';
        return;
    }

    if(num < 0 && base == 10)
    {
        is_negative = 1;
        num = -num;
    }

    while(num != 0)
    {
        int rem = num % base;
        string[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    if(is_negative && base == 10)
    {
        string[i++] = '-';
    }

    string[i] = '\0';

    reverse(string, i);
}

void memcpy(uint8_t *dest, const uint8_t *src, uint8_t len)
{
    const uint8_t *sp = (const uint8_t *)src;
    uint8_t *dp = (uint8_t *)dest;
    for(; len != 0; len--) *dp++ = *sp++;
}

void memset(uint8_t *dest, uint8_t val, uint32_t len)
{
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}