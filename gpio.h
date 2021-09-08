#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

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

extern struct GPIO *const GPIOC;
extern struct GPIO *const GPIOD;

#endif /* GPIO_H */
