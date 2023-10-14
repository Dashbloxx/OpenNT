#pragma once

#include <stdint.h>

/**
 *  @brief A wrapper function for the `outb` instruction.
 *  @param port Where are we sending the byte to?
 *  @param data What's the byte that we're sending?
 */
static inline void outb(unsigned int port, uint8_t data)
{
    asm volatile("outb %b0, %w1" : : "a" (data), "Nd" (port));
}

/**
 *  @brief A wrapper function for the `inb` instruction.
 *  @param port From where should we be recieving from?
 *  @return The byte that `inb` recieves.
 */
static inline uint8_t inb(unsigned int port)
{
    uint8_t data;
    asm volatile("inb %w1, %b0" : "=a" (data) : "Nd" (port));
    return data;
}

/**
 *  @brief A wrapper function for the `outw` instruction.
 *  @param port Where are we sending the word to?
 *  @param data What's the word that we're sending?
 */
static inline void outw(unsigned int port, uint16_t data)
{
    asm volatile("outw %w0, %w1" : : "a" (data), "Nd" (port));
}

/**
 *  @brief A wrapper function for the `inw` instruction.
 *  @param port From where should we be recieving from?
 *  @return The word that `inw` recieves.
 */
static inline uint16_t inw(unsigned int port)
{
    uint16_t data;
    asm volatile("inw %w1, %w0" : "=a" (data) : "Nd" (port));
    return data;
}

/**
 *  @brief A wrapper function for the `outl` instruction.
 *  @param port Where are we sending the long to?
 *  @param data What's the long that we're sending?
 */
static inline void outl(unsigned int port, uint32_t data)
{
    asm volatile("outl %0, %w1" : : "a" (data), "Nd" (port));
}

/**
 *  @brief A wrapper function for the `inw` instruction.
 *  @param port From where should we be recieving from?
 *  @return The long that `inw` recieves.
 */
static inline uint32_t inl(unsigned int port)
{
    uint32_t data;
    asm volatile("inl %w1, %0" : "=a" (data) : "Nd" (port));
    return data;
}

/** @brief Wait a single instruction. */
static inline void io_wait()
{
    outb(0x80, 0);
}