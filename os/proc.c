#include "thread.h"
#include <proc.h>
#include <stdlib.h>
#include <string.h>
#include "../build/header.h"
#include <stdint.h>

struct header load_program_to_ram(void *addr)
{
	/* copy the header to aligned memory before reading */
	struct header h;
	memcpy(&h, addr, sizeof(struct header));

	void *ram_addr = malloc(h.total_size - sizeof h);
	memcpy(ram_addr, addr + sizeof h, h.flash_size - sizeof h);

	size_t offset = (size_t)ram_addr - sizeof h;

	h.entry_addr += offset;
	h.got_start += offset;
	h.bss_start += offset;

	void **p = h.got_start;
	for (size_t i = 0; i < h.got_size / sizeof(void *); i++)
		if (p[i] != NULL) p[i] += offset;

	memset(h.bss_start, 0, h.bss_size);

	return h;
}

void start_process(void *program)
{
	struct header h = load_program_to_ram(program);

	start_thread(h.entry_addr, NULL);
}
