#include <stdint.h>

#include "../utility/string.h"
#include "physmem.h"
#include "virtmem.h"
#include "paging.h"
#include "../io/terminal.h"
#include "../general/bounds.h"
#include "../drivers/vga/vga.h"

page_directory_t page_directory[1024] __attribute__((aligned(PAGE_SIZE)));
page_table_t page_tables0[1024] __attribute__((aligned(PAGE_SIZE)));

void virtmem_initialize()
{
	memset((uint8_t *)page_directory, 0, sizeof(page_directory_t) * 1024);
	memset((uint8_t *)page_tables0, 0, sizeof(page_table_t) * 1024);

	/* Map the kernel to 0xC0000000, for a higher-half kernel! */
	for(uint32_t i = 0; i < 1024; i++)
	{
		page_tables0[i].present = 1;
		page_tables0[i].read_write = 1;
		page_tables0[i].user = 0; /* Identify as kernel. */
		page_tables0[i].frame = i;
	}

	page_directory[0].present = 1;
	page_directory[0].read_write = 1;
	page_directory[0].user = 0; /* Identify as kernel. */
	page_directory[0].frame = ((uint32_t)page_tables0) >> 12;

	/* Load page directory & enable paging! */
	load_page_directory((uint32_t *)&page_directory);
	enable_paging();

	vgabuffer = (uint16_t *)0xC03FF000;
	terminal_printf(current_terminal, "Hello, world!\r\n");
}