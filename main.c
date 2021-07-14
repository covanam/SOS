#include "gpio.h"
#include "power.h"
#include "rcc.h"
#include "os.h"

int main() {
    /* gpiod clock */
    RCC->AHB1ENR = (1u << 3u);

    __asm__("nop");

    GPIOD->MODER = (1u << 24u) | (1u << 26u) | (1u << 28u) | (1u << 30u);

    start_os();    
}