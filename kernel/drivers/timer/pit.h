#pragma once

#include <stdint.h>

#define TIMER_INPUT_CLOCK_FREQUENCY 1193180
#define TIMER_CHANNEL_0_DATA_PORT 0x40
#define TIMER_CHANNEL_1_DATA_PORT 0x41
#define TIMER_CHANNEL_2_DATA_PORT 0x42
#define TIMER_COMMAND_PORT 0x43

void pit_setfreq(uint16_t freq);