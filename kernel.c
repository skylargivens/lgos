#include "kernel.h"

char *vidptr = (char*) 0xB8000; // Video memory lives here

void kmain() {
  clearScreen();
  puts("Welcome to Looking Glass!");
}

/**
 * Clear the screen
 */
void clearScreen() {
  unsigned int j = 0;

  for (int i = 0; i < 4000; i++) {
    vidptr[i] = ' '; // Set blank character
    vidptr[i+1] = 0x07; // Set color of character - light gray on black
  }
}

/**
 * Write a string to the buffer
 * @param str String to print to screen.
 */
void puts(char *str) {
  int i = 0;
  int j = 0;

  while (str[j] != '\0') {
    vidptr[i] = str[j];
    j++;
    i += 2;
  }
}
