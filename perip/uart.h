#ifndef UART_H
#define UART_H

#include <stdint.h>

struct UART_t {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GPTR;
};

extern struct UART_t *const UART1;
extern struct UART_t *const UART6;

void uart_write(struct UART_t *const uart, char c);
char uart_read(struct UART_t *const uart);

#endif /* UART_H */
