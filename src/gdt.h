#ifndef GDT_H
#define GDT_H

#include "kio.h"

#define GDT_ENTRIES 6


struct gdt_entry_struct {
   unsigned short limit_low;        
   unsigned short base_low;       
   unsigned char  base_middle;        
   unsigned char  access;              
   unsigned char  granularity;
   unsigned char  base_high;         
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t; 
static gdt_entry_t gdt_entries[GDT_ENTRIES];

void* gdt_entry_start;
void* gdt_entry_end;

extern void gdt_flush(unsigned int);
void init_gdt();
 
struct gdt_ptr_struct {
   unsigned short limit;    
   unsigned int base;
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t; 

static gdt_ptr_t gdtp;

#endif
