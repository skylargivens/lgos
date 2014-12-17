#include "kernel.h"
#include "screen.h"
#include "interrupts.h"

void kmain() {
    init_video();

    puts("Setting up IDT...");
    init_idt();
    puts("Done\n");

    puts("\nLooking Glass OS v0.0.1\n\n");
    puts("Press a key...\n");
    while(1);
}
