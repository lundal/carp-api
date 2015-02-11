/*****************************************************************************
 * Bit Vector
 *
 * TODO
 *
 * Asbjørn Djupdal 2003
 * Kjetil Aamodt 2005
 * Ola Martin Tiseth Støvneng 2014
 * Per Thomas Lundal 2015
 *****************************************************************************/

#include "bitvector.h"
#include "utility.h"

#include <stdlib.h>

bitvector_t bitvector_create(uint32_t number_of_bits) {
  uint32_t number_of_parts = div_ceil(number_of_bits, 32);
  uint32_t *vector_parts = malloc(number_of_parts * sizeof(uint32_t));
  return (bitvector_t){vector_parts, number_of_parts, 0};
}

void bitvector_add(bitvector_t *vector, uint32_t data, uint32_t bits) {
  for (int i = 0; i < vector->number_of_parts; i++) {
    int start_bit = vector->number_of_bits;
    int shift_amount = start_bit - i*32;
    vector->vector_parts[i] |= (data << shift_amount);
  }
  vector->number_of_bits += bits;
}

void bitvector_dispose(bitvector_t *vector) {
  free(vector->vector_parts);
  vector->vector_parts = NULL;
  vector->number_of_parts = 0;
  vector->number_of_bits = 0;
}
