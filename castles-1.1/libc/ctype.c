/* ctype.c
 * Minimalist ctype for zlibc.
 * (C) 2001 David Given
 */

#include <stdio.h>
#include <stdlib.h>

int isalnum(int c)
{
	return (((c >= 'A') && (c <= 'Z')) ||
	    	((c >= 'a') && (c <= 'z')) ||
	    	((c >= '0') && (c <= '9')));
}

int isalpha(int c)
{
	return (((c >= 'A') && (c <= 'Z')) ||
	    	((c >= 'a') && (c <= 'z')));
}

int isdigit(int c)
{
	return ((c >= '0') && (c <= '9'));
}

int isspace(int c)
{
	switch (c)
	{
		case ' ':
		case '\f':
		case '\n':
		case '\r':
		case '\t':
		case '\v':
			return 1;
	}
	return 0;
}

int toupper(int c)
{
	if ((c >= 'a') && (c <= 'z'))
		return c + ('A' - 'a');
	return c;
}

int tolower(int c)
{
	if ((c >= 'A') && (c <= 'A'))
		return c + ('a' - 'A');
	return c;
}

