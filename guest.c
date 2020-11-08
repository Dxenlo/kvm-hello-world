#include <stddef.h>
#include <stdint.h>

static void outb(uint16_t port, uint8_t value) {
	asm("outb %0,%1" : /* empty */ : "a" (value), "Nd" (port) : "memory");
}

static uint8_t inb(uint16_t port){
	uint8_t value;
	asm("inb %1, %0" : "=a"(value):"Nd"(port):/* empty */);
	return value;
}

void
__attribute__((noreturn))
__attribute__((section(".start")))
_start(void) {
	uint8_t m;
	m = inb(0xE9);
	
	outb(0xE9, m);

	
	const char *p;

	for (p = "Hello, world!\n"; *p; ++p)
		outb(0xE9, *p);

	*(long *) 0x400 = 42;

	for (;;)
		asm("hlt" : /* empty */ : "a" (42) : "memory");
}
