#pragma once

#include <stdint.h>
#include <stdbool.h>

extern bool is_threading_initialized;

typedef uint32_t thread_id_t;

typedef struct thread
{
    thread_id_t thread_id;
    struct
    {
        uint32_t esp, ebp, eip;
    } registers;
    struct thread * next_thread;
} thread_t;

extern thread_t kernel_thread;
extern thread_t * current_thread;

void context_switch(thread_t * current_thread, thread_t * next_thread);
void thread_initialize();