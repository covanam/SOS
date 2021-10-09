#include <stdint.h>
#include <stddef.h>
#include "header.h"

extern uint8_t _program_size[];
extern int _got_start[];
extern int _got_size[];
void _entry(void);

__attribute__((section(".header")))
struct header _header = {
	.size = (size_t)_program_size,
	.entry_addr = _entry,
	.got_start = _got_start,
	.got_size = (size_t)_got_size,
};

void _entry(void)
{
	extern int main();
	main();
}
