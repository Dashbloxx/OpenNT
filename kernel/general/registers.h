#pragma once

#include <stdint.h>

typedef struct Registers
{
    uint32_t ds, edi, esi, ebp, esp, ebx, edx, ecx, eax, interrupt, err, eip, cs, eflags, useresp, ss;
} registers_t;