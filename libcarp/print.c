#include "print.h"
#include "utility.h"
#include <stdio.h>

void print_information(carp_info_t *info) {
  printf("Information:\n");
  printf("- Matrix wrap: %s\n", (info->matrix_wrap) ? "Enabled" : "Disabled");
  printf("- Matrix size: %dx%dx%d\n", info->matrix_width, info->matrix_height, info->matrix_depth);
  printf("- State bits: %d\n", info->state_bits);
  printf("- Type bits: %d\n", info->type_bits);
  printf("- Counters: %dx%d\n", info->counter_amount, info->counter_bits);
  printf("- Rule amount: %d\n", info->rule_amount);
  printf("- Fitness id: %d\n", info->fitness_id);
  printf("- Fitness words: %d\n", info->fitness_words);
  printf("- Fitness params: 0x%04X\n", info->fitness_params);
  printf("\n");
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

void print_matrix_postscript(matrix_t *matrix, char *filename, uint8_t scale) {
  FILE *file = fopen(filename, "wb");

  fprintf(file, "%%!PC-Adobe-3.0 EPSF-3,0\n");
  fprintf(file, "%%%%BoundingBox: 0 0 %d %d \n", matrix->width*scale, matrix->height*scale);

  fprintf(file, "/cell {\n");
  fprintf(file, "%d 0 rlineto\n", scale);
  fprintf(file, "0 %d rlineto\n", scale);
  fprintf(file, "-%d 0 rlineto\n", scale);
  fprintf(file, "closepath\n");
  fprintf(file, "gsave\n");
  fprintf(file, "fill\n");
  fprintf(file, "grestore\n");
  fprintf(file, "0 0 0 setrgbcolor\n");
  fprintf(file, "stroke\n");
  fprintf(file, "} def\n");

  for (int z = 0; z < 1; z++) {
    for (int y = 0; y < matrix->height; y++) {
      for (int x = 0; x < matrix->width; x++) {
        uint32_t value = matrix->values[z][y][x];

        int red, blue, green;

        switch (value) {
          default:
          case 0:
            red = 1;
            green = 1;
            blue = 1;
            break;
          case 1:
          case 2:
          case 3:
          case 4:
          case 5:
          case 6:
          case 7:
          case 8:
            red = 0;
            green = 1;
            blue = 0;
            break;
          case 9:
            red = 1;
            green = 0;
            blue = 0;
            break;
          case 0xA:
          case 0xB:
          case 0xC:
          case 0xD:
            red = 0;
            green = 1;
            blue = 1;
            break;
        }

        fprintf(file, "newpath\n");
        fprintf(file, "%d %d moveto\n", x*scale, y*scale);
        fprintf(file, "%d %d %d setrgbcolor\n", red, green, blue);
        fprintf(file, "cell\n");
      }
    }
  }
  fclose(file);
}

void print_rule_vectors(bool **rule_vectors, uint16_t vector_amount, uint32_t rule_amount) {
  for (int i = 0; i < vector_amount; i++) {
    print_rule_vector(rule_vectors[i], rule_amount);
  }
}

void print_rule_vector(bool *rule_vector, uint32_t rule_amount) {
  bool first_hit = true;

  printf("RuleVector: ");
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

void print_fitness_dft(carp_info_t *info, uint32_t *fitness_data) {
  /* Parse parameters */
  int result_bits    = (info->fitness_params >> 0) & 0x3F;
  int transform_size = (info->fitness_params >> 6) & 0x3FF;

  int results_per_word = 32 / result_bits;
  uint32_t bitmask = create_bitmask(result_bits);

  printf("DFT(%d): ", transform_size);

  for (int w = 0; w < info->fitness_words; w++) {

    /* Get next word */
    uint32_t word = fitness_data[w];

    for (int r = 0; r < results_per_word; r++) {
      /* Use it like a shift register */
      uint32_t result = word & bitmask;
      word = word >> result_bits;

      if (w == 0 && r == 0) {
        printf("%d", result);
      }
      else {
        printf(", %d", result);
      }
    }
  }
  printf("\n");
  fflush(stdout);
}
