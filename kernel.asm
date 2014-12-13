;; Looking Glass OS bootstrapper
;; This will be loaded at 0x100000 and called by GRUB

bits 32             ; Tell NASM that we want 32-bit code
section .text

; Multiboot header to appease the GRUB gods
  align 4
  dd 0x1BADB002               ; Magic number!
  dd 0x00                     ; Flags
  dd - (0x1BADB002 + 0x00)    ; Checksum, should add up to zero

global start        ; Tell NASM to make "start" global so our linker can see it
extern kmain        ; C kernel entrypoint

start:
  cli               ; Disable interrupts completely
  call kmain        ; Call our C code. Let's get this party started!
  hlt               ; Halt the CPU
