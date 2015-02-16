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

# Files
SOURCES    = pci.c communication.c utility.c bitvector.c libcarp.c test.c
OBJECTS    = $(SOURCES:.c=.o)
EXECUTABLE = test

###############################################################################

# Settings
SETTINGS = #-DDEBUG -DTESTBENCH\
           -DWRAP=true -DWIDTH=8 -DHEIGHT=8 -DDEPTH=8\
           -DSTATE_BITS=1 -DTYPE_BITS=8 -DRULE_AMOUNT=256\

# Compiler
CC = gcc
CCFLAGS = -Wall -g -std=gnu11 -O3 $(SETTINGS)

# Linker
LD = gcc
LDFLAGS = -Wall -g -pedantic -lm

###############################################################################

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

