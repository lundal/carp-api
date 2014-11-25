###############################################################################
#
# CARP makefile
#
###############################################################################

# Settings
COORD_SIZE_X = 3
COORD_SIZE_Y = 3
COORD_SIZE_Z = 3

SETTINGS = -DCOORD_SIZE_X=$(COORD_SIZE_X) \
           -DCOORD_SIZE_Y=$(COORD_SIZE_Y) \
           -DCOORD_SIZE_Z=$(COORD_SIZE_Z)

# Compiler
CC = gcc
CCFLAGS = -Wall -g -O3 $(SETTINGS)
LDFLAGS = -Wall -g -pedantic -lm -lpthread

# Files
COMMON = common/pci.c
2D = 2D/sblocklib.c 2D/testrules.c 2D/read_print.c 2D/sblocktest.c
3D = 3D/sblocklib.c 3D/testrules.c 3D/read_print.c 3D/sblocktest.c
SRC = $(COMMON) $(2D) $(3D)
OBJ = $(SRC:.c=.o)

###############################################################################

.PHONY: all clean

# Compile everything
all: $(OBJ)

# Compile object file from code
%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

# Remove all generated files
clean:
	rm -rf $(OBJ)

