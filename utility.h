/*****************************************************************************
 * Utility
 *
 * Various utility functions
 *
 * Asbjørn Djupdal 2003
 * Kjetil Aamodt 2005
 * Ola Martin Tiseth Støvneng 2014
 * Per Thomas Lundal 2015
 *****************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdint.h>

int div_ceil(int dividend, int divisor);

int log2_floor(uint32_t value);
int log2_ceil(uint32_t value);

int bits(uint32_t amount);

#endif
