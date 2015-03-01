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

bitvector_t *bitvector_create(uint32_t max_bits) {
  bitvector_t *vector = malloc(sizeof(bitvector_t));
  vector->number_of_bits = 0;
  vector->number_of_parts = div_ceil(max_bits, 32);
  vector->parts = calloc(vector->number_of_parts, sizeof(uint32_t));
  return vector;
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

  /* Prevent overflow */
  uint32_t ones = ~0;
  uint32_t mask = ones >> (32 - bits);
  data &= mask;

  for (int i = first_word; i <= last_word; i++) {
    int shift_amount = vector->number_of_bits - i*32;
    if (shift_amount > 0) {
      vector->parts[i] |= (data << shift_amount);
    }
    else {
      vector->parts[i] |= (data >> (-shift_amount));
    }
  }
  vector->number_of_bits += bits;
}

void bitvector_dispose(bitvector_t *vector) {
  free(vector->parts);
  free(vector);
}
