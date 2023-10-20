#include <stdint.h>

#include "physmem.h"
#include "virtmem.h"
#include "paging.h"

page_directory_t page_directory[1024] __attribute__((aligned(PAGE_SIZE)));
page_table_t page_tables0[1024] __attribute__((aligned(PAGE_SIZE)));

void virtmem_initialize()
{
	memset(page_directory, 0, sizeof(page_directory_t) * 1024);
	memset(page_tables0, 0, sizeof(page_table_t) * 1024);

	for (int i = 0; i < 1024; i++)
	{
		page_directory[i].read_write = 1;
		page_directory[i].user = 1;
	}

	for (int i = 0; i < 1024; i++)
	{
		page_tables0[i].present = 1;
		page_tables0[i].read_write = 1;
		page_tables0[i].user = 1;
		page_tables0[i].frame = (i * PAGE_SIZE) >> 12;
	}

	page_directory[0].present = 1;
	page_directory[0].accessed = 0;
	page_directory[0].user = 1;
	page_directory[0].frame = ((uint32_t)page_tables0) >> 12;

	load_page_directory((uint32_t *)&page_directory);
	enable_paging();
}