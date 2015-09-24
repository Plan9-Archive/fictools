/* printf.c
 * Limited functionality printf for the Z-machine's libc.
 * (C) 2001 David Given
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <z.h>

#define OUTC(c) do { \
		if (wrch(c, fp) == 0) \
			return count; \
		count++; \
	} while(0)

static int renderlong(int base, char* buf, unsigned long l)
{
	int count = 0;

	if (l == 0)
	{
		*buf++ = 0;
		return 1;
	}

	while (l != 0)
	{
		*buf++ = l % base;
		l /= base;
		count++;
	}

	return count;
}

static int printlong(int (*wrch)(int c, void* fp), void* fp, long l)
{
	char buf[15];
	int count = 0;
	int i;

	if (l < 0)
	{
		OUTC('-');
		l = -l;
	}

	i = renderlong(10, buf, l);
	while (i)
	{
		i--;
		OUTC('0' + buf[i]);
	}

	return count;
}

static int printunsignedlong(int (*wrch)(int c, void* fp), void* fp, unsigned long l)
{
	char buf[15];
	int count = 0;
	int i;

	i = renderlong(10, buf, l);
	while (i)
	{
		i--;
		OUTC('0' + buf[i]);
	}

	return count;
}

static int printhex(int (*wrch)(int c, void* fp), void* fp, long l)
{
	char buf[15];
	int count = 0;
	int i, c;

	if (l < 0)
	{
		OUTC('-');
		l = -l;
	}

	i = renderlong(16, buf, l);
	while (i)
	{
		i--;
		c = buf[i];
		if (c < 10)
			OUTC('0' + c);
		else
			OUTC('A' + (c - 10));
	}

	return count;
}

static int vxprintf(int (*wrch)(int c, void* fp), void* fp, char* format, va_list ap)
{
	int c;
	int count = 0;

	while (c = *format++)
	{
		if (c == '%')
		{
			switch (c = *format++)
			{
				case 'l':
				{
					switch (c = *format++)
					{
						case 'd':
						{
							long i = va_arg(ap, long);
							printlong(wrch, fp, i);
							break;
						}
							
						case 'u':
						{
							unsigned long i = va_arg(ap, unsigned long);
							printunsignedlong(wrch, fp, i);
							break;
						}
							
						case 'x':
						case 'X':
						{
							long i = va_arg(ap, long);
							printhex(wrch, fp, i);
							break;
						}
					}
					break;
				}

				case 'd':
				{
					int i = va_arg(ap, int);
					printlong(wrch, fp, i);
					break;
				}
					
				case 'u':
				{
					unsigned int i = va_arg(ap, int);
					printunsignedlong(wrch, fp, i);
					break;
				}
					
				case 'x':
				{
					unsigned int i = va_arg(ap, int);
					printhex(wrch, fp, i);
					break;
				}
					
				case 's':
				{
					char* s = va_arg(ap, char*);
					while (c = *s++)
						OUTC(c);
					break;
				}

				case 'c':
				{
					char c = va_arg(ap, int);
					OUTC(c);
					break;
				}

				default:
				{
					OUTC(c);
					break;
				}
			}
		}
		else
			OUTC(c);
	}

	return count;
}

int printf(char* format, ...)
{
	int i;
	va_list ap;
	va_start(ap, format);
	i = vxprintf(fputc, (void*)stdout, format, ap);
	va_end(ap);
	return i;
}

