void init_idt();

extern void keyboard_interrupt_handler();
extern void write_port(int port, int value);
extern int read_port(int port);
extern void load_idt(unsigned long* idt_ptr);
