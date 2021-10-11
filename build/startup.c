#include <stdint.h>
#include <stddef.h>
#include "header.h"

extern int _flash_size[];
extern int _total_size[];
extern int _got_start[];
extern int _got_size[];
extern int _bss_start[];
extern int _bss_size[];
void _entry(void);

__attribute__((section(".header")))
struct header _header = {
	.flash_size = (size_t)_flash_size,
	.total_size = (size_t)_total_size,
	.entry_addr = _entry,
	.got_start = _got_start,
	.got_size = (size_t)_got_size,
	.bss_start = _bss_start,
	.bss_size = (size_t)_bss_size,
};

void _entry(void)
{
	extern int main();
	main();
}
