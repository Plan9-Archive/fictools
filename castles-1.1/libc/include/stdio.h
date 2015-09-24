/* stdio.h
 * Ultra-simple stdio implementation for zlibc.
 * (C) 2001 David Given
 */

#include <fcntl.h>
#include <sys/types.h>
#include <malloc.h>

#ifndef __STDIO_H
#define __STDIO_H

typedef struct __stdio_file {
	int fd;
	unsigned eof:1;
	unsigned error:1;
} FILE;

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;
extern FILE* stdaux;

#define EOF (-1)

#define putc(c, fp) fputc(c, fp)
#define getc(fp) fgetc(fp)
#define putchar(c) putc((c), stdout)  
#define getchar() getc(stdin)
#define ungetc(c, stream) (EOF)

#define ferror(fp) ((fp)->error)
#define feof(fp) ((fp)->eof)

#define fileno(fp) ((fp)->fd)

extern int fputc(int c, FILE* fp);
extern int fgetc(FILE* fp);
extern int fputs(const char* s, FILE* fp);
extern int puts(const char* s);
#define fopen(filename, mode) (stdaux)
#define fclose(stream) (0)

extern int printf(const char* format, ...);
extern int fprintf(FILE* fp, const char* format, ...);
extern int sprintf(char* string, const char* format, ...);
#if 0
/* when you add or change fields here, be sure to change the initialization
 * in stdio_init and fopen */
struct __stdio_file {
  int fd; /* the file descriptor associated with the stream */
  unsigned char *bufstart; /* the start of the buffer */
  unsigned char *bufpos;   /* the next byte to write to or read from */
  unsigned char *bufread;  /* the end of data returned by last read() */
  unsigned char *bufend;   /* the end of the buffer; ie the byte after the last
                              malloc()ed byte */
  int buffer_mode;
#define _IONBF      0xB111 /* no buffering */
#define _IOLBF      0xB112 /* line buffering */
#define _IOFBF      0xB113 /* full buffering */
  int file_mode;
#define _MODE_READ  0xB121
#define _MODE_WRITE 0xB122
#define _MODE_RDWR  0xB124 /* used when a file is readwrite and is ord with
                              what's in the buffer now */
  unsigned char ungetted, ungetchar;
                            /* ungetted = 1 if there's data unread; else 0
                               ungetchar contains the character */
  int fc_eof:1;
  int fc_err:1;		/* eof and error conditions */
  int iotrans:1;	/* Translate \n -> \r\n on MSDOS */
};


typedef struct __stdio_file FILE;

#define BUFSIZ 256

extern FILE *stdin, *stdout, *stderr, *__stdsprintf;

/* The following macros are used for all access to the buffers.  If you
 * know the file is unbuffered, however, you may write to it directly, as
 * fputs.c does.  However, be aware that sprintf assumes that by setting
 * bufend to 0, no file writing will occur.  Also, since NO streams use
 * unbuffered mode by default and the function to change this behavior is
 * not implemented yet, I'm considering disallowing raw access at the cost
 * of having each byte of a string written individually.  However, that
 * IS what you're asking for with non-buffered mode.
 *
 * RDB: It's considered very bad form to use the raw read() & write()
 *      calls on the same files you use the stdio functions.
 */
#ifdef __MSDOS__
#define putc(c, fp) fputc(c, fp)
#define getc(fp) fgetc(fp)
#else
#define putc(c, stream)							\
 (((stream)->bufpos[0] = (c)),						\
  ((stream)->bufpos++),							\
  ((((stream)->bufpos == (stream)->bufend)				\
    ||((stream)->buffer_mode == _IONBF)					\
    ||(((stream)->buffer_mode == _IOLBF)				\
      && ((stream)->bufpos != (stream)->bufstart)			\
      && ((stream)->bufpos[-1] == '\n')))				\
        ? fflush(stream):0))

#define getc(stream)	\
  ((stream)->ungetted ? (((stream)->ungetted = 0), ((stream)->ungetchar)) : \
  (((stream)->bufpos == (stream)->bufread)?__ffillbuf(stream):		\
    (*(stream)->bufpos++)))

#endif

/* declare functions; not like it makes much difference without ANSI */
/* RDB: The return values _are_ important, especially if we ever use
        8086 'large' model
 */

#ifndef __P
#define __P(x) ()
#endif

int setvbuf __P((FILE*, char*, int, size_t));
int __ffillbuf __P((FILE*));
void __stdio_init __P((void));
int fclose __P((FILE*));
int fflush __P((FILE*));
int fgetc __P((FILE*));
char *fgets __P((char*, size_t, FILE*));
FILE *fopen __P((char*, char*));

int fputc __P((int, FILE*));
int fputs __P((__const char*, FILE*));
char *idealgetline __P((FILE*));
int puts __P((char*));

int printf __P ((__const char *, ...));
int fprintf __P ((FILE *, __const char *, ...));
int sprintf __P ((char *, __const char *, ...));

#ifndef SEEK_SET
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif
#endif

#endif /* __STDIO_H */
/* TODO: add scanf, fscanf */
