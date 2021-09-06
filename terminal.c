#include "os.h"
#include "apps.h"
#include <stdio.h>

int strcmp(const char* s1, const char* s2)
{
    while (*s1 && (*s1 == *s2))
        s1++, s2++;
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void terminal(void) {
    char buf[20];
    char *pbuf = buf;

    printf("\r\nWelcome to Simple operating system\r\n");
    printf("Compiled on " __DATE__ " at " __TIME__ "\r\n");

    while (1) {
        char c;

        while (c = getchar(), c == '\0') {
            /* wait for user input */
        }

        /* echo typed character */
        putchar(c);

        if (c != '\r') {
            *(pbuf++) = c;
        }
        else {
            putchar('\n'); //require for proper newline in putty
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