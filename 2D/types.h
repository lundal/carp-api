/* types.h
 *
 * Kjetil Aamodt, 2005
 */

#ifndef TYPES_H
#define TYPES_H

typedef unsigned char bool_t;
typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;
typedef unsigned long uint64_t;

#define FALSE 0
#define TRUE  (~FALSE)
//#define NULL 0L

#endif

// define sblock_matrix size and program start address
#ifndef PROGRAM
#define PROGRAM

#define PROGRAM_ADDRESS 0

#define ROWS    (1 << COORD_SIZE_Y) /* from Makefile */
#define COLUMNS (1 << COORD_SIZE_X) /* from Makefile */

#endif


// values used in LUT
#ifndef LUT
#define LUT

#define EMPTY    0xffff0000
#define OR4      0xfffefffe
#define XOR4     0x69966996
#define AND4     0x00010001

#endif

