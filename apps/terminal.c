#include "thread.h"
#include "apps.h"
#include <stdio.h>
#include "uart.h"

int putchar(int c)
{
	uart_write(UART6, (char)c);

	if (c == '\n')
		uart_write(UART6, '\r');

	return c;
}

int getchar(void)
{
	static int line_pointer = 0;

	char c = uart_read(UART6);

	/* putty sends '\r' when Enter is pressed, we want Enter means '\n' */
	if (c == '\r')
		c = '\n';

	if (c != '\x7f' || line_pointer > 0)
		putchar(c);

	if (c == '\n') {
		line_pointer = 0;
	} else if (c == '\x7f') {
		if (line_pointer > 0)
			line_pointer--;
	} else {
		line_pointer++;
	}

	return c;
}

int strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const char *p1 = ptr1;
	const char *p2 = ptr2; 
	while (num--) {
		if (*p1 != *p2)
			return 1;
		p1++, p2++;
	}
	return 0;
}

void get_command(char *buf)
{
	char c;
	char *pbuf = buf;
	while (c = getchar(), c != '\n') {
		if (c != '\x7f') {
			*(pbuf++) = c;
		} else {
			if (pbuf != buf) {
				--pbuf;
			}
		}
	}
	*pbuf = '\0';
}

static const struct app *find_app(const char *name) {
	const struct app *ret = NULL;

	for (const struct app *a = app_list; a->name != NULL; ++a) {
		if (0 == strcmp(a->name, name)) {
			ret = a;
			break;
		}
	}

	return ret;
}

void terminal(void)
{
	char buf[50];

	printf("\nWelcome to Simple operating system\n");
	printf("Compiled on " __DATE__ " at " __TIME__ "\n");

	while (1) {
		printf(">>> ");

		int detach;
		const struct app *a;

		get_command(buf);

		if (0 == memcmp("detach ", buf, 7)) {
			a = find_app(buf + 7);
			detach = 1;
		} else {
			a = find_app(buf);
			detach = 0;
		}

		if (a != NULL) {
			struct thread_handle *h = start_thread(a->entry);
			if (detach) detach_thread(h);
			else wait_thread(h);
		}
		else
			printf("Unrecognized command: %s\n", buf);
	}
}
