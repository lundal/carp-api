/*****************************************************************************
 * Utility
 *
 * Various utility functions
 *
 * Per Thomas Lundal 2015
 *****************************************************************************/

#include "utility.h"

#include <stdio.h>

int div_ceil(int dividend, int divisor) {
  return (dividend % divisor) ? dividend / divisor + 1 : dividend / divisor;
}

/* More verbose version of:
 * https://stackoverflow.com/questions/11376288/
 * fast-computing-of-log2-for-64-bit-integers */
int log2_floor(uint32_t value) {
  static const int hashtable[32] = {
     0,  9,  1, 10, 13, 21,  2, 29,
    11, 14, 16, 18, 22, 25,  3, 30,
     8, 12, 20, 28, 15, 17, 24,  7,
    19, 27, 23,  6, 26,  5,  4, 31
  };

  /* Set all bits after the first to one */
  value |= value >> 1;
  value |= value >> 2;
  value |= value >> 4;
  value |= value >> 8;
  value |= value >> 16;

  /* Calculate a unique 5-bit DeBrujin hash */
  uint32_t hash = (value * 0x07C4ACDD) >> 27;

  return hashtable[hash];
}

int log2_ceil(uint32_t value) {
  return log2_floor((value << 1) - 1);
}

int bits(uint32_t amount) {
  return log2_ceil(amount);
}

uint32_t create_bitmask(uint32_t bits) {
  return ~(uint32_t)((int32_t)(-1) << bits);
}
