#pragma once

#include <stdint.h>

/*
 *  These are wrapper functions for the instructions inb, inw, inl, outb, outw, and outl. They
 *  are useful for communicating with hardware easily, such as with serial ports.
 */

static inline void outb(unsigned int port, uint8_t data)
{
    asm volatile("outb %b0, %w1" : : "a" (data), "Nd" (port));
}

static inline uint8_t inb(unsigned int port)
{
    uint8_t data;
    asm volatile("inb %w1, %b0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline void outw(unsigned int port, uint16_t data)
{
    asm volatile("outw %w0, %w1" : : "a" (data), "Nd" (port));
}

static inline uint16_t inw(unsigned int port)
{
    uint16_t data;
    asm volatile("inw %w1, %w0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline void outl(unsigned int port, uint32_t data)
{
    asm volatile("outl %0, %w1" : : "a" (data), "Nd" (port));
}

static inline uint32_t inl(unsigned int port)
{
    uint32_t data;
    asm volatile("inl %w1, %0" : "=a" (data) : "Nd" (port));
    return data;
}