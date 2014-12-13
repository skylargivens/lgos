#include "kernel.h"

char *vidptr = 0xB8000; // Video memory lives here

void kmain() {
  clearScreen();
  fake_puts("Welcome to Looking Glass OS!");
}

/**
 * Clear the screen
 */
void clearScreen() {
  unsigned int j = 0;

  for (int i = 0; i < (80 * 25 * 2); i++) {
    vidptr[i] = ' '; // Set to blank character
    vidptr[i+1] = 0x0F; // Set color of character
  }
}

/**
 * Write a string to the screen
 * @param str String to print to screen
 */
void fake_puts(char *str) {
  int i = 0;
  int j = 0;

  while (str[j] != '\0') {
    vidptr[i] = str[j];
    vidptr[i+1] = 0x0F;
    i += 2;
    j++;
  }
}
