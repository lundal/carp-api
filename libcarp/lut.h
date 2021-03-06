/*****************************************************************************
 * Lookup Table
 *
 * LUT format: (z-,z+,y-,y+,x-,x+,c)
 *
 * Per Thomas Lundal 2015
 *****************************************************************************/

#ifndef LUT_H
#define LUT_H

#include <stdint.h>

typedef struct {
  uint32_t z_positive_negative;
  uint32_t z_negative;
  uint32_t z_positive;
  uint32_t z_none;
} lut_t;

#define LUT_ZERO (lut_t){0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define LUT_SELF (lut_t){0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA}
#define LUT_AND4 (lut_t){0xFFFCFCC0, 0xFCC0C000, 0xFCC0C000, 0xC0000000}
#define LUT_AND6 (lut_t){0xC0000000, 0x00000000, 0x00000000, 0x00000000}
#define LUT_OR   (lut_t){0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFC}
#define LUT_XOR  (lut_t){0x3CC3C33C, 0xC33C3CC3, 0xC33C3CC3, 0x3CC3C33C}

#endif
