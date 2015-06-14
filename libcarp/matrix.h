/*****************************************************************************
 * Matrix
 *
 * Data structure for states, types and rule numbers
 *
 * Per Thomas Lundal 2015
 *****************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

typedef struct {
  uint8_t depth;
  uint8_t height;
  uint8_t width;
  uint32_t ***values;
} matrix_t;

matrix_t *matrix_create(uint8_t depth, uint8_t height, uint8_t width);
void matrix_dispose(matrix_t *matrix);

#endif
