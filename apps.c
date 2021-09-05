#include "gpio.h"
#include "os.h"
#include <stdint.h>

void toggle_green(void) {
    GPIOD->ODR ^= (1u << 12u);
    yield();
}

void blinking_green(void) {
    uint32_t count = 0;
    while(1) {
        if (count < getMsCount()) {
            count += 500;
            toggle_green();
        }
    }
}

void blinking_blue(void) {
    uint32_t count = 0;
    while(1) {
        if (count < getMsCount()) {
            count += 2000;
            GPIOD->ODR ^= (1u << 15u);
        }
        yield();
    }
}

void blinking_red(void) {
    uint32_t count = 0;
    while(1) {
        if (count < getMsCount()) {
            count += 300;
            GPIOD->ODR ^= (1u << 14u);
        }
        yield();
    }
}
