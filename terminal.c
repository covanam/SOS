#include "uart.h"

static void print(const char* s) {
    for (; *s != '\0'; ++s) {
        uart_write(UART6, *s);
    }
}

void terminal(void) {
    print("\r\nWelcome to Simple operating system\r\n");
    print("This is developed by Nam Cao\r\n");

    while (1) {
        char c;

        while (c = uart_read(UART6), c == '\0') {
            /* wait for user input */
        }

        /* echo typed character */
        uart_write(UART6, c);
    }
}