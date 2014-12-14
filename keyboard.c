#include "keyboard.h"
#include "screen.h"

void init_keyboard() {
  write_port(0x21, 0xFD);
  // TODO: Enable only necessary bit
}

void keyboard_handler() {
  puts("Key pressed\n");
  return;
}
