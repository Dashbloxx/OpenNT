#pragma once

#include <stddef.h>

#include "../memory/free.h"

extern free_memory_t free_memory;

#define HALT while(1) { asm volatile("hlt"); }