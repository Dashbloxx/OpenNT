#pragma once

#include <stddef.h>

extern size_t installed_ram;

#define HALT while(1) { asm volatile("hlt"); }