#ifndef OS_H
#define OS_H

#include <stdint.h>

extern volatile uint32_t MsCount;

void start_os(void);

void waitevent(void);

#endif
