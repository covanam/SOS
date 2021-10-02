#include "thread.h"
#include <proc.h>
#include <stdlib.h>
#include <string.h>

void start_process(void *program)
{
	size_t size = *(size_t *)program;
	void *entry_addr = ((void **)program)[1];

	void *addr = malloc(size);
	memcpy(addr, program, size);

	if ((char *)addr > (char *)program) {
		size_t offset = (char *)addr - (char *)program;
		entry_addr = (char *)entry_addr + offset;
	} else {
		size_t offset = (char *)program - (char *)addr;
		entry_addr = (char *)entry_addr - offset;
	}

	detach_thread(start_thread(entry_addr));
}
