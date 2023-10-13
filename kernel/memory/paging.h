#pragma once

#include <stdint.h>

extern void load_page_directory(uint32_t *);
extern void enable_paging();