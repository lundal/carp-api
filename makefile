###############################################################################
#
# CARP Makefile
#
# Asbjørn Djupdal 2003
# Kjetil Aamodt 2005
# Ola Martin Tiseth Støvneng 2014
# Per Thomas Lundal 2014
#
###############################################################################

# Settings
COORD_SIZE_X = 3
COORD_SIZE_Y = 3
COORD_SIZE_Z = 3

# Source files
COMMON = common/pci.c
2D = 2D/sblocklib.c 2D/testrules.c 2D/read_print.c 2D/sblocktest.c
3D = 3D/sblocklib.c 3D/testrules.c 3D/read_print.c 3D/sblocktest.c

# Executables
EXECUTABLE_2D = carp_2d
EXECUTABLE_3D = carp_3d

###############################################################################

# Settings
SETTINGS = -DCOORD_SIZE_X=$(COORD_SIZE_X) \
           -DCOORD_SIZE_Y=$(COORD_SIZE_Y) \
           -DCOORD_SIZE_Z=$(COORD_SIZE_Z)
OBJECTS_2D = $(COMMON:.c=.o) $(2D:.c=.o)
OBJECTS_3D = $(COMMON:.c=.o) $(3D:.c=.o)

# Compiler
CC = gcc
CCFLAGS = -Wall -g -O3 $(SETTINGS)

# Linker
LD = gcc
LDFLAGS = -Wall -g -pedantic -lm

###############################################################################

.PHONY: all clean

all: $(EXECUTABLE_2D) $(EXECUTABLE_3D)

$(EXECUTABLE_2D): $(OBJECTS_2D)
	$(LD) $(LDFLAGS) $^ -o $@

$(EXECUTABLE_3D): $(OBJECTS_3D)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS_2D) $(OBJECTS_3D) $(EXECUTABLE_2D) $(EXECUTABLE_3D)

