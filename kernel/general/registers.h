#pragma once

#include <stdint.h>

/**
 *  @brief A structure representing the i386 CPU's registers. Also contains two
 *         values that tell us the current interrupt called & error, which is
 *         for use with interrupt handlers.
 */
typedef struct
{
    uint32_t ds, edi, esi, ebp, esp, ebx, edx, ecx, eax, interrupt, error, eip, cs, eflags, useresp, ss;
} registers_t;