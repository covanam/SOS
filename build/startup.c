#include <stdint.h>
#include <stddef.h>
#include "header.h"

#define HEAP_SIZE 1024U

__attribute__ ((section(".heap")))
uint32_t _heap_memory[HEAP_SIZE / sizeof(uint32_t)];

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
	extern void init_malloc(void* heap_start, size_t heap_size);
	init_malloc(_heap_memory, sizeof(_heap_memory));
	extern int main();
	main();
}
