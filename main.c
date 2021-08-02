#include "gpio.h"
#include "os.h"
#include "rcc.h"
#include "uart.h"

int main() {
    /* gpiod and gpioc clock */
    RCC->AHB1ENR = (1u << 3u) | (1 << 2u);

    /* enable clock for USART6 */
    RCC->APB2ENR = 0x20;

    __asm__("nop");

    GPIOD->MODER = (1u << 24u) | (1u << 26u) | (1u << 28u) | (1u << 30u);

    /* config 9600 baud (clk = 16MHz) */
    UART6->BRR = (208u << 4U) | 3U;

    /* set over8, enable, TE */
    UART6->CR1 = (1U << 15U) | (1U << 13U) | (1U << 3U);

    /* setup pin6, pin7 for alternative function mode */
    GPIOC->MODER = (2u << 12u) | (2u << 14u);

    /* alternative function 8: USART6 */
    GPIOC->AFRL = (8u << 24u) | (8u << 28u);

    start_os();
}

void led(uint32_t n) {
    GPIOD->ODR ^= (1 << n);
}

void toggle_green(void) {
    GPIOD->ODR ^= (1u << 12u);
    print(UART6, "nothing\r\n");
    waitevent();
}

void blinking_green(void) {
    uint32_t count = 0;
    while(1) {
        if (count < MsCount) {
            count += 500;
            toggle_green();
        }
    }
}

void blinking_blue(void) {
    uint32_t count = 0;
    while(1) {
        if (count < MsCount) {
            count += 2000;
            GPIOD->ODR ^= (1u << 15u);
        }
        waitevent();
    }
}

void blinking_red(void) {
    uint32_t count = 0;
    while(1) {
        if (count < MsCount) {
            count += 300;
            GPIOD->ODR ^= (1u << 14u);
        }
        waitevent();
    }
}
