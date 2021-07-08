#include <stdint.h>

struct UART {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GPTR;
};

struct GPIO {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
};

struct GPIO *gpiod = (struct GPIO *)0x40020C00;

struct UART *const uart1 = (struct UART *)(0x40011000);

uint32_t *const RCC_CFGR = (uint32_t *)(0x40023800 + 0x08);
uint32_t *const RCC_APB2END = (uint32_t *)(0x40023800 + 0x44);
uint32_t *const RCC_AHB1ENR = (uint32_t *)(0x40023800 + 0x30);

void Tx(struct UART *uart, char c) {
    while ((uart->SR & (1u << 6u)) == 0u)
        ;
    uart->DR = c;
}

void print(const char *s) {
    while (*s != '\0') {
        Tx(uart1, *s);
        s++;
    }
}

int main() {
    /* setup clock for UART1 to run at 16MHz */
    /* set AHB and APB2 prescaler to 1 */
    *RCC_CFGR = 0x0;

    /* enable clock for USART1 */
    *RCC_APB2END = 0x10;

    /* gpiod clock */
    *RCC_AHB1ENR = (1u << 3u);

    uart1->BRR = (52U << 4U) | 1U;                       // 9600 baud
    uart1->CR1 = (1U << 15U) | (1U << 13U) | (1U << 3U); // over8, enable, TE

    gpiod->MODER = (1u << 24u) | (1u << 26u) | (1u << 28u) | (1u << 30u);
    gpiod->PUPDR = (1u << 24u) | (1u << 26u) | (1u << 28u) | (1u << 30u);
    gpiod->ODR = (1u << 12u) | (1u << 13u) | (1u << 14u) | (1u << 15u);
}