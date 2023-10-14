#pragma once

#include <stdint.h>

#include "../../io/port.h"

#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71
#define RTC_TICKS_PER_SECOND 32

typedef struct
{
    uint16_t year;
    uint8_t month, day, hour, minute, second;
} time_t;


/**
 *  @brief Obtain the update flag of the RTC clock.
 *  @return Returns the update flag.
 */
static inline uint8_t rtc_flag()
{
	outb(CMOS_ADDRESS, 0x0A);
	return inb(CMOS_DATA) & 0x80;
}

/**
 *  @brief Get the update register of the RTC clock.
 */
static inline uint8_t rtc_register(uint32_t reg)
{
	outb(CMOS_ADDRESS, reg);
	return inb(CMOS_DATA);
}