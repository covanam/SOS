#include <stdint.h>
#include <stddef.h>

extern uint8_t _program_size[];
void _entry(void);

__attribute__((section(".header"))) struct {
	size_t size;
	void *entry_addr;
} _header = { .size = (size_t)_program_size, .entry_addr = _entry };

void _entry(void)
{
	extern int main();
	main();
}
