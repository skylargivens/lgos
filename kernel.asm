;; Looking Glass OS bootstrapper
;; This will be loaded at 0x100000 and called by GRUB

bits 32               ; Tell NASM that we want 32-bit code
section .text

; Multiboot header to appease the GRUB gods
align 4
dd 0x1BADB002               ; Magic number!
dd 0x00                     ; Flags
dd - (0x1BADB002 + 0x00)    ; Checksum, should add up to zero

global start          ; Tell NASM to make start visible to linker
global read_port
global write_port
global load_idt
global keyboard_interrupt_handler
extern kmain          ; C kernel entrypoint
extern keyboard_handler

start:                ; This is the main entrypoint to our kernel. The
                      ; bootloader (GRUB or QEMU) calls this once the
                      ; kernel has been loaded into memory.

  cli                 ; Disable interrupts completely
  call kmain          ; Call our C code. Let's get this party started!
  hlt                 ; Halt the CPU

; Read from an IO port
; Argument: Port #
read_port:
  mov edx, [esp + 4]  ; Copy argument (IO port #) from stack to edx register.
                      ; Before a C function calls our assembly code, it pushes
                      ; the function call's arguments to the stack.

  in al, dx           ; Read value on the IO port into AL. Function return
                      ; values are received through the EAX register. AL
                      ; is the lower 8 bits of EAX

  ret                 ; Pass control back to calling C code

; Write value to an IO port
; Argument 1: Port #
; Argument 2: Value
write_port:
  mov edx, [esp + 4]  ; Copy IO port # from stack into edx register
  mov al, [esp + 8]   ; Copy value to write into al
  out dx, al          ; Output value on port
  ret                 ; Return to C

; Load our newly-created IDT
; Argument: Start address of IDT
load_idt:
  mov edx, [esp + 4]
  lidt [edx]
  sti                 ; Turn interrupts back on
  ret

; Handle a keyboard interrupt by calling our C function
keyboard_interrupt_handler:
  call keyboard_handler
  iretd
