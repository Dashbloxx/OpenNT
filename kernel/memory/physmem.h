#pragma once

#include <stdint.h>

#define PAGE_SIZE 4096

typedef struct
{
    uint32_t memory_size;
    uint32_t max_blocks;
    uint32_t * memory_map_array;
    uint32_t memory_map_end;
    uint32_t used_blocks;
} physmem_info_t;

extern physmem_info_t physmem_info;

static inline void physmem_mmap_set(int bit)
{
    physmem_info.memory_map_array[bit / 32] |= (1 << (bit % 32));
}

static inline void physmem_mmap_unset(int bit)
{
    physmem_info.memory_map_array[bit / 32] &= ~(1 << (bit % 32));
}

static inline char physmem_mmap_test(int bit)
{
    return physmem_info.memory_map_array[bit / 32] & (1 << (bit % 32));
}

static inline uint32_t physmem_get_max_blocks()
{
    return physmem_info.max_blocks;
}

static inline uint32_t physmem_get_used_blocks()
{
    return physmem_info.used_blocks;
}

int physmem_mmap_first_free();
int physmem_mmap_first_free_by_size(uint32_t size);

static inline int physmem_next_free_frame(int size)
{
    return physmem_mmap_first_free_by_size(size);
}

void physmem_initialize(uint32_t bitmap, uint32_t total_memory_size);
void physmem_initialize_region(uint32_t base, uint32_t region_size);
void physmem_uninitialize_region(uint32_t base, uint32_t region_size);
void * physmem_alloc_block();
void physmem_free_block(void * pointer);
void * physmem_alloc_blocks(uint32_t size);
void physmem_free_blocks(void * pointer, uint32_t size);