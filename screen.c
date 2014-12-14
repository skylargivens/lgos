#include "screen.h"

unsigned char *vidptr; // Video memory lives here
char attr = 0x0F;

// Software cursor
int cursorX = 0;
int cursorY = 0;

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

/**
 * Clear the screen
 */
void cls() {
  for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT * 2); i += 2) {
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

  // Backspace
  if (c == '\b') {
    if (cursorX != 0) cursorX--;
  }

  // Carriage return
  else if (c == '\r') {
    cursorX = 0;
  }

  // Newline
  else if (c == '\n') {
    cursorX = 0;
    cursorY++;
  }

  // Non-special characters
  else if (c >= ' ') {
    location = ((cursorY * SCREEN_WIDTH) + cursorX) * 2;
    vidptr[location] = c;
    vidptr[location + 1] = attr;
    cursorX++;
  }

  // Move cursor to next line if it's beyond the right edge of the screen
  if (cursorX >= SCREEN_WIDTH) {
    cursorX = 0;
    cursorY++;
  }

  // Scroll the screen up if necessary
  if (cursorY >= SCREEN_HEIGHT) scrollup();
  // TODO: Move hardware cursor to match software cursor
}

/**
 * Scroll the screen up by one row if necessary
 */
void scrollup() {
    cursorY = SCREEN_HEIGHT - 1;
    // TODO: Implement scrolling
}

void initVideo() {
  vidptr = (unsigned char*) 0xB8000;
  cls();
}
