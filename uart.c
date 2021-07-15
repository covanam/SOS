#include "uart.h"

struct UART_t *const UART1 = (struct UART_t *)(0x40011000);
struct UART_t *const UART6 = (struct UART_t *)(0x40011400);

static inline void uart_putc(struct UART_t *const uart, char c) {
    while ((uart->SR & (1u << 7u)) == 0u) {
        /* wait for TXE */
    }
    uart->DR = c;
}

void print(struct UART_t *const u, const char *s) {
    for (; *s != '\0'; ++s) {
        uart_putc(u, *s);
    }
}
