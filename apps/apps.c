#include "gpio.h"
#include "os.h"
#include <stdint.h>
#include "apps.h"
#include <stddef.h>
#include <stdio.h>
#include "mutex.h"

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

static struct mutex counter_mutex;
static volatile unsigned int counter = 0;

void plus_million(void) {
	for (int i = 0; i < 1000000; ++i) {
		counter++;
	}
}

void plus_million_sync(void) {
	for (int i = 0; i < 1000000; ++i) {
		mutex_lock(&counter_mutex);
		counter++;
		mutex_release(&counter_mutex);
	}
}

void print_counter(void) {
	printf("counter=%u\n", counter);
}

void reset_counter(void) {
	counter = 0;
}

const struct app app_list[] = {
	{
		.name = "green",
		.entry = blinking_green,
	},
	{
		.name = "blue",
		.entry = blinking_blue,
	},
	{
		.name = "red",
		.entry = blinking_red,
	},
	{
		.name = "orange",
		.entry = toggle_orange,
	},
	{
		.name = "plus",
		.entry = plus_million,
	},
	{
		.name = "plus sync",
		.entry = plus_million_sync,
	},
	{
		.name = "print",
		.entry = print_counter,
	},
	{
		.name = "reset",
		.entry = reset_counter,
	},
	{
		NULL,
		NULL,
	},
};
