#include "matrix.h"

#include <stdlib.h>

matrix_t *matrix_create(uint8_t depth, uint8_t height, uint8_t width) {
  matrix_t *matrix = malloc(sizeof(matrix_t));
  matrix->depth = depth;
  matrix->height = height;
  matrix->width = width;

  matrix->values = malloc(depth * sizeof(uint32_t**));
  for (int z = 0; z < depth; z++) {
    matrix->values[z] = malloc(height * sizeof(uint32_t*));
    for (int y = 0; y < height; y++) {
      matrix->values[z][y] = malloc(width * sizeof(uint32_t));
    }
  }

  return matrix;
}

void matrix_dispose(matrix_t *matrix) {
  /* Free memory */
  for (int z = 0; z < matrix->depth; z++) {
    for (int y = 0; y < matrix->height; y++) {
      free(matrix->values[z][y]);
    }
    free(matrix->values[z]);
  }
  free(matrix->values);
  free(matrix);
}
