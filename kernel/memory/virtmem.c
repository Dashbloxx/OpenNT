#include <stdbool.h>

#include "virtmem.h"
#include "physmem.h"
#include "../utility/string.h"

bool is_paging_enabled = false;

page_directory_t page_directory[1024] __attribute__((aligned(4096)));
page_table_t page_tables[1024] __attribute__((aligned(4096)));

void virtmem_initialize()
{
    int i;
    uint32_t cr0;

    memset((uint8_t *)page_directory, 0, sizeof(page_directory_t) * 1024);
    memset((uint8_t *)page_tables, 0, sizeof(page_table_t) * 1024);

    for(i = 0; i < 1024; i++)
    {
        page_directory[i].read_write = 1;
        page_directory[i].user = 1;
    }

    for(i = 0; i < 1024; i++)
    {
        page_tables[i].present = 1;
        page_tables[i].read_write = 1;
        page_tables[i].user = 1;
        page_tables[i].frame = (i * PAGE_SIZE) >> 12;
    }

    page_directory[0].present = 1;
    page_directory[0].accessed = 0;
    page_directory[0].user = 1;
    page_directory[0].frame = 0x11a;

    asm volatile("mov %0, %%cr3" ::"r"(page_directory));

    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 = cr0 | 0x80000000;
    asm volatile("mov %0, %%cr0" ::"r"(cr0));

    is_paging_enabled = true;
}