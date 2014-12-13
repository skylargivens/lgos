#include "kernel.h"

char *vidptr = (unsigned char *) 0xB8000; // Video memory lives here
char attr = 0x0F;
int cursorX = 0;
int cursorY = 0;

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define SCREEN_MEMORY_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT * 2)

void kmain() {
  cls();
  puts("\b\bLorem\b ipsum dolor sit amet, consectetur adipisicing elit. Aut recusandae excepturi delectus, incidunt sunt a expedita maiores iste iusto non vel asperiores veniam eveniet voluptatibus inventore aliquam deleniti, laborum corporis\b\b\b\b\b\b\b\b\n\n");
  puts("Done...");
}

/**
 * Clear the screen
 */
void cls() {
  for (int i = 0; i < SCREEN_MEMORY_SIZE; i += 2) {
    vidptr[i] = ' ';
    vidptr[i + 1] = attr;
  }
}

/**
 * Print a string to the screen
 */
void puts(char str[]) {
  int i = 0;

  while(str[i] != '\0') {
    putch(str[i]);
    i++;
  }
}

/**
 * Print a character to the screen using the current attributes
 *
 * TODO: Handle tab character
 */
void putch(unsigned char c) {
  unsigned int location;

  if (c == '\b') {
    if (cursorX != 0) cursorX--;
  } else if (c == '\r') {
    cursorX = 0;
  } else if (c == '\n') {
    cursorX = 0;
    cursorY++;
  } else if (c >= ' ') {
    location = ((cursorY * SCREEN_WIDTH) + cursorX) * 2;
    vidptr[location] = c;
    vidptr[location + 1] = attr;
    cursorX++;
  }

  if (cursorX >= SCREEN_WIDTH) {
    cursorX = 0;
    cursorY++;
  }

  scroll();
  // TODO: Move hardware cursor
}

/**
 * Scroll the screen up by one row if necessary
 */
void scroll() {
  if (cursorY >= SCREEN_HEIGHT) {
    cursorY = SCREEN_HEIGHT - 1;
    // TODO: Scroll screen
  }
}
