#pragma once

#include <stdint.h>
#include <stdbool.h>

extern bool is_paging_enabled;

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
extern page_table_t page_tables[1024] __attribute__((aligned(4096)));

void virtmem_initialize();