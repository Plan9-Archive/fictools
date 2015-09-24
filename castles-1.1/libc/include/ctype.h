/* ctype.h
 * Minimalist ctype for zlibc.
 * (C) 2001 David Given
 */

#ifndef __CTYPE_H
#define __CTYPE_H

extern int isalnum(int c);
extern int isalpha(int c);
extern int isdigit(int c);

extern int toupper(int c);
extern int tolower(int c);

#endif
