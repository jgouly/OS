#ifndef PMM_H
#define PMM_H

#include "kio.h"

static int debug = 1;
unsigned long long memUsed;

struct multiboot_mmap_entry {
	unsigned int size;
	unsigned long long addr;
	unsigned long long len;
	unsigned int type;
} __attribute__((packed));
typedef struct multiboot_mmap_entry multiboot_mmap_entry_t;
 
/* The Multiboot header. */
     typedef struct multiboot_header
     {
       unsigned long magic;
       unsigned long flags;
       unsigned long checksum;
       unsigned long header_addr;
       unsigned long load_addr;
       unsigned long load_end_addr;
       unsigned long bss_end_addr;
       unsigned long entry_addr;
     } multiboot_header_t;
     
     /* The symbol table for a.out. */
     typedef struct aout_symbol_table
     {
       unsigned long tabsize;
       unsigned long strsize;
       unsigned long addr;
       unsigned long reserved;
     } aout_symbol_table_t;
     
     /* The section header table for ELF. */
     typedef struct elf_section_header_table
     {
       unsigned long num;
       unsigned long size;
       unsigned long addr;
       unsigned long shndx;
     } elf_section_header_table_t;

typedef struct multiboot_info
{
unsigned long flags;
unsigned long mem_lower;
unsigned long mem_upper;
unsigned long boot_device;
unsigned long cmdline;
unsigned long mods_count;
unsigned long mods_addr;
union
{
aout_symbol_table_t aout_sym;
elf_section_header_table_t elf_sec;
} u;
unsigned long mmap_length;
unsigned long mmap_addr;
} multiboot_info_t;


unsigned int InitAmountOfRam(multiboot_info_t* mbd);
void pmm_free(void* addr);
void pmm_mark_used(void* addr);
void init_pmm(void* mbd);
void* pmm_alloc();
bool pmm_check(void* addr);
unsigned int pmm_count();

#endif
