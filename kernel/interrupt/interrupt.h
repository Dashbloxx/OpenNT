#pragma once

#define DISABLE_INTERRUPTS asm volatile("sti")
#define ENABLE_INTERRUPTS asm volatile("cli")