#include "carp.h"
#include "print.h"
#include "postscript.h"

carp_info_t *info;

void init() {
  rule_t grow_y_neg = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 1},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 1},
  };
  rule_t grow_y_pos = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 1},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 1},
  };
  rule_t grow_x_neg = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 1},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 1},
  };
  rule_t grow_x_pos = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 1},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 1},
  };
  rule_t change_1_to_2 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 1},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 2},
  };
  rule_t change_2_to_3 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 2},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 3},
  };

  int index = 0;

  write_rule(grow_y_neg, ++index);
  write_rule(grow_y_pos, ++index);
  write_rule(grow_x_neg, ++index);
  write_rule(grow_x_pos, ++index);
  write_rule(change_1_to_2, ++index);
  write_rule(change_2_to_3, ++index);

  set_rules_active(index);

  write_type(0,2,2, 1);
}

uint32_t colorfunction (uint32_t value) {
  if (value == 1) {
    return 0xFF6666;
  }
  if (value == 2) {
    return 0x88FF88;
  }
  if (value == 3) {
    return 0x66FFFF;
  }
  return 0xFFFFFF;
}

void demo() {
  printf("Demo: Development\n");
  printf("- Simple development using 6 rules and 4 types\n");

  init();

  for (int i = 0; i <= 3; i++) {
    read_types();

    char filename[20];
    sprintf(filename, "%02d.ps", i);

    matrix_t *type_matrix = get_types();
    print_matrix(type_matrix, info->type_bits);
    postscript_from_matrix_layer(type_matrix, 0, &colorfunction, filename);
    matrix_dispose(type_matrix);

    devstep();
    swap_cell_storage();
  }
}

int main() {
  info = carp_connect();
  carp_reset();
  demo();
  carp_disconnect();
  return 0;
}
