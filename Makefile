CC=gcc
KERNEL=kernel-001
CFLAGS=-m32 -ffreestanding -std=c99
LDFLAGS=-m elf_i386
BUILDDIR=build/

all: build_dir $(KERNEL)

build_dir:
	mkdir -p build

kernel_asm.o: kernel.asm
	nasm -f elf32 kernel.asm -o $(BUILDDIR)kernel_asm.o

kernel_c.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o $(BUILDDIR)kernel_c.o

screen.o: screen.c
	$(CC) $(CFLAGS) -c screen.c -o $(BUILDDIR)screen.o

$(KERNEL): kernel_c.o kernel_asm.o link.ld screen.o
	ld $(LDFLAGS) -T link.ld -o $(BUILDDIR)$(KERNEL) $(BUILDDIR)kernel_asm.o $(BUILDDIR)kernel_c.o $(BUILDDIR)screen.o

clean:
	rm -rf build/

run:
	qemu-system-i386 -kernel $(BUILDDIR)$(KERNEL)
