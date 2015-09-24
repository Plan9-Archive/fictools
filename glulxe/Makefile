# Unix Makefile for Glulxe.

# To use this, you must set three variables. GLKINCLUDEDIR must be the 
# directory containing glk.h, glkstart.h, and the Make.library file.
# GLKLIBDIR must be the directory containing the library.a file.
# And GLKMAKEFILE must be the name of the Make.library file. Two
# sets of values appear below; uncomment one of them and change the
# directories appropriately.

GLKINCLUDEDIR = ../cheapglk
GLKLIBDIR = ../cheapglk
GLKMAKEFILE = Make.cheapglk

#GLKINCLUDEDIR = ../glkterm
#GLKLIBDIR = ../glkterm
#GLKMAKEFILE = Make.glkterm

#GLKINCLUDEDIR = ../xglk
#GLKLIBDIR = ../xglk
#GLKMAKEFILE = Make.xglk

#GLKINCLUDEDIR = ../remglk
#GLKLIBDIR = ../remglk
#GLKMAKEFILE = Make.remglk

# Pick a C compiler.
#CC = cc
CC = pcc

#OPTIONS = -g -Wall -Wmissing-prototypes -Wstrict-prototypes -Wno-unused -DOS_UNIX
OPTIONS =

include $(GLKINCLUDEDIR)/$(GLKMAKEFILE)

CFLAGS = $(OPTIONS) -I$(GLKINCLUDEDIR)
LIBS = -L$(GLKLIBDIR) $(GLKLIB) $(LINKLIBS) -lm

OBJS = main.8 files.8 vm.8 exec.8 funcs.8 operand.8 string.8 glkop.8 \
  heap.8 serial.8 search.8 accel.8 float.8 gestalt.8 osdepend.8 profile.8

all: glulxe

glulxe: $(OBJS) unixstrt.8
	$(CC) $(OPTIONS) -o glulxe $(OBJS) unixstrt.8 $(LIBS)

glulxdump: glulxdump.8
	$(CC) -o glulxdump glulxdump.8

$(OBJS) unixstrt.8: glulxe.h

exec.8 operand.8: opcodes.h
gestalt.8: gestalt.h

clean:
	rm -f *~ *.8 glulxe glulxdump profile-raw

