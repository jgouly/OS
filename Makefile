SOURCES=src/boot.o src/main.o src/kio.o src/time.o src/gdt.o src/gdt_asm.o
SOURCES+=src/idt.o src/idt_asm.o src/pit.o src/util.o src/paging.o src/pmm.o src/vmm.o src/tasks.o
CFLAGS=-std=c99 -m32 -nostdlib -fno-builtin -nostartfiles -nodefaultlibs
LDFLAGS=-Tsrc/link.ld -melf_i386
ASFLAGS=-felf
CC=i586-elf-gcc
LD=i586-elf-ld

all: $(SOURCES) link

%.c:+
	$(CC) $(CFLAGS) -o $@ $<

link:
	$(LD) $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

clean:
	rm -f *.o

install:
	cp kernel A:\boot\kernel
