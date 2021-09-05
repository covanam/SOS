#include "uart.h"
#include "os.h"
#include "apps.h"

static void print(const char* s) {
    for (; *s != '\0'; ++s) {
        uart_write(UART6, *s);
    }
}

int strcmp(const char* s1, const char* s2)
{
    while (*s1 && (*s1 == *s2))
        s1++, s2++;
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void terminal(void) {
    char buf[20];
    char *pbuf = buf;

    print("\r\nWelcome to Simple operating system\r\n");
    print("Compiled on " __DATE__ " at " __TIME__ "\r\n");

    while (1) {
        char c;

        while (c = uart_read(UART6), c == '\0') {
            /* wait for user input */
        }

        /* echo typed character */
        uart_write(UART6, c);

        if (c != '\r') {
            *(pbuf++) = c;
        }
        else {
            uart_write(UART6, '\n'); //require for proper newline in putty
            *pbuf = '\0';
            pbuf = buf;

            if (0 == strcmp(buf, "red"))
                startThread(blinking_red);
            else if (0 == strcmp(buf, "blue"))
                startThread(blinking_blue);
            else if (0 == strcmp(buf, "green"))
                startThread(blinking_green);
            else {
                print("Unrecognized command: ");
                print(buf);
                print("\r\n");
            }
        }
    }
}