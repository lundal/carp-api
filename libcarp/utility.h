/*****************************************************************************
 * Utility
 *
 * Various utility functions
 *
 * Per Thomas Lundal 2015
 *****************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdint.h>

int div_ceil(int dividend, int divisor);

int log2_floor(uint32_t value);
int log2_ceil(uint32_t value);

int bits(uint32_t amount);

uint32_t create_bitmask(uint32_t bits);

#endif
