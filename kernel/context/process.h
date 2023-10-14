#pragma once

#include <stdint.h>
#include <stddef.h>

#include "thread.h"

typedef uint32_t process_id_t;

typedef struct
{
    process_id_t process_id;
    struct threads
    {
        thread_t * array;
        size_t size;
    };
} process_t;