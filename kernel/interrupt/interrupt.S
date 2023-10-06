.extern exception_handler
.extern handle_irq

.macro ISR_ERROR_CODE number
    .global isr\number
    
    isr\number:
        pushl $\number
        jmp handle_isr_common
.endm

.macro ISR_NO_ERROR_CODE number
    .global isr\number

    isr\number:
        pushl $0
        pushl $\number
        jmp handle_isr_common
.endm

.macro IRQ number vector
    .global irq\number

    irq\number:
        pushl $0
        pushl $\vector
        jmp handle_irq_common
.endm

.macro STORE_REGISTERS
    pushl %eax
    pushl %ecx
    pushl %edx
    pushl %ebx
    pushl %esp
    pushl %ebp
    pushl %esi
    pushl %edi

    pushl %ebx
    movw $0x10, %bx
    movw %bx, %ds
    movw %bx, %es
    movw %bx, %fs
    movw %bx, %gs
    popl %ebx
.endm

.macro RESTORE_REGISTERS
    popl %edi
    popl %esi
    popl %ebp
    popl %ebx
    popl %edx
    popl %ecx
    popl %eax

    popw %gs
    popw %fs
    popw %es
    popw %ds
    popal
.endm

IRQ 0, 32

ISR_NO_ERROR_CODE 0
ISR_NO_ERROR_CODE 1
ISR_NO_ERROR_CODE 2
ISR_NO_ERROR_CODE 3
ISR_NO_ERROR_CODE 4
ISR_NO_ERROR_CODE 5
ISR_NO_ERROR_CODE 6
ISR_NO_ERROR_CODE 7
ISR_ERROR_CODE 8
ISR_NO_ERROR_CODE 9
ISR_ERROR_CODE 10
ISR_ERROR_CODE 11
ISR_ERROR_CODE 12
ISR_ERROR_CODE 13
ISR_ERROR_CODE 14
ISR_NO_ERROR_CODE 15
ISR_NO_ERROR_CODE 16
ISR_ERROR_CODE 17
ISR_NO_ERROR_CODE 18
ISR_NO_ERROR_CODE 19
ISR_NO_ERROR_CODE 20
ISR_NO_ERROR_CODE 21
ISR_NO_ERROR_CODE 22
ISR_NO_ERROR_CODE 23
ISR_NO_ERROR_CODE 24
ISR_NO_ERROR_CODE 25
ISR_NO_ERROR_CODE 26
ISR_NO_ERROR_CODE 27
ISR_NO_ERROR_CODE 28
ISR_NO_ERROR_CODE 29
ISR_ERROR_CODE 30
ISR_NO_ERROR_CODE 31

handle_isr_common:
    STORE_REGISTERS
    call exception_handler
    RESTORE_REGISTERS
    addl $8, %esp
    iret

handle_irq_common:
    STORE_REGISTERS
    call handle_irq
    RESTORE_REGISTERS
    addl $8, %esp
    iret
