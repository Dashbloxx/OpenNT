#pragma once

#include <stdint.h>

typedef struct Registers
{
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, user_esp, ss; 
} registers_t;

typedef void (*interrupt_t)(registers_t *);