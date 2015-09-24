# Do you want the slow-book version or the fast-book version?

FAST_BOOK = 1

# If you want fast-book, you need to give the name of the book file.

# For Frotz
BOOK_FILE = book.AUX

# C compiler settings.

CC = vc +z
CFLAGS = -O=3
INCLUDES = -Ilibc/include -Ic

# Inform settings.

ZVERSION = 5
IFLAGS = \
	\$$MAX_LABELS=10000 	\
	\$$MAX_ARRAYS=256 	\
	\$$MAX_ZCODE_SIZE=100000 \
	\$$MAX_STATIC_DATA=60000 \
	-v$(ZVERSION) 		\
	-ew~S~X~D 		\
	+include_path=,/usr/lib/inform

OBJS = \
	c/mscp.o		\
	libc/misc.o		\
	libc/stdio.o		\
	libc/printf.o		\
	libc/scanf.o		\
	libc/strcasecmp.o	\
	libc/strcspn.o		\
	libc/string.o		\
	libc/strncasecmp.o	\
	libc/strpbrk.o		\
	libc/strsep.o		\
	libc/strspn.o		\
	libc/strstr.o		\
	libc/strtok.o		\
	libc/atexit.o		\
	libc/atoi.o		\
	libc/atol.o		\
	libc/bsearch.o		\
	libc/crypt.o		\
	libc/ctype.o		\
	libc/getenv.o		\
	libc/getopt.o		\
	libc/itoa.o		\
	libc/lsearch.o		\
	libc/ltoa.o		\
	libc/ltostr.o		\
	libc/putenv.o		\
	libc/qsort.o		\
	libc/rand.o		\
	libc/setenv.o		\
	libc/strtol.o		\
	libc/malloc.o

ifeq ($(FAST_BOOK), 1)
OBJS := $(OBJS) book.hb
else
OBJS := $(OBJS) book.hi
endif

SRCS = \
	castles.inf		\
	c/system.s		\
	fileio.h		\
	texteffects.h		\
	objects.h		\
	genie.h			\
	chessboard.h		\
	history.h		\
	grammar.h

all: castles.z$(ZVERSION)

abbreviations:
	inform $(IFLAGS) -u castles.inf | grep Abbreviate > abbreviations.h

castles.z$(ZVERSION): release.h $(OBJS) $(SRCS)
	awk '{ print "release ", $$2 + 1, ";"; exit(0) }' < release.h > release.new
ifeq ($(FAST_BOOK), 1)
	echo "constant FAST_BOOK;" >> release.new
endif
	mv release.new release.h
	inform $(IFLAGS) -s castles.inf

clean:
	rm -f $(OBJS)
	rm -f book.dump book.hi book.hb
	rm -f castles.z$(ZVERSION) gameinfo.dbg

purge: clean
	rm -f $(BOOK_FILE)

book.hi: book.txt mkbook.awk
	awk -f mkbook.awk $< > $@

book.hb: $(BOOK_FILE) mktable.awk
	od -t u1 $(BOOK_FILE) > book.dump
	awk -f mktable.awk book.dump > $@

%.s %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -module-name=$(basename $(notdir $<))

