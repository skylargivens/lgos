#include "screen.h"
#include "io.h"

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
  if (cursorY >= SCREEN_HEIGHT) {
      cursorY = SCREEN_HEIGHT - 1;
      scroll_up();
  }

  move_hw_cursor(cursorX, cursorY);
}

/**
 * Scroll the screen up by one row
 */
void scroll_up() {
    int last_row_start = (SCREEN_WIDTH * (SCREEN_HEIGHT - 1) * 2);

    // Shift characters and their attributes up a single row
    for (int pos = SCREEN_WIDTH; pos < (SCREEN_WIDTH * SCREEN_HEIGHT * 2); pos++) {
        vidptr[pos - SCREEN_WIDTH * 2] = vidptr[pos];
    }

    // Clear the last row
    for (int pos = last_row_start; pos < (SCREEN_WIDTH * SCREEN_HEIGHT * 2); pos += 2) {
        vidptr[pos] = ' ';
    }
}

/**
 * Move hardware cursor to x, y coords
 */
void move_hw_cursor(int x, int y) {
    // @STODO - Move hardware cursor to software cursor position
    unsigned short position = (y * 80) + x;

    // High byte
    write_port(0x3D4, 0x0F);
    write_port(0x3D5, (unsigned char) (position & 0xFF));
    
    // Low byte
    write_port(0x3D4, 0x0E);
    write_port(0x3D5, (unsigned char) ((position >> 8) & 0xFF));
}

void init_video() {
  vidptr = (unsigned char*) 0xB8000;
  cls();
}
