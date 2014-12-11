/* constants.h
 *
 * Kjetil Aamodt, 2005
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// CA size

#define ROWS    (1 << COORD_SIZE_Y) /* from Makefile */
#define COLUMNS (1 << COORD_SIZE_X) /* from Makefile */

// Program start address

#define PROGRAM_ADDRESS 0

// LUT values

#define EMPTY    0xffff0000
#define OR4      0xfffefffe
#define XOR4     0x69966996
#define AND4     0x10001000

#endif

