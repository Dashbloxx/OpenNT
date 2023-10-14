#pragma once

#include <stdint.h>

enum {USER_MODE = 1, KERNEL_MODE = 0};

typedef enum
{
    TS_RUN,
    TS_WAITIO,
    TS_WAITCHILD,
    TS_SLEEP,
    TS_SELECT,
    TS_SUSPEND,
    TS_CRITICAL,
    TS_UNINTERRUPTIBLE,
    TS_DEAD,
} thread_state_t;

typedef struct _thread_t
{
    uint32_t thread_id;
    uint32_t user_mode;

    thread_state_t thread_state;

    struct
    {
        uint32_t eax, ecx, edx, ebx;
        uint32_t esp, ebp, esi, edi;
        uint32_t eip, eflags;
        uint32_t cs:16, ss:16, ds:16, es:16, fs:16, gs:16;
        uint32_t cr3;
    } registers __attribute__ ((packed));

    struct
    {
        uint32_t esp0;
        uint16_t ss0;
        uint32_t stack_start;
    } kstack __attribute__ ((packed));

    struct _thread_t * next;
} thread_t;

typedef void (*function_t)();

extern thread_t * first_thread;
extern thread_t * current_thread;

void thread_initialize();
void thread_create_kthread(function_t func, thread_t * thread);
void thread_resume(thread_t * thread);
void thread_switch_to(thread_t * thread, int mode);