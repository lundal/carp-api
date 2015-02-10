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
SOURCES    = pci.c communication.c libcarp.c test.c
OBJECTS    = $(SOURCES:.c=.o)
EXECUTABLE = carp

###############################################################################

# Settings
SETTINGS = -DDEBUG

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

