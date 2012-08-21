#include "pmm.h"


#define BITMAP_SIZE 32768
static unsigned int bitmap[BITMAP_SIZE];

unsigned int InitAmountOfRam(multiboot_info_t* mbd){
	ramAmount = mbd->mem_lower+mbd->mem_upper;
	return ramAmount;
}

void pmm_test(){
	for (unsigned int i = 0; i < BITMAP_SIZE; i++) {
		for (unsigned int off = 0;off < 32; off++) {
			if (bitmap[i] & (1 << off)) {
				kprintf(".");
			}
			else
			kprintf("X");
		}
		break;
	}
	kprintf("\n");
}

void init_pmm(void* mbd){
	multiboot_info_t* mb_info = (multiboot_info_t*)mbd;
	multiboot_mmap_entry_t* mmap = (multiboot_mmap_entry_t*)mb_info->mmap_addr;
	multiboot_mmap_entry_t* mmap_end = (void*) ((unsigned int*) mb_info->mmap_addr + mb_info->mmap_length);

    /* Per Default ist erst einmal alles reserviert */
    memset(bitmap, 0, sizeof(bitmap));

    /*
     * Nur, was die BIOS-Memory-Map als frei bezeichnet, wird wieder als frei
     * markiert
     */
	while (mmap < mmap_end) {
        if (mmap->type == 1) {
            /* Der Speicherbereich ist frei, entsprechend markieren */
            unsigned int addr = mmap->addr;
            unsigned int end_addr = (unsigned char*)addr + mmap->len;

            while (addr < end_addr) {
				pmm_free((void*) addr);
                addr += 0x1000;
            }
        }
        mmap++;
    }
	
    extern const void kernel_start;
    extern const void kernel_end;
    unsigned int addr = (unsigned int) &kernel_start;
    while (addr < (unsigned int*) &kernel_end) {
        pmm_mark_used((void*) addr);
        addr += 0x1000;
    }
	
	addr = (unsigned int)0x00;
	unsigned int addr_end = (unsigned int)0x800000;
	while (addr < addr_end) {
		pmm_mark_used((void*) addr);
		addr += 0x1000;
	}
}

bool pmm_check(void* addr){
	unsigned int index = (unsigned int) addr / 4096;
	unsigned int idx = (unsigned int)index/32;
	unsigned int offset = (unsigned int)index%32;
	return (bitmap[idx] & (1 << offset));	//true =free .. .used block = false
}

void pmm_free(void* addr){
	unsigned int index = (((unsigned int)addr) / 4096);
	bitmap[index / 32] |= (1 << (index % 32));
}

void pmm_mark_used(void* addr){
	unsigned int index =  (((unsigned int)addr) / 4096);
	bitmap[index / 32] &= ~(1 << ((unsigned int)index % 32));
}

unsigned int pmm_count(){
	unsigned int free = 0;
	for(unsigned int i = 0; i < BITMAP_SIZE/32;i++){
		for(unsigned int off = 0;off<32;off++){
			if (bitmap[i] & (1 << off)) {
				free++;
			}
		}
	}
	return free;
}

void* pmm_alloc(){
	int i, j;
	for (i = 0; i < BITMAP_SIZE; i++) {
        if (bitmap[i] != 0) {

            /* Jetzt muessen wir nur noch das gesetzte Bit finden */
            for (j = 0; j < 32; j++) {
				
                if (bitmap[i] & (1 << j)) {
                    bitmap[i] &= ~(1 << j);
					return (void*)( (i * 32 + j) * 4096);
                }
            }
        }
    }

    /* Scheint wohl nichts frei zu sein... */
    return NULL;
}
