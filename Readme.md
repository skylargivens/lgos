# Looking Glass OS
I'm building a simple 32-bit x86 kernel as an exercise. The goal is to improve my C skills and learn more about system internals.

## Prerequisites
- qemu-system-i386 (QEMU)
- gcc
- ld
- nasm

## Building
<aside class="warning">
**OS X Users** - If you're running the standard Apple dev tools, you won't be able to build this project. Look into [building a cross-compiler](http://wiki.osdev.org/GCC_Cross-Compiler) or set up a Linux VM.
</aside>

Simply run make from within the project directory:
```
make
```
If all goes well, there should be a file named kernel-001 in the /build directory.
## Running
Assuming you have qemu installed, run:
```
make run
```
You should see the welcome message displayed in the QEMU window.

For the more adventurous, try booting your kernel with [GRUB](http://wiki.osdev.org/GRUB)

## Todo
- Fill me with helpful information
- Move video functions to separate file
- Handle keyboard input
- 64 bits?
