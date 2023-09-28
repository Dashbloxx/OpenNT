/*
 *  Here we've got a macro that allows us to generate a small wrapper function that the CPU can call in order to alert us
 *  that an exception occured.
 */

.macro EXCEPTION_HANDLER exception_number
    .section .text
    .global wrapper\exception_number

    wrapper\exception_number:
        pusha
        cld
        pushl $\exception_number
        call exception_handler
        popa
        iret
.endm

/*
 *  Here we just place a number following `EXCEPTION_HANDLER` for each exception interrupt that we can handle
 *  (see kernel/exception.c).
 */

EXCEPTION_HANDLER 0
