#include <stdbool.h>

#include "thread.h"
#include "../drivers/interrupt/interrupt.h"

bool is_threading_initialized = false;

/*
 *  The kernel thread is the first thread, which is pointed to by the last
 *  thread.
 */
thread_t kernel_thread;
thread_t * current_thread;

void context_switch(thread_t * from, thread_t * to)
{
    DISABLE_INTERRUPTS;

    // Save the current thread's context
    asm volatile(
        "pushf\n\t"           // Push flags register
        "pusha\n\t"           // Push general-purpose registers
        "movl $1f, %0\n\t"    // Save the current EIP in the 'from' thread
        "mov %%esp, %1\n\t"   // Save ESP
        "mov %%ebp, %2\n\t"   // Save EBP"
        : "=m" (from->registers.eip), "=m" (from->registers.esp), "=m" (from->registers.ebp)
        :
        : "memory"
    );

    // Load the next thread's context
    asm volatile(
        "mov %0, %%esp\n\t"   // Load ESP
        "mov %1, %%ebp\n\t"   // Load EBP"
        "jmp *%2\n\t"         // Jump to the new EIP
        "1:\n\t"              // Label for the current EIP
        "popa\n\t"            // Pop general-purpose registers
        "popf\n\t"            // Pop flags register
        :
        : "m" (to->registers.esp), "m" (to->registers.ebp), "m" (to->registers.eip)
        : "memory"
    );

    ENABLE_INTERRUPTS;
}

void thread_initialize()
{
    DISABLE_INTERRUPTS;

    is_threading_initialized = true;

    asm volatile(
        "movl %%esp, %0\n\t"
        "movl %%ebp, %1\n\t"
        "call 1f\n"
        "1: pop %2\n"
        : "=m" (kernel_thread.registers.esp), "=m" (kernel_thread.registers.ebp), "=m" (kernel_thread.registers.eip)
    );

    kernel_thread.next_thread = &kernel_thread;
    current_thread = &kernel_thread;

    ENABLE_INTERRUPTS;
}