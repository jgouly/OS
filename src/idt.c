#include "idt.h"
#include "kio.h"
#include "util.h"
#include "paging.h"

void PANIC(registers_t regs){
	unsigned int faulting_address;
	__asm__ volatile("mov %%cr2, %0" : "=r" (faulting_address));

	unsigned int cr2;
	__asm__ volatile("mov %%cr2, %0" : "=b" (cr2));
	int present   = (regs.err_code & 0x1); // Page not present
	int rw = regs.err_code & 0x2;           // Write operation?
	int us = regs.err_code & 0x4;           // Processor was in user-mode?
	int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
	int id = regs.err_code & 0x10;          // Caused by an instruction fetch?

   	switch(regs.number){
		case 14: {
					__asm__ volatile("cli");
					kprintf("Page Fault (");
					if (present) 
						kprintf("present; ");
					else
						kprintf("not-present; ");
					if (rw) 
						kprintf("read-only; ");
					if (us) 
						kprintf("user-mode; ");
					if (reserved) 
						kprintf("reserved; ");
					kprintf("\b\b) at %x %x\n",&faulting_address,faulting_address);
					kprintf("cr2: %x\n",cr2);
					
					
				}
				while(1){}
				break;
		case 13: kprintf("GPF  ");
				while(1){}
				break;
		default:	kprintf("faulting %d\n",regs.number);
				break;
	}
	
}

void isr_handler(registers_t reg) {
	int int_no = reg.number;// & 0xFF;
	kprintf("ISR\nNr: %d\n",int_no);
	switch(int_no ){
		case 14:	/* Page Fault */
					PANIC(reg);
					kprintf("Page fault\n");
					break;
		case 0x80:  kprintf("SYSCALL\n");
				break;
		default: PANIC(reg);
					break;
	}
} 

void irq_handler(registers_t reg) {
	if (reg.number >= 40)
		outb(0xA0, 0x20);
	outb(0x20, 0x20);
	if (reg.number == 33){
		unsigned char scancode = inb(0x60);
		KbKey c;
		c.c = scancodeToChar(scancode);
		c.code = scancodeToCode(scancode);
		//keyboardHandler(scancode & 0x80,c);
	}
} 

void idt_set_gate(unsigned char num, unsigned int base, unsigned short sel, unsigned char flags) {
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags =flags  | 0x60;
}

void init_idt() {
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int)&idt;

   // memset(&idt, 0, sizeof(struct idt_entry) * 256);

	 outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
  
	idt_set_gate(0,(unsigned int)isr0,0x08,0x8E);
	idt_set_gate(1,(unsigned int)isr1,0x08,0x8E);
	idt_set_gate(2,(unsigned int)isr2,0x08,0x8E);
	idt_set_gate(3,(unsigned int)isr3,0x08,0x8E);
	idt_set_gate(4,(unsigned int)isr4,0x08,0x8E);
	idt_set_gate(5,(unsigned int)isr5,0x08,0x8E);
	idt_set_gate(6,(unsigned int)isr6,0x08,0x8E);
	idt_set_gate(7,(unsigned int)isr7,0x08,0x8E);
	idt_set_gate(8,(unsigned int)isr8,0x08,0x8E);
	idt_set_gate(9,(unsigned int)isr9,0x08,0x8E);
	idt_set_gate(10,(unsigned int)isr10,0x08,0x8E);
	idt_set_gate(11,(unsigned int)isr11,0x08,0x8E);
	idt_set_gate(12,(unsigned int)isr12,0x08,0x8E);
	idt_set_gate(13,(unsigned int)isr13,0x08,0x8E);
	idt_set_gate(14,(unsigned int)isr14,0x08,0x8E);
	idt_set_gate(15,(unsigned int)isr15,0x08,0x8E);
	idt_set_gate(16,(unsigned int)isr16,0x08,0x8E);
	idt_set_gate(17,(unsigned int)isr17,0x08,0x8E);
	idt_set_gate(18,(unsigned int)isr18,0x08,0x8E);
	idt_set_gate(19,(unsigned int)isr19,0x08,0x8E);
	idt_set_gate(20,(unsigned int)isr20,0x08,0x8E);
	idt_set_gate(21,(unsigned int)isr21,0x08,0x8E);
	idt_set_gate(22,(unsigned int)isr22,0x08,0x8E);
	idt_set_gate(23,(unsigned int)isr23,0x08,0x8E);
	idt_set_gate(24,(unsigned int)isr24,0x08,0x8E);
	idt_set_gate(25,(unsigned int)isr25,0x08,0x8E);
	idt_set_gate(26,(unsigned int)isr26,0x08,0x8E);
	idt_set_gate(27,(unsigned int)isr27,0x08,0x8E);
	idt_set_gate(28,(unsigned int)isr28,0x08,0x8E);
	idt_set_gate(29,(unsigned int)isr29,0x08,0x8E);
	idt_set_gate(30,(unsigned int)isr30,0x08,0x8E);
	idt_set_gate(31,(unsigned int)isr31,0x08,0x8E);

	idt_set_gate(128,(unsigned int)isr128,0x08,0x8E);

	idt_set_gate(32,(unsigned int)irq0, 0x08, 0x8E);
	idt_set_gate(33,(unsigned int)irq1, 0x08, 0x8E);
	idt_set_gate(34,(unsigned int)irq2, 0x08, 0x8E);
	idt_set_gate(35,(unsigned int)irq3, 0x08, 0x8E);
	idt_set_gate(36,(unsigned int)irq4, 0x08, 0x8E);
	idt_set_gate(37,(unsigned int)irq5, 0x08, 0x8E);
	idt_set_gate(38,(unsigned int)irq6, 0x08, 0x8E);
	idt_set_gate(39,(unsigned int)irq7, 0x08, 0x8E);
	idt_set_gate(40,(unsigned int)irq8, 0x08, 0x8E);
	idt_set_gate(41,(unsigned int)irq9, 0x08, 0x8E);
	idt_set_gate(42,(unsigned int)irq10, 0x08, 0x8E);
	idt_set_gate(43,(unsigned int)irq11, 0x08, 0x8E);
	idt_set_gate(44,(unsigned int)irq12, 0x08, 0x8E);
	idt_set_gate(45,(unsigned int)irq13, 0x08, 0x8E);
	idt_set_gate(46,(unsigned int)irq14, 0x08, 0x8E);
	idt_set_gate(47,(unsigned int)irq15, 0x08, 0x8E);
	
	
    	void* start = idt;
	void* end = (start + (( sizeof(struct idt_entry)*256)-1));
	idt_entry_start = start;
	idt_entry_end = end;
	idt_load((unsigned int)&idtp);
}
