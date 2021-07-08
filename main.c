#include "gpio.h"
#include "rcc.h"

int main() {
    /* gpiod clock */
    RCC->AHB1ENR = (1u << 3u);

    GPIOD->MODER = (1u << 24u) | (1u << 26u) | (1u << 28u) | (1u << 30u);
    GPIOD->ODR = (1u << 12u) | (1u << 13u) | (1u << 14u) | (1u << 15u);
}