#include "kernel.h"
#include "screen.h"

void kmain() {
  initVideo();
  puts("\b\bLorem\b ipsum dolor sit amet, consectetur adipisicing elit. Aut recusandae excepturi delectus, incidunt sunt a expedita maiores iste iusto non vel asperiores veniam eveniet voluptatibus inventore aliquam deleniti, laborum corporis\b\b\b\b\b\b\b\b\n\n");
  puts("Done...");
}
