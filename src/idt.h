#ifndef IDT_H
#define IDT_H

//#include "tasks.h"

typedef struct registers {
	unsigned int ds;              
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int number, err_code;   
	unsigned int eip, cs, eflags, useresp, ss;
} registers_t; 

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;   
    unsigned char always0;
    unsigned char flags; 
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void* idt_entry_start;
void* idt_entry_end;

void PANIC(registers_t regs);
extern void idt_load(unsigned int);
void init_idt();

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void isr128();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
#endif
