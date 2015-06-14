/*****************************************************************************
 * Print
 *
 * Formats various data structures as text
 *
 * Asbjørn Djupdal 2003
 * Kjetil Aamodt 2005
 * Per Thomas Lundal 2015
 *****************************************************************************/

#ifndef PRINT_H
#define PRINT_H

#include "carp.h"
#include "matrix.h"

#include <stdint.h>
#include <stdbool.h>

void print_information(carp_info_t *info);
void print_matrix(matrix_t *matrix, uint8_t value_bits);
void print_rule_vectors(bool **rule_vectors, uint16_t vector_amount, uint32_t rule_amount);
void print_rule_vector(bool *rule_vector, uint32_t rule_amount);

void print_fitness_dft(carp_info_t *info, uint32_t *fitness_data);

#endif
