#include "power.h"
#include <stdint.h>

void deepsleep(void) {
    volatile uint32_t *SCR = (uint32_t *)0xE000ED10;
    *SCR = 4u;
    __asm__("wfi");
}
