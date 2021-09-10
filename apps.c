#include "gpio.h"
#include "os.h"
#include <stdint.h>

void toggle_green(void)
{
	GPIOD->ODR ^= (1u << 12u);
}

void blinking_green(void)
{
	while (1) {
		toggle_green();
		sleep(500);
	}
}

void blinking_blue(void)
{
	while (1) {
		GPIOD->ODR ^= (1u << 15u);
		sleep(2000);
	}
}

void blinking_red(void)
{
	while (1) {
		GPIOD->ODR ^= (1u << 14u);
		sleep(300);
	}
}

void toggle_orange(void)
{
	GPIOD->ODR ^= (1u << 13u);
}
