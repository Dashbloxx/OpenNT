#include <stddef.h>

#include "thread.h"
#include "../drivers/interrupt/interrupt.h"
#include "../general/gdt.h"
#include "../utility/string.h"
#include "../memory/physmem.h"

thread_t kernel_thread;
thread_t * first_thread;
thread_t * current_thread;

uint32_t thread_id = 0;

void thread_initialize()
{
    thread_t * thread = &kernel_thread;
    memset((uint8_t*)thread, 0, sizeof(thread_t));

    thread->thread_id = thread_id++;
    thread->user_mode = 0;

    thread->thread_state = TS_RUN;

    uint32_t selector = 0x10;

    thread->registers.ss = selector;
    thread->registers.eflags = 0x0;
    thread->registers.cs = 0x08;
    //thread->registers.eip = NULL;
    thread->registers.eip = 0;
    thread->registers.ds = selector;
    thread->registers.es = selector;
    thread->registers.fs = selector;
    thread->registers.gs = selector;

    thread->registers.esp = 0;

    thread->kstack.ss0 = 0x10;
    thread->kstack.esp0 = 0;


    first_thread = thread;
    current_thread = thread;
}

void thread_create_kthread(function_t func, thread_t * thread)
{
    memset((uint8_t*)thread, 0, sizeof(thread_t));


    thread->thread_id = thread_id++;

    thread->user_mode = 0;

    thread->thread_state = TS_RUN;

    uint32_t selector = 0x10;

    thread->registers.ss = selector;
    thread->registers.eflags = 0x0;
    thread->registers.cs = 0x08;
    thread->registers.eip = (uint32_t)func;
    thread->registers.ds = selector;
    thread->registers.es = selector;
    thread->registers.fs = selector;
    thread->registers.gs = selector;

    uint8_t* stack = physmem_alloc_block();

    thread->registers.esp = (uint32_t)(stack + PAGE_SIZE - 4);

    thread->kstack.ss0 = 0x10;
    thread->kstack.esp0 = 0;
    thread->kstack.stack_start = (uint32_t)stack;

    thread_t * pointer = current_thread;

    while (pointer->next != NULL)
    {
        pointer = pointer->next;
    }

    pointer->next = thread;
}

void thread_switch_to(thread_t * thread, int mode)
{
    uint32_t kesp, eflags;
    uint16_t kss, ss, cs;

    tss.ss0 = thread->kstack.ss0;
    tss.esp0 = thread->kstack.esp0;

    ss = thread->registers.ss;
    cs = thread->registers.cs;
    eflags = (thread->registers.eflags | 0x200) & 0xFFFFBFFF;

    if(mode == USER_MODE)
    {
        kss = thread->kstack.ss0;
        kesp = thread->kstack.esp0;
    }
    else
    {
        kss = thread->registers.ss;
        kesp = thread->registers.esp;
    }

    asm("	mov %0, %%ss; \
        mov %1, %%esp; \
        cmpl %[KMODE], %[mode]; \
        je nextt; \
        push %2; \
        push %3; \
        nextt: \
        push %4; \
        push %5; \
        push %6; \
        push %7; \
        ljmp $0x08, $switch_task"
        :: \
        "m"(kss), \
        "m"(kesp), \
        "m"(ss), \
        "m"(thread->registers.esp), \
        "m"(eflags), \
        "m"(cs), \
        "m"(thread->registers.eip), \
        "m"(thread), \
        [KMODE] "i"(KERNEL_MODE), \
        [mode] "g"(mode)
        );
}