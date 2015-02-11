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

#ifndef BITVECTOR_H
#define BITVECTOR_H

#include <stdint.h>

typedef struct {
  uint32_t *vector_parts;
  uint32_t number_of_parts;
  uint32_t number_of_bits;
} bitvector_t;

bitvector_t bitvector_create(uint32_t number_of_bits);
void bitvector_add(bitvector_t *vector, uint32_t data, uint32_t bits);
void bitvector_dispose(bitvector_t *vector);

#endif
