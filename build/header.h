#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>

struct header {
	size_t flash_size;
	size_t total_size;
	void (*entry_addr)(void);
	void *got_start;
	size_t got_size;
	void *bss_start;
	size_t bss_size;
};

#endif
