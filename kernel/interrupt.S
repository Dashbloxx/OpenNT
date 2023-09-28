/*
 *  Here we define wrapper functions that later call the actual interrpt handler, since
 *  making them in plain C doesn't exactly work, and causes corruption.
 */

.section .text
.global wrapper0

wrapper0:
    pusha
    cld
    call interrupt0
    popa
    iret
