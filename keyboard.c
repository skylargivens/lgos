#include "keyboard.h"
#include "screen.h"
#include "keyboard_map.h"
#include "io.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

void init_keyboard() {
    write_port(0x21, 0xFD);
    // TODO: Enable only necessary bit
}

void keyboard_handler() {
    unsigned char status;
    char key_code;

    // Write End of Interrupt (EOI) to PIC
    write_port(0x20, 0x20);

    status = read_port(KEYBOARD_STATUS_PORT);

    // Check lowest bit to see if there are characters in the buffer
    if (status & 0x01) {
        key_code = read_port(KEYBOARD_DATA_PORT);
        if (key_code < 0) return;
        // Print character to the screen
        putch(keyboard_map[key_code]);
    }

  return;
}

