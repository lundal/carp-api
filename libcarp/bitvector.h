/*****************************************************************************
 * Bit Vector
 *
 * Utility bit string builder
 *
 * Per Thomas Lundal 2015
 *****************************************************************************/

#ifndef BITVECTOR_H
#define BITVECTOR_H

#include <stdint.h>

typedef struct {
  uint32_t number_of_bits;
  uint32_t number_of_parts;
  uint32_t *parts;
} bitvector_t;

bitvector_t *bitvector_create(uint32_t max_bits);
void bitvector_add(bitvector_t *vector, uint32_t data, uint32_t bits);
void bitvector_dispose(bitvector_t *vector);

#endif
