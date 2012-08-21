#ifndef COMMON_H
#define COMMON_H


static unsigned char *videoram = (unsigned char *) 0xb8000;
static char command[1024];
static int command_offset;

typedef enum {false=0,true} bool;

typedef char *va_list;
#define _INTSIZEOF(n)    ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
#define va_start(ap, v)  (ap = (va_list) &v + _INTSIZEOF(v))
#define va_arg(ap, t)    (*(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)))
#define va_end(ap)       (ap = (va_list) 0)

#define NULL 0

static void outb(unsigned short port, unsigned char value) {
    __asm__ volatile ("outb %1, %0" : : "Nd" (port), "a" (value));
}

static unsigned char inb(unsigned short port) {
   unsigned char ret;
   __asm__ volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

static unsigned short inw(unsigned short port) {
   unsigned short ret;
   __asm__ volatile("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

static void skprintf(char* str, char* x, ...){
	int i = 0;
	while (x[i]!='\0')
	str[i]=x[i++];
}

static void memset(void* addr, int value, unsigned long length){
	char *d = (char*)addr;
	while(length--){
		*d++=value;
	}
}

#endif
