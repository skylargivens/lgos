void kmain() {
  char *greeting = "Welcome to Looking Glass!";
  char *vidptr = 0xb8000; // Video memory lives here
  unsigned int i = 0;
  unsigned int j = 0;

  // Let's clear the screen
  while (j < (80 * 25 * 2)) {
    // Set blank character
    vidptr[j] = ' ';
    // Set color of character - light gray on black
    vidptr[j+1] = 0x07;
    j += 2;
  }

  // Write the greeting to the top left corner of the screen
  j = 0;
  while (greeting[j] != '\0') {
    vidptr[i] = greeting[j];
    j++;
    i += 2; // In video memory, characters are stored at every other byte
  }
}
