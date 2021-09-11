#ifndef OS_H
#define OS_H

#include <stdint.h>

__attribute__((noreturn)) void start_os(void);

void sleep(unsigned int);

#endif
