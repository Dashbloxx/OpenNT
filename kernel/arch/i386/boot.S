/*
 *  Let's create a basic struct where the bootloader will set the multiboot data here.
 *  The bootloader will find this by the magic number, 0x1BADB002!
 */
.section .multiboot, "aw"
    .align 4
    .long 0x1BADB002
    .long (1<<0 | 1<<1 | 1<<2)
    .long -(0x1BADB002 + (1<<0 | 1<<1 | 1<<2))
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000
    .long 0x00000000
    .long 1024
    .long 768
    .long 32

.section .bss, "aw"
    .align 16
stack_bottom:
    .space 16384 /* Let's create the stack, and set it to 16KiB in size. */
stack_top:

.global _start
.extern main

.section .text

_start:
    /* Let's tell the CPU where our stack is. We do this by setting the ESP register, which it's purpose is to store a pointer to the stack. */
    movl $stack_top, %esp

    /* Let's send the multiboot header structure to our kernel's main function! */
    pushl %ebx

    /* And finally, let's call the kernel's main function. */
    call main

    /* Clear all interrupts, and halt the CPU. The end of the kernel's main function should keep a loop that already does this for us. */
    cli
    hlt