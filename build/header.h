#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>

struct header {
	size_t size;
	void (*entry_addr)(void);
	void *got_start;
	size_t got_size;
};

#endif
