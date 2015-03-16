###############################################################################
#
# CARP Makefile
#
# Requires GNU make and GCC
#
# Asbjørn Djupdal 2003
# Kjetil Aamodt 2005
# Ola Martin Tiseth Støvneng 2014
# Per Thomas Lundal 2014
#
###############################################################################

# Directories
PROGRAMDIR = programs
LIBRARYDIR = libcarp

# Programs
PROGRAMS    = $(wildcard $(PROGRAMDIR)/*.c)
EXECUTABLES = $(patsubst %.c,%.carp,$(PROGRAMS))

# Library
SOURCES  = $(wildcard $(LIBRARYDIR)/*.c)
OBJECTS  = $(patsubst %.c,%.o,$(SOURCES))
LIBRARY  = $(LIBRARYDIR)/libcarp.a

###############################################################################

# Compiler flags
GCCFLAGS     = -Wall -g -pedantic -std=gnu11 -O3 -I$(LIBRARYDIR)
PROGRAMFLAGS = -L$(LIBRARYDIR) -lcarp -lm
LIBRARYFLAGS = #-DDEBUG -DTESTBENCH\
               -DWRAP=true -DWIDTH=8 -DHEIGHT=8 -DDEPTH=8\
               -DSTATE_BITS=1 -DTYPE_BITS=8\
               -DCOUNTER_AMOUNT=4 -DCOUNTER_BITS=16\
               -DRULE_AMOUNT=256

###############################################################################

.phony: all test clean

all: $(EXECUTABLES)

$(PROGRAMDIR)/%.carp: $(PROGRAMDIR)/%.c $(LIBRARY)
	gcc $< $(GCCFLAGS) $(PROGRAMFLAGS) -o $@

$(LIBRARY): $(OBJECTS)
	ar crs $@ $^

$(LIBRARYDIR)/%.o: $(LIBRARYDIR)/%.c
	gcc $(GCCFLAGS) $(LIBRARYFLAGS) -c $< -o $@

test: all
	for x in programs/test_*.carp; do sudo $$x; done

clean:
	rm -rf $(EXECUTABLES)
	rm -rf $(LIBRARY)
	rm -rf $(OBJECTS)

