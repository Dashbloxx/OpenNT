.macro ISR_NO_ERR num
	.global interrupt\num
	interrupt\num:
		cli
		push $0
		push $\num
		jmp isr_common
.endm

.macro ISR_ERR num
	.global interrupt\num
	interrupt\num:
		cli
		push $\num
		jmp isr_common
.endm

.macro IRQ num
	.global interrupt\num
	interrupt\num:
		cli
		push $0
		push $\num
		jmp irq_common
.endm

ISR_NO_ERR 0
ISR_NO_ERR 1
ISR_NO_ERR 2
ISR_NO_ERR 3
ISR_NO_ERR 4
ISR_NO_ERR 5
ISR_NO_ERR 6
ISR_NO_ERR 7
ISR_ERR 8
ISR_NO_ERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NO_ERR 15
ISR_NO_ERR 16
ISR_NO_ERR 17
ISR_NO_ERR 18
ISR_NO_ERR 19
ISR_NO_ERR 20
ISR_NO_ERR 21
ISR_NO_ERR 22
ISR_NO_ERR 23
ISR_NO_ERR 24
ISR_NO_ERR 25
ISR_NO_ERR 26
ISR_NO_ERR 27
ISR_NO_ERR 28
ISR_NO_ERR 29
ISR_NO_ERR 30
ISR_NO_ERR 31

IRQ 32
IRQ 33
IRQ 34
IRQ 35
IRQ 36
IRQ 37
IRQ 38
IRQ 39
IRQ 40
IRQ 41
IRQ 42
IRQ 43
IRQ 44
IRQ 45
IRQ 46
IRQ 47

isr_common:
	pusha
	mov	%ds, %ax
	pushl %eax

	mov	$0x10, %ax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs

	call handle_isr

	popl %eax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs

	popa
	addl $8, %esp
	sti
	iret

irq_common:
	pusha
	mov	%ds, %ax
	pushl %eax

	mov	$0x10, %ax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs

	call handle_irq

	popl %eax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs

	popa
	addl $8, %esp
	sti
	iret
