#ifndef OS_H
#define OS_H

#include <stdint.h>

uint32_t get_ms_counter(void);

__attribute__((noreturn)) void start_os(void);

void sleep(int);

#endif
