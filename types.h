/* types.h
 *
 * Kjetil Aamodt, 2005
 */

#ifndef TYPES_H
#define TYPES_H

typedef unsigned int uint_t;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef uint8_t bool_t;

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
#define LAYERS  (1 << COORD_SIZE_Z) /* from Makefile */

#endif


// values used in LUT
#ifndef LUT
#define LUT

#define EMPTY_LO    0x0000000000000000
#define EMPTY_HI    0xffffffffffffffff
#define OR4_LO      0xfffefffefffefffe
#define OR4_HI      0xfffefffefffefffe
#define XOR4_LO     0x6996699669966996
#define XOR4_HI     0x6996699669966996
#define AND4_LO     0x0001000100010001
#define AND4_HI     0x0001000100010001

#endif

