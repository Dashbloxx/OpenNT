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
EXCEPTION_HANDLER 1
EXCEPTION_HANDLER 2
EXCEPTION_HANDLER 3
EXCEPTION_HANDLER 4
EXCEPTION_HANDLER 5
EXCEPTION_HANDLER 6
EXCEPTION_HANDLER 7
EXCEPTION_HANDLER 8
EXCEPTION_HANDLER 9
EXCEPTION_HANDLER 10
EXCEPTION_HANDLER 11
EXCEPTION_HANDLER 12
EXCEPTION_HANDLER 13
EXCEPTION_HANDLER 14
EXCEPTION_HANDLER 15
EXCEPTION_HANDLER 16
EXCEPTION_HANDLER 17
EXCEPTION_HANDLER 18
EXCEPTION_HANDLER 19
EXCEPTION_HANDLER 20
EXCEPTION_HANDLER 21
EXCEPTION_HANDLER 22
EXCEPTION_HANDLER 23
EXCEPTION_HANDLER 24
EXCEPTION_HANDLER 25
EXCEPTION_HANDLER 26
EXCEPTION_HANDLER 27
EXCEPTION_HANDLER 28
EXCEPTION_HANDLER 29
EXCEPTION_HANDLER 30
EXCEPTION_HANDLER 31