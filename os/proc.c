#include "thread.h"
#include <proc.h>
#include <stdlib.h>
#include <string.h>
#include "../build/header.h"
#include <stdint.h>

static void *load_program_to_ram(void *addr)
{
	/* copy the header to aligned memory before reading */
	struct header h;
	memcpy(&h, addr, sizeof(struct header));

	struct header *ram_header = malloc(h.size);
	memcpy(ram_header, addr, h.size);

	size_t offset = (size_t)ram_header;

	ram_header->entry_addr += offset;
	ram_header->got_start += offset;

	void **p = ram_header->got_start;
	for (size_t i = 0; i < ram_header->got_size / sizeof(void *); i++)
		p[i] += offset;

	return ram_header;
}

void start_process(void *program)
{
	struct header *ram_header = load_program_to_ram(program);

	detach_thread(start_thread(ram_header->entry_addr));
}
