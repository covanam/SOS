#include "uart.h"

struct UART_t *const UART1 = (struct UART_t *)(0x40011000);
struct UART_t *const UART6 = (struct UART_t *)(0x40011400);

void uart_write(struct UART_t *const uart, char c) {
    while ((uart->SR & (1u << 7u)) == 0u) {
        /* wait for TXE */
    }
    uart->DR = c;
}

char uart_read(struct UART_t *const uart) {
    if ((uart->SR & (1u << 5u)) != 0u)
        return uart->DR;
    else
        return '\0';
}
