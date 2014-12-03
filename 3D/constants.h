/* constants.h
 *
 * Kjetil Aamodt, 2005
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// CA size

#define ROWS    (1 << COORD_SIZE_Y) /* from Makefile */
#define COLUMNS (1 << COORD_SIZE_X) /* from Makefile */
#define LAYERS  (1 << COORD_SIZE_Z) /* from Makefile */

// Program start address

#define PROGRAM_ADDRESS 0

// LUT values

#define EMPTY_LO    0x0000000000000000
#define EMPTY_HI    0xffffffffffffffff
#define OR4_LO      0xfffefffefffefffe
#define OR4_HI      0xfffefffefffefffe
#define XOR4_LO     0x6996699669966996
#define XOR4_HI     0x6996699669966996
#define AND4_LO     0x0001000100010001
#define AND4_HI     0x0001000100010001

#endif

