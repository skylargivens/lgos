CC=gcc
KERNEL=kernel-1200
CFLAGS=-m32
LDFLAGS=-m elf_i386

all: kernel

kernel: $(KERNEL)

kernel_asm.o: kernel.asm
	nasm -f elf32 kernel.asm -o kernel_asm.o

kernel_c.o: kernel.c
	$(CC) (CFLAGS) -c kernel.c -o kernel_c.o

$(KERNEL): kernel_asm.o kernel_c.o link.ld
	ld $(LDFLAGS) -T link.ld -o kernel-1200 kernel_asm.o kernel_c.o

clean:
	rm -rf *.o kernel-1200
