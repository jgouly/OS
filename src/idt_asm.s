[GLOBAL idt_load]
idt_load:
	mov eax, [esp+4]
	lidt [eax]     
	ret
   
[GLOBAL isr0]
isr0:
	cli                
	push byte 0         
	push byte 0         
	jmp isr_common_stub 
[GLOBAL isr1]
isr1:
	cli                
	push byte 0         
	push 1         
	jmp isr_common_stub 
[GLOBAL isr2]
isr2:
	cli                
	push byte 0         
	push 2         
	jmp isr_common_stub 
[GLOBAL isr3]
isr3:
	cli                
	push byte 0         
	push 3         
	jmp isr_common_stub 
[GLOBAL isr4]
isr4:
	cli                
	push byte 0         
	push 4         
	jmp isr_common_stub 
[GLOBAL isr5]
isr5:
	cli                
	push byte 0         
	push 5        
	jmp isr_common_stub 
[GLOBAL isr6]
isr6:
	cli                
	push byte 0         
	push 6         
	jmp isr_common_stub 
[GLOBAL isr7]
isr7:
	cli                
	push byte 0         
	push 7         
	jmp isr_common_stub 
[GLOBAL isr8]
isr8:
	cli                
	push 8         
	jmp isr_common_stub 
[GLOBAL isr9]
isr9:
	cli                
	push byte 0         
	push 9         
	jmp isr_common_stub 
[GLOBAL isr10]
isr10:
	cli                
	push 10         
	jmp isr_common_stub 
[GLOBAL isr11]
isr11:
	cli                
	push 11         
	jmp isr_common_stub 
[GLOBAL isr12]
isr12:
	cli                
	push 12         
	jmp isr_common_stub 
[GLOBAL isr13]
isr13:
	cli                
	push 13         
	jmp isr_common_stub 
[GLOBAL isr14]
isr14:
	cli                
	push 14         
	jmp isr_common_stub 
[GLOBAL isr15]
isr15:
	cli                
	push byte 0         
	push 15         
	jmp isr_common_stub 
[GLOBAL isr16]
isr16:
	cli                
	push byte 0         
	push 16         
	jmp isr_common_stub 
[GLOBAL isr17]
isr17:
	cli                
	push byte 0         
	push 17         
	jmp isr_common_stub 
[GLOBAL isr18]
isr18:
	cli                
	push byte 0         
	push 18         
	jmp isr_common_stub 
[GLOBAL isr19]
isr19:
	cli                
	push byte 0         
	push 19         
	jmp isr_common_stub 
[GLOBAL isr20]
isr20:
	cli                
	push byte 0         
	push 20         
	jmp isr_common_stub 
[GLOBAL isr21]
isr21:
	cli                
	push byte 0         
	push 21         
	jmp isr_common_stub 
[GLOBAL isr22]
isr22:
	cli                
	push byte 0         
	push 22         
	jmp isr_common_stub 
[GLOBAL isr23]
isr23:
	cli                
	push byte 0         
	push 23         
	jmp isr_common_stub 
[GLOBAL isr24]
isr24:
	cli                
	push byte 0         
	push 24         
	jmp isr_common_stub 
[GLOBAL isr25]
isr25:
	cli                
	push byte 0         
	push 25         
	jmp isr_common_stub 
[GLOBAL isr26]
isr26:
	cli                
	push byte 0         
	push 26         
	jmp isr_common_stub 
[GLOBAL isr27]
isr27:
	cli                
	push byte 0         
	push 27         
	jmp isr_common_stub 
[GLOBAL isr28]
isr28:
	cli                
	push byte 0         
	push 28         
	jmp isr_common_stub 
[GLOBAL isr29]
isr29:
	cli                
	push byte 0         
	push 29         
	jmp isr_common_stub 
[GLOBAL isr30]
isr30:
	cli                
	push byte 0         
	push 30         
	jmp isr_common_stub 
[GLOBAL isr31]
isr31:
	cli                
	push byte 0         
	push 31         
	jmp isr_common_stub 

[GLOBAL irq1]
irq1:
    cli
    push byte 0
    push 33
    jmp irq_common_stub	
[GLOBAL irq2]
irq2:
    cli
    push byte 0
    push 34
    jmp irq_common_stub	
[GLOBAL irq3]
irq3:
    cli
    push byte 0
    push 35
    jmp irq_common_stub	
[GLOBAL irq4]
irq4:
    cli
    push byte 0
    push 36
    jmp irq_common_stub	
[GLOBAL irq5]
irq5:
    cli
    push byte 0
    push 37
    jmp irq_common_stub	
[GLOBAL irq6]
irq6:
    cli
    push byte 0
    push 38
    jmp irq_common_stub	
[GLOBAL irq7]
irq7:
    cli
    push byte 0
    push 39
    jmp irq_common_stub	
[GLOBAL irq8]
irq8:
    cli
    push byte 0
    push 40
    jmp irq_common_stub	
[GLOBAL irq9]
irq9:
    cli
    push byte 0
    push 41
    jmp irq_common_stub	
[GLOBAL irq10]
irq10:
    cli
    push byte 0
    push 42
    jmp irq_common_stub	
[GLOBAL irq11]
irq11:
    cli
    push byte 0
    push 43
    jmp irq_common_stub	
[GLOBAL irq12]
irq12:
    cli
    push byte 0
    push 44
    jmp irq_common_stub	
[GLOBAL irq13]
irq13:
    cli
    push byte 0
    push 45
    jmp irq_common_stub	
[GLOBAL irq14]
irq14:
    cli
    push byte 0
    push 46
    jmp irq_common_stub	
[GLOBAL irq15]
irq15:
    cli
    push byte 0
    push 47
    jmp irq_common_stub	

[GLOBAL isr128]
isr128:
	cli     
	push byte 0 
	push 80h
	jmp isr_common_stub	

		
[EXTERN isr_handler]
isr_common_stub:
   pusha              

   mov ax, ds        
   push eax      
   
   mov ax, 0x10
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call isr_handler

   pop eax       
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   popa         
   add esp, 8  
   sti
   iret     
   
[EXTERN irq_handler]
irq_common_stub:
 pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds               ; Lower 16-bits of eax = ds.
    push eax                 ; save the data segment descriptor

    mov ax, 0x10  ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop ebx        ; reload the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                     ; Pops edi,esi,ebp...
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    sti
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
	
[EXTERN task_scheduler]
[GLOBAL irq0]
irq0:
                pusha           ; push general registers onto stack
                push ds         ; push ds onto stack
                push es         ; push es
                push fs         ; push fs
                push gs         ; push gs
                
                mov eax, 0x10   ; save selector
                mov ds, eax             
                mov es, eax
                mov fs, eax
                mov gs, eax             
                
                mov eax, esp    ; stack => eax
                push eax        ; push eax (esp)

                call task_scheduler      ; sched(eax) returns stack of next task
                mov esp, eax    ; return value => stack
                
                mov al, 0x20    ; ack IRQ
                out 0x20, al    
                
                pop gs          ; pop gs off task stack
                pop fs          ; pop fs
                pop es          ; pop es
                pop ds          ; pop ds
                popa            ; pop general registers

                iret            ; interrupt return
	
[GLOBAL read_eip]
read_eip:
    pop eax                     ; Get the return address
    jmp eax                     ; Return. Can't use RET because return
                                ; address popped off the stack. 
