#ifndef OS_H
#define OS_H

#include <stdint.h>

uint32_t getMsCount(void);

__attribute__((noreturn)) void startOs(void);

void yield(void);

void startThread(void (*entryAddress)(void));

#endif
