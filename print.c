#include "print.h"
#include "utility.h"
#include <stdio.h>

void print_information(carp_info_t *info) {
  printf("Matrix wrap: %s\n", (info->matrix_wrap) ? "Enabled" : "Disabled");
  printf("Matrix size: %dx%dx%d\n", info->matrix_width, info->matrix_height, info->matrix_depth);
  printf("State bits: %d\n", info->state_bits);
  printf("Type bits: %d\n", info->type_bits);
  printf("Counters: %dx%d\n", info->counter_amount, info->counter_bits);
  printf("Rule amount: %d\n", info->rule_amount);
  fflush(stdout);
}

void print_matrix(matrix_t *matrix, uint8_t value_bits) {
  char format[8];
  sprintf(format, "%%%dX ", div_ceil(value_bits, 4));

  for (int z = 0; z < matrix->depth; z++) {
    for (int y = 0; y < matrix->height; y++) {
      for (int x = 0; x < matrix->width; x++) {
        uint32_t value = matrix->values[z][y][x];
        if (value_bits == 1) {
          printf("%s ", (value) ? "x" : ".");
        }
        else {
          printf(format, value);
        }
      }
      /* End row */
      printf("\n");
    }
    /* End layer */
    printf("\n");
  }
  fflush(stdout);
}

void print_rule_vectors(bool **rule_vectors, uint16_t vector_amount, uint32_t rule_amount) {
  for (int i = 0; i < vector_amount; i++) {
    print_rule_vector(rule_vectors[i], rule_amount);
  }
}

void print_rule_vector(bool *rule_vector, uint32_t rule_amount) {
  bool first_hit = true;

  for (int i = 1; i < rule_amount; i++) {
    if (rule_vector[i]) {
      if (first_hit) {
        printf("%d", i);
        first_hit = false;
      }
      else {
        printf(", %d", i);
      }
    }
  }
  printf("\n");
  fflush(stdout);
}
