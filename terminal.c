#include "os.h"
#include "apps.h"
#include <stdio.h>
#include "uart.h"

int putchar(int c) {
	uart_write(UART6, (char)c);

	if (c == '\n') uart_write(UART6, '\r');

	return c;
}

int getchar(void) {
	char c = uart_read(UART6);

	/* putty send '\r' when Enter is pressed */
	if (c == '\r') c = '\n';

	putchar(c);

    return c;
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

    printf("\r\nWelcome to Simple operating system\n");
    printf("Compiled on " __DATE__ " at " __TIME__ "\n");

    while (1) {
        char c;

        c = getchar();

        if (c != '\n') {
            *(pbuf++) = c;
        }
        else {
            *pbuf = '\0';
            pbuf = buf;

            if (0 == strcmp(buf, "red"))
                startThread(blinking_red);
            else if (0 == strcmp(buf, "blue"))
                startThread(blinking_blue);
            else if (0 == strcmp(buf, "green"))
                startThread(blinking_green);
            else {
                printf("Unrecognized command: %s\r\n", buf);
            }
        }
    }
}