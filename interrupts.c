#include "interrupts.h"
#include "keyboard.h"

#define IDT_SIZE 256

/**
 * Structure for a single entry in the Interrupt Descriptor Table
 */
typedef struct IDT_entry {
    unsigned short int offset_low;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_high;
} IDT_entry;

struct IDT_entry IDT[IDT_SIZE];

/**
 * Set up the data structure for the Interrupt Data Table and initialize the
 * two Programmable Interrupt Controllers.
 * 
 * The PICs are responsible for triggering the appropriate handler function when
 * they receive a signal on one of their inputs. Interrupts can be triggered by
 * software or hardware, including the keyboard. We'll use interrupts to listen
 * for keyboard input by the user. 
 */
void init_idt() {
    unsigned long keyboard_address;
    unsigned long idt_address;
    unsigned long idt_ptr[2];

    // Set up IDT entry for keyboard interrupt
    keyboard_address = (unsigned long) keyboard_interrupt_handler;
    IDT[0x21].offset_low = keyboard_address & 0xffff;
    IDT[0x21].selector = 0x08; // Kernel code segment offset
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = 0x8e; // Interrupt gate
    IDT[0x21].offset_high = (keyboard_address & 0xffff0000) >> 16;

    /**
    * Ports for communication with the Programmable Interrupt Controllers:
    *
    *          PIC1  PIC2
    * Command  0x20  0xA0
    * Data     0x21  0xA1
    *
    * PIC 1 receives IRQ0 - IRQ7
    * PIC 2 receives IRQ8 - IRQ15
    *
    * PICS are initialized using 8-bit "Initialization Command Words" (ICWs)
    */

    /**
    * ICW1: Begin initialization
    *
    * This command makes the PICS listen for 3 more initialization words on
    * their respective data ports. 0x21 for PIC1 and 0xA1 for PIC2.
    */
    write_port(0x20, 0x11);
    write_port(0xA0, 0x11);

    /**
    * ICW2: Remap offset address of IDT
    *
    * In x86 protected mode, Intel has designated the first 32 interrupts as
    * reserved for CPU extensions. So we must remap the PICs beyond 0x20.
    *
    * This is the value which we add to the interrupt line number to form the
    * interrupt number.
    */
    write_port(0x21, 0x20);
    write_port(0xA1, 0x28);

    /**
    * ICW3: Set up cascading
    *
    * PICs allow cascading their outputs to the others' inputs. For now, we
    * don't want to do this so we set both values to zero.
    */
    write_port(0x21, 0x00);
    write_port(0xA1, 0x00);

    /**
    * ICW4: Environment info
    *
    * Tells the PICs about additional environment paramters. Let's set the
    * lowest bit to tell them we're in 80x86 mode. This ICW concludes the
    * PIC initialization process.
    */
    write_port(0x21, 0x01);
    write_port(0xA1, 0x01);
    // Init finished!

    /**
    * Ignore all interrupts by masking them. We haven't set up any handlers yet
    * so we don't want any interrupts to fire. This would crash our kernel.
    */
    write_port(0x21, 0xff);
    write_port(0xA1, 0xff);

    // Populate the IDT descriptor
    idt_address = (unsigned long) IDT;
    idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
    init_keyboard();
}
