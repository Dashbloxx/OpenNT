#pragma once

#define DISABLE_INTERRUPTS asm volatile("cli")
#define ENABLE_INTERRUPTS asm volatile("sti")