# Makefile for sblocktest
#
# Requires: GNU make and other GNU utilities
#           gcc
#           BenERA header and library from NallaTech
#           The following variables set: COORD_SIZE_X COORD_SIZE_Y
#
# export COORD_SIZE_X and Y manually first
#COORD_SIZE_X=3 
#COORD_SIZE_Y=3
#COORD_SIZE_Z=3
#
# Asbjorn Djupdal 2003
# Kjetil Aamodt 2005

PROJECT_NAME = sblocktest

CC = gcc

CFLAGS = -g -O -Wall -DCOORD_SIZE_X=${COORD_SIZE_X} \
			-DCOORD_SIZE_Y=${COORD_SIZE_Y} \
			-DCOORD_SIZE_Z=${COORD_SIZE_Z}

LD = gcc
LDFLAGS =
LDLIBS = -ldl -lm

OBJECTS = sblocktest.o sblocklib.o read_print.o rules.o

$(PROJECT_NAME) : $(OBJECTS)

sblocktest.o : sblocktest.c sblocklib.h types.h 
read_print.o: read_print.c read_print.h types.h
sblocklib.o : sblocklib.c sblocklib.h types.h 
rules.o: rules.c rules.h

clean : 
	rm -rf *.o *.obj $(PROJECT_NAME) *.exp *.lib *.exe

cd:
	scp *.c *.h Makefile kjetila@stud3115.idi.ntnu.no:~/diplom/cd-rom/software/c-code;
	scp output/* kjetila@stud3115.idi.ntnu.no:~/diplom/cd-rom/software/output


