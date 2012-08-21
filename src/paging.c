#include "paging.h"

void* align(void* addr){
	return (void*)( (unsigned int)addr & (~0xFFF));
}

void map_range(char* str,void* start,void* end){
	//kprintf("MAPPING [%s] %x to %x\n",str,start,end);
	while (start<end){
		map_page(kernel_context,start,start);
		start+=0x1000;
	}
}

void init_paging(){
	paging_enabled = false;
	kernel_context = create_context();
	/*void *start = align(0x00);
	void* end = align(0x10000000);
	map_range(start,end);
	*/
	void* start = gdt_entry_start;
	void* end = gdt_entry_end;
	int j = 0;
	start = align(start);
	end = align(end);
	end+=0x1000;
	map_range("GDT",start,end);
	
	start = (void*)0x100000;
	end =&kernel_end;
	map_range("Kernel", start,end);
	
	start =idt_entry_start-0x1000;
	end  = idt_entry_end;
	start = align(start);
	end = align(end);
	end+=0x1000;
	map_range("IDT",start,end);
	
	start = (kernel_stack-0x10000);
	end =(kernel_stack);
	start = align(start);
	end = align(end);
	end+=0x1000;
	//map_range(start,end);
	
	start = (void*)0xB8000;
	end =(void*)(0xB8000+(25*80*2/0x1000));
	start = align(start);
	end = align(end);
	end+=0x1000;
	map_range("Video",start,end);
	
	start = 0x000;
	end =(void*)(0x400000);
	start = align(start);
	end = align(end);
	map_range("first 4MB",start,end);

	start = 0x400000;
	end =(void*)(0x800000);
	start = align(start);
	end = align(end);
	map_range("second 4MB",start,end);

	heap = (node*)pmm_alloc();
	map_page(kernel_context,(unsigned int*)heap,(unsigned int*)heap);
	activate_context(kernel_context);

    unsigned int cr0;
	__asm__ volatile("mov %%cr0, %0" : "=r" (cr0));
    cr0 |= (1 << 31);
    __asm__ volatile("mov %0, %%cr0" : : "r" (cr0));
	paging_enabled = true;
	
	/*unsigned int* x = (unsigned int*)0x3fcff000;
	kprintf("virt=%x\n",(unsigned int)*x);
	kDebug(true);
	map_page(0x3fcff000,(void*)0x2000,(void*)0x2000);
	kDebug(false);
	*/
	
}

int map_page(context* ctx,void* virt, void* phys) {
	unsigned int page_index = (unsigned int)virt / 0x1000;
    unsigned int pd_index = (unsigned int)page_index / 1024;
    unsigned int pt_index = (unsigned int)page_index % 1024;

    if (kIsDebug()){
		kprintf("page_idx=%d pd_idx=%d pt_idx=%d\n",page_index,pd_index,pt_index);
	}
	unsigned int* page_table;
    int i;

    /* Wir brauchen 4k-Alignment */
    if (((unsigned int)virt & 0xFFF) || ((unsigned int)phys & 0xFFF)) {
        return -1;
    }

    /* Page Table heraussuchen bzw. anlegen */
    if (((unsigned int)ctx->pagedir[pd_index]) & 0x1) {
        /* Page Table ist schon vorhanden */
        page_table = (unsigned int*) (((unsigned int)ctx->pagedir[pd_index]) & ~0xFFF);
		if (kIsDebug())
				kprintf("present pt=%x\n",page_table);
	} else {
        /* Neue Page Table muss angelegt werden */
		page_table = 0x400000+(pd_index+1)*0x1000;
		if (kIsDebug())
			kprintf("not present PT at %x\n",page_table);
		__asm__ volatile("invlpg %0" : : "m" (*(char*)page_table));
		
		if (kIsDebug())  
			kprintf("new pagetable at %x for %x\n",page_table,virt);
		for (i = 0; i < 1024; i++) {
            page_table[i] = 0;
        }
        ctx->pagedir[pd_index] = (unsigned int) page_table | 0x3;
		if (kIsDebug())  
			kprintf("\tNewPT phys=%x pd-entry=%x\n",page_table,ctx->pagedir[pd_index]);
	}
	if (1==2) {
		if (!((unsigned int)page_table & 0x1))
			map_page(kernel_context,page_table,page_table);
	}
    /* Neues Mapping in the Page Table eintragen */
	//if (kIsDebug()) kprintf("\t* entering phys=%x at pt=%x\n",phys,page_table);
	page_table[pt_index] = (unsigned int)phys | 0x3;
    __asm__ volatile("invlpg %0" : : "m" (*(char*)virt));

    return 0;
}

void activate_context(context* ctx) {
	__asm__ volatile("mov %0, %%cr3" : : "r" (ctx->pagedir));
	//kprintf("active context with (phys) PD=%x\n",ctx->pagedir);
}

context* create_context() {
	context* ctx = 0x400000;
    ctx->pagedir = 0x400000+0x1000;
	//kprintf("new context... phys=%x pd=%x\n",ctx,ctx->pagedir);
    for (unsigned int i = 0; i < 1024; i++) {
        ctx->pagedir[i] = 0;
    }

    return ctx;
}
