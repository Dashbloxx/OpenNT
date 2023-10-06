#include <stdint.h>

#include "../../interrupt/8259.h"
#include "../../interrupt/idt.h"
#include "../../io/port.h"
#include "../../io/terminal.h"
#include "../../general/registers.h"
#include "pit.h"

void pit_setfreq(uint16_t freq)
{
    uint16_t divisor = TIMER_INPUT_CLOCK_FREQUENCY / freq;
    outb(TIMER_COMMAND_PORT, 0b00110110);
    outb(TIMER_CHANNEL_0_DATA_PORT, divisor & 0xFF);
    outb(TIMER_CHANNEL_0_DATA_PORT, (divisor >> 8) & 0xFF);
}