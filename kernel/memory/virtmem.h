#pragma once

#include <stdint.h>

/*
 *  Make it easier to distinguish whether we're working with physical addresses
 *  or virtual addresses.
 */
typedef uint32_t physaddr_t;
typedef uint32_t virtaddr_t;

static inline uint32_t page_directory_index(virtaddr_t virtaddr)
{
    return virtaddr >> 22;
}

static inline uint32_t page_table_index(virtaddr_t virtaddr)
{
    return (virtaddr >> 12) & 0x3ff;
}

#define PAGE_PHYSICAL_ADDRESS(directory_entry) ((*directory_entry) & ~0xFFF)
#define SET_ATTRIBUTE(entry, attribute) (*entry |= attribute)
#define CLEAR_ATTRIBUTE(entry, attribute) (*entry &= ~attribute)
#define TEST_ATTRIBUTE(entry, attribute) (*entry & attribute)
#define SET_FRAME(entry, address) (*entry = (*entry & ~0x7FFFF000) | address)

typedef enum
{
    PTF_PRESENT = 0x01,
    PTF_RW = 0x02,
    PTF_USER = 0x04,
    PTF_WRITE_THROUGH = 0x08,
    PTF_CACHE_DISABLE = 0x10,
    PTF_ACCESSED = 0x20,
    PTF_DIRTY = 0x40,
    PTF_PAT = 0x80,
    PTF_GLOBAL = 0x100,
    PTF_FRAME = 0x7FFFF000
} page_table_flags_t;

typedef enum
{
    PDF_PRESENT = 0x01,
    PDF_RW = 0x02,
    PDF_USER = 0x04,
    PDF_WRITE_THROUGH = 0x08,
    PDF_CACHE_DISABLE = 0x10,
    PDF_ACCESSED = 0x20,
    PDF_DIRTY = 0x40,
    PDF_PAGE_SIZE = 0x80,
    PDF_GLOBAL = 0x100,
    PDF_PAT = 0x2000,
    PDF_FRAME = 0x7FFFF000
} page_directory_flags_t;

typedef struct
{
    uint32_t present:1;
    uint32_t read_write:1;
    uint32_t user:1;
    uint32_t write_through:1;
    uint32_t cache:1;
    uint32_t accessed:1;
    uint32_t dirty:1;
    uint32_t page_size:1;
    uint32_t global:1;
    uint32_t available:3;
    uint32_t frame:20;
} page_directory_t;

typedef struct
{
    uint32_t present:1;
    uint32_t read_write:1;
    uint32_t user:1;
    uint32_t write_through:1;
    uint32_t cache:1;
    uint32_t accessed:1;
    uint32_t dirty:1;
    uint32_t page_size:1;
    uint32_t global:1;
    uint32_t available:3;
    uint32_t frame:20;
} page_table_t;

extern page_directory_t page_directory[1024] __attribute__((aligned(4096)));
extern page_table_t page_tables0[1024] __attribute__((aligned(4096)));

void virtmem_initialize();