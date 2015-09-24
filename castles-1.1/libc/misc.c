/* misc.c
 * Miscellaneous zlibc stuff.
 * (C) 2001 David Given
 */

#include <stdlib.h>
#include <errno.h>

int errno;

int abs(int i)
{
	return (i > 0) ? i : -i;
}

