#ifndef OS_H
#define OS_H

#include <stdint.h>

uint32_t getMsCount(void);

void startOs(void);

void yield(void);

#endif
