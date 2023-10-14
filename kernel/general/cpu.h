#pragma once

#include <stdint.h>

/**
 *  @brief Obtain the CPU vendor.
 *  @return A 32-byte string containing the CPU vendor.
 */
static inline char * cpu_vendr()
{
	static char vendor[32] = {0};
	__asm__ __volatile__(
		"mov $0, %%eax;\n"
		"cpuid;\n"
		"lea (%0), %%eax;\n"
		"mov %%ebx, (%%eax);\n"
		"mov %%edx, 0x4(%%eax);\n"
		"mov %%ecx, 0x8(%%eax)\n"
		: "=m"(vendor));
	return vendor;
}

/**
 *  @brief Not documented yet.
 */
static inline void cpu_cpuid(int code, uint32_t * a, uint32_t * d)
{
	asm volatile("cpuid"
				 : "=a"(*a), "=d"(*d)
				 : "a"(code)
				 : "ecx", "ebx");
}
