#ifndef POSTSCRIPT_H
#define POSTSCRIPT_H

#include "carp.h"
#include "matrix.h"

#include <stdint.h>

void postscript_from_matrix(matrix_t *matrix, uint32_t (*colorfunction)(uint32_t), char *filename);

#endif
