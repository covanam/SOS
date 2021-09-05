#include "uart.h"
#include "os.h"
#include "apps.h"

static void print(const char* s) {
    for (; *s != '\0'; ++s) {
        uart_write(UART6, *s);
    }
}

void terminal(void) {
    startThread(blinking_green);
    startThread(blinking_blue);
    startThread(blinking_red);

    print("\r\nWelcome to Simple operating system\r\n");
    print("Compiled on " __DATE__ " at " __TIME__);

    while (1) {
        char c;

        while (c = uart_read(UART6), c == '\0') {
            /* wait for user input */
        }

        /* echo typed character */
        uart_write(UART6, c);
        if (c == '\r') uart_write(UART6, '\n');
    }
}