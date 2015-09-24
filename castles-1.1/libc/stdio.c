/* stdio.c
 * Ultra-minimalist stdio for zlibc.
 * (C) 2001 David Given
 */

#include <stdlib.h>
#include <stdio.h>
#include <z.h>

static struct __stdio_file _stdin = {0, 0, 0};
static struct __stdio_file _stdout = {1, 0, 0};
static struct __stdio_file _stderr = {2, 0, 0};
static struct __stdio_file _stdaux = {3, 0, 0};

FILE* stdin = &_stdin;
FILE* stdout = &_stdout;
FILE* stderr = &_stderr;
FILE* stdaux = &_stdaux;

int fputc(int c, FILE* stream)
{
	char cc = c;
	if (write(stream->fd, &cc, 1) != 1)
	{
		stream->error = 1;
		return EOF;
	}
	return c;
}

int fgetc(FILE* stream)
{
	char c;
	int i = read(stream->fd, &c, 1);
	switch (i)
	{
		case -1:
			stream->error = 1;
			printf("fgetc error, returning %d\n", EOF);
			return EOF;

		case 0:
			stream->eof = 1;
			return EOF;

		case 1:
			return c;
	}
}

int fputs(const char* s, FILE* stream)
{
	int len = strlen(s);
	int i = write(stream->fd, s, len);

	if (i == -1)
	{
		stream->error = 1;
		return EOF;
	}

	return i;
}

int puts(const char* s)
{
	int i = fputs(s, stdout);
	putchar('\n');
	return i;
}
	
int fflush(FILE* stream)
{
	if (stream->error)
		return EOF;
	return 0;
}

