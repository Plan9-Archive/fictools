/* Copyright (C) 1995,1996 Robert de Bath <rdebath@cix.compulink.co.uk>
 * This file is part of the Linux-8086 C library and is distributed
 * under the GNU Library General Public License.
 */

#include <string.h>
#include <malloc.h>

#ifdef __AS386_16__
#if __FIRST_ARG_IN_AX__
#define BCC_AX_ASM	/* BCC Assembler that can cope with arg in AX  */
#else
#define BCC_AX_ASM
#define BCC_ASM		/* Use 16 bit BCC assembler */
#endif

#define PARANOID	/* Include extra code for cld and ES register */
#endif

/* This is a basic string package; it includes the most used functions

   strlen strcat strcpy strcmp strncat strncpy strncmp strchr strrchr strdup
   memcpy memccpy memchr memset memcmp memmove

   These functions are in seperate files.
    strpbrk.o strsep.o strstr.o strtok.o strcspn.o
    strspn.o strcasecmp.o strncasecmp.o
 */

/********************** Function strlen ************************************/

size_t strlen(str)
const char * str;
{
   register char * p =(char *) str;
   while(*p) p++;
   return p-str;
}

/********************** Function strcat ************************************/

char * strcat(d, s)
char *d; 
const char * s;
{
   (void) strcpy(d+strlen(d), s);
   return d;
}

/********************** Function strcpy ************************************/

char * strcpy(d, s)
char *d;
const char * s;
{
   /* This is probably the quickest on an 8086 but a CPU with a cache will
    * prefer to do this in one pass */
   return memcpy(d, s, strlen(s)+1);
}

/********************** Function strcmp ************************************/

int strcmp(d, s)
const char *d;
const char * s;
{
  /* There are a number of ways to do this and it really does depend on the
     types of strings given as to which is better, nevertheless the Glib
     method is quite reasonable so we'll take that */

   register char *s1=(char *)d, *s2=(char *)s, c1,c2;
   while((c1= *s1++) == (c2= *s2++) && c1 );
   return c1 - c2;
}

/********************** Function strncat ************************************/

char * strncat(d, s, l)
char *d, *s;
size_t l;
{
   register char *s1=d+strlen(d), *s2;
   
   s2 = memchr(s, l, 0);
   if( s2 )
      memcpy(s1, s, s2-s+1);
   else
   {
      memcpy(s1, s, l);
      s1[l] = '\0';
   }
   return d;
}

/********************** Function strncpy ************************************/

char * strncpy(d, s, l)		/* FIXME need the fast version of this */
char *d, *s;
size_t l;
{
   register char *s1=d, *s2=s;
   while(l > 0)
   {
      l--;
      if( (*s1++ = *s2++) == '\0')
         break;
   }

   /* This _is_ correct strncpy is supposed to zap */
   for(; l>0; l--) *s1++ = '\0';
   return d;
}

/********************** Function strncmp ************************************/

int strncmp(d, s, l)
const char *d, *s;
size_t l;
{
   register char c1=0, c2=0;
   while(l-- >0)
      if( (c1= *d++) != (c2= *s++) || c1 == '\0' )
         break;
   return c1-c2;
}

/********************** Function strchr ************************************/

char *
strchr(s, c)
char * s;
int c;
{
   register char ch;
   for(;;)
   {
     if( (ch= *s) == c ) return s;
     if( ch == 0 ) return 0;
     s++;
   }
}

/********************** Function strrchr ************************************/

char * strrchr(s, c)
char * s;
int c;
{
   register char * prev = 0;
   register char * p = s;
   /* For null it's just like strlen */
   if( c == '\0' ) return p+strlen(p);

   /* everything else just step along the string. */
   while( (p=strchr(p, c)) != 0 )
   {
      prev = p; p++;
   }
   return prev;
}

/********************** Function strdup ************************************/

char * strdup(s)
char * s;
{
   register size_t len;
   register char * p;

   len = strlen(s)+1;
   p = (char *) malloc(len);
   if(p) memcpy(p, s, len); /* Faster than strcpy */
   return p;
}

/********************** Function memcpy ************************************/

void *
memcpy(d, s, l)
void *d;
const void *s;
size_t l;
{
   register char *s1=d, *s2=(char *)s;
   for( ; l>0; l--) *((unsigned char*)s1++) = *((unsigned char*)s2++);
   return d;
}

/********************** Function memccpy ************************************/

void * memccpy(d, s, c, l)	/* Do we need a fast one ? */
void *s, *d;
int c;
size_t l;
{
   register char *s1=d, *s2=s;
   while(l-- > 0)
      if((*s1++ = *s2++) == c )
         return s1;
   return 0;
}

/********************** Function memchr ************************************/

void * memchr(str, c, l)
const void * str;
int c;
size_t l;
{
   register char *p=(char *)str;
   while(l-- > 0)
   {
      if(*p == c) return p;
      p++;
   }
   return 0;
}

/********************** Function memset ************************************/

void * memset(str, c, l)
void * str;
int c;
size_t l;
{
   register char *s1=str;
   while(l-->0) *s1++ = c;
   return str;
}

/********************** Function memcmp ************************************/

int memcmp(s, d, l)
const void *s, *d;
size_t l;
{
   register const char *s1=d, *s2=s;
   register char c1=0, c2=0;
   while(l-- > 0)
      if( (c1= *s1++) != (c2= *s2++) )
         break;
   return c1-c2;
}

/********************** Function memmove ************************************/

void *
memmove(d, s, l)
void *d, *s;
size_t l;
{
   register char *s1=d, *s2=s;
   /* This bit of sneakyness c/o Glibc, it assumes the test is unsigned */
   if( s1-s2 >= l ) return memcpy(d,s,l);

   /* This reverse copy only used if we absolutly have to */
   s1+=l; s2+=l;
   while(l-- >0)
      *(--s1) = *(--s2);
   return d;
}

/********************** Function movedata ***********************************/


/* NB There isn't any C version of this function ... */



/********************** THE END ********************************************/

