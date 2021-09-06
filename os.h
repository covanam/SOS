#ifndef OS_H
#define OS_H

#include <stdint.h>

uint32_t getMsCount(void);

__attribute__((noreturn)) void startOs(void);

void startThread(void (*entryAddress)(void));

void sleep(int);

#endif
