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
  uint32_t *vector_parts = calloc(number_of_parts, sizeof(uint32_t));
  return (bitvector_t){vector_parts, number_of_parts, 0};
}

void bitvector_add(bitvector_t *vector, uint32_t data, uint32_t bits) {
  int first_bit = vector->number_of_bits;
  int last_bit = first_bit + bits - 1;
  int first_word = first_bit / 32;
  int last_word = last_bit / 32;

  /* Bounds check */
  if (last_word > vector->number_of_parts - 1) {
    last_word = vector->number_of_parts - 1;
  }

  for (int i = first_word; i <= last_word; i++) {
    int shift_amount = vector->number_of_bits - i*32;
    if (shift_amount > 0) {
      vector->vector_parts[i] |= (data << shift_amount);
    }
    else {
      vector->vector_parts[i] |= (data >> (-shift_amount));
    }
  }
  vector->number_of_bits += bits;
}

void bitvector_dispose(bitvector_t *vector) {
  free(vector->vector_parts);
  vector->vector_parts = NULL;
  vector->number_of_parts = 0;
  vector->number_of_bits = 0;
}
