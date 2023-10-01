#include <stdint.h>

#include "pic.h"
#include "port.h"

void pic_sendeoi(unsigned char interrupt)
{
	if(interrupt >= 8)
		outb(PIC2_COMMAND, PIC_EOI);
 
	outb(PIC1_COMMAND, PIC_EOI);
}

void pic_remap(int offset1, int offset2)
{
	unsigned char a1, a2;
 
	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);
	io_wait();
	outb(PIC2_DATA, offset2);
	io_wait();
	outb(PIC1_DATA, 4);
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
 
	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);
}

void irq_set_mask(unsigned char irq_line)
{
    uint16_t port;
    uint8_t value;
 
    if(irq_line < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        irq_line -= 8;
    }
    value = inb(port) | (1 << irq_line);
    outb(port, value);        
}
 
void irq_clear_mask(unsigned char irq_line)
{
    uint16_t port;
    uint8_t value;
 
    if(irq_line < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        irq_line -= 8;
    }
    value = inb(port) & ~(1 << irq_line);
    outb(port, value);        
}