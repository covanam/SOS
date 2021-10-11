#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t n)
{
	const char *ps = src;
	char *pd = dest;
	while (n--) {
		*pd = *ps;
		++pd;
		++ps;
	}
	return dest;
}

void *memset(void *s, int c, size_t n)
{
	char *p = s;
	while (n--) {
		*p = c;
		++p;
	}
	return s;
}
