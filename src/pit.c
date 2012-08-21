#include "pit.h"

void init_pit(){
	unsigned int divisor = 1193180/frequency;

	outb(0x43,0x36);

	unsigned char l = (unsigned char)(divisor & 0xFF);
	unsigned char h = (unsigned char)((divisor>>8) & 0xFF );

	outb(0x40,l);
	outb(0x40,h);
}