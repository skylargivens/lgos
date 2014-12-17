CC=gcc
KERNEL=kernel-001
CFLAGS=-m32 -ffreestanding -std=c99 -c
LDFLAGS=-m elf_i386
BUILDDIR=build/
CSOURCES=$(wildcard *.c)
COBJS=$(CSOURCES:.c=.o)
COBJSFULL=$(addprefix $(BUILDDIR), $(CSOURCES:.c=.o))

all: build_dir $(KERNEL)

build_dir:
	mkdir -p build

kernel_asm.o: kernel.asm
	nasm -f elf32 kernel.asm -o $(BUILDDIR)kernel_asm.o

.c.o:
	$(CC) $(CFLAGS) $< -o $(BUILDDIR)$@ 

$(KERNEL): kernel_asm.o $(COBJS)
	ld $(LDFLAGS) -T link.ld -o $(BUILDDIR)$(KERNEL) $(BUILDDIR)kernel_asm.o $(COBJSFULL)

clean:
	rm -rf build/

run:
	qemu-system-i386 -kernel $(BUILDDIR)$(KERNEL)
