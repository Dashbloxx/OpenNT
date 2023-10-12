#pragma once

#include <stdint.h>

typedef struct
{
    uint32_t start_address, end_address, size;
} free_memory_t;