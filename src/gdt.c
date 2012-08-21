#include "gdt.h"

void gdt_set_gate(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran) {
	gdt_entries[num].base_low    = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high   = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low   = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access      = access;
} 

/*void write_tss(int num, unsigned short ss0, unsigned int esp0) {
	unsigned int base = (unsigned int) &tss_entry;
	unsigned int limit = base + sizeof(tss_entry);

	gdt_set_gate(num, base, limit, 0xE9, 0x00);

	memset(&tss_entry, 0, sizeof(tss_entry));

	tss_entry.ss0  = ss0;
	tss_entry.esp0 = esp0; 

	tss_entry.cs   = 0x0b;
	tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13;
} */


void init_gdt(){
	gdtp.limit = (sizeof(gdt_entry_t) * 6) - 1;
	gdtp.base  = (unsigned int)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

	//write_tss(5, 0x10, 0x0);
	
	unsigned int* start = (unsigned int*)&gdt_entries;
	unsigned int* end = (unsigned int*)(&gdt_entries+ (sizeof(gdt_entry_t) * 6) - 1);
	gdt_entry_start = start;
	gdt_entry_end = end;
	
	gdt_flush((unsigned int)&gdtp);
	
//	tss_flush();
}
