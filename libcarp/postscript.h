#ifndef POSTSCRIPT_H
#define POSTSCRIPT_H

#include "matrix.h"

#include <stdint.h>

void postscript_from_matrix_layer(matrix_t *matrix, uint8_t layer, uint32_t (*colorfunction)(uint32_t), char *filename);

#endif
