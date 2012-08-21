global loader                        
 
extern kmain                        
global kernel_stack

MODULEALIGN 	equ  	1<<0                
MEMINFO    		equ  	1<<1                  
FLAGS      		equ  	MODULEALIGN | MEMINFO 
MAGIC       		equ    	0x1BADB002        
CHECKSUM    		equ 		-(MAGIC + FLAGS)       
   
STACKSIZE equ 0x4000                    ; 16k.
kernel_stack dd 0
 
[EXTERN bss]
[EXTERN kernel_end]
 
mboot:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	
	dd mboot 
	dd bss
	dd kernel_end
	dd loader
  
loader:
	mov  eax, kernel_end
	add 	eax, STACKSIZE   
	mov [kernel_stack], eax
	mov esp,eax
	push ebx                           

	cli
	call kmain                        

	hlt                                
               
	
