#include <stddef.h>

#include "physmem.h"
#include "../utility/string.h"

physmem_info_t physmem_info;

int physmem_mmap_first_free()
{
    uint32_t i, j;

    for(i = 0; i < physmem_info.max_blocks; i++)
    {
        if(physmem_info.memory_map_array[i] != 0xffffffff)
        {
            for(j = 0; j < 32; j++)
            {
                int bit = 1 << j;
                if(!(physmem_info.memory_map_array[i] & bit))
                    return i * 32 + j;
            }
        }
    }
    return -1;
}

int physmem_mmap_first_free_by_size(uint32_t size)
{
    uint32_t i, j, k, free = 0;
    int bit;

    if(size == 0)
        return -1;

    if(size == 1)
        return physmem_mmap_first_free();

    for(i = 0; i < physmem_info.max_blocks; i++)
    {
        if(physmem_info.memory_map_array[i] != 0xffffffff)
        {
            for(j = 0; j < 32; j++)
            {
                bit = 1 << j;
                if(!(physmem_info.memory_map_array[i] & bit))
                {
                    for(k = j; k < 32; k++)
                    {
                        bit = 1 << k;
                        if(!(physmem_info.memory_map_array[i] & bit))
                            free++;
                        
                        if(free == size)
                            return i * 32 + j;
                    }
                }
            }
        }
    }
    return -1;
}

void physmem_initialize(uint32_t bitmap, uint32_t total_memory_size)
{
    physmem_info.memory_size = total_memory_size;
    physmem_info.memory_map_array = (uint32_t *)bitmap;
    physmem_info.max_blocks = total_memory_size / PAGE_SIZE;
    physmem_info.used_blocks = physmem_info.max_blocks;
    memset((uint8_t *)physmem_info.memory_map_array, 0xff, physmem_info.max_blocks * sizeof(uint32_t));
    physmem_info.memory_map_end = (uint32_t)&physmem_info.memory_map_array[physmem_info.max_blocks];
}

void physmem_initialize_region(uint32_t base, uint32_t region_size)
{
    int align = base / PAGE_SIZE;
    int blocks = region_size / PAGE_SIZE;

    while(blocks >= 0)
    {
        physmem_mmap_unset(align++);
        physmem_info.used_blocks--;
        blocks--;
    }
}

void physmem_uninitialize_region(uint32_t base, uint32_t region_size)
{
    int align = base / PAGE_SIZE;
    int blocks = region_size / PAGE_SIZE;

    while(blocks >= 0)
    {
        physmem_mmap_set(align++);
        physmem_info.used_blocks++;
        blocks--;
    }
}

void * physmem_alloc_block()
{
    if((physmem_info.max_blocks - physmem_info.used_blocks) <= 0)
        return NULL;

    int frame = physmem_mmap_first_free();
    if(frame == -1)
        return NULL;

    physmem_mmap_set(frame);

    uint32_t address = (frame * PAGE_SIZE) + physmem_info.memory_map_end;
    physmem_info.used_blocks++;

    return (void *)address;
}

void physmem_free_block(void * pointer)
{
    uint32_t address = (uint32_t)pointer;
    address -= physmem_info.memory_map_end;
    int frame = address / PAGE_SIZE;
    physmem_mmap_unset(frame);
    physmem_info.used_blocks--;
}

void * physmem_alloc_blocks(uint32_t size)
{
    uint32_t i;

    if((physmem_info.max_blocks - physmem_info.used_blocks) <= size)
        return NULL;

    int frame = physmem_mmap_first_free_by_size(size);
    if(frame == -1)
        return NULL;

    for(i = 0; i < size; i++)
        physmem_mmap_set(frame + i);

    uint32_t addr = (frame * PAGE_SIZE) + physmem_info.memory_map_end;
    physmem_info.used_blocks += size;

    return (void *)addr;
}

void physmem_free_blocks(void * pointer, uint32_t size)
{
    uint32_t i;

    uint32_t address = (uint32_t)pointer;
    address -= physmem_info.memory_map_end;
    int frame = address / PAGE_SIZE;
    for(i = 0; i < size; i++)
        physmem_mmap_unset(frame + i);
    physmem_info.used_blocks -= size;
}