#include "carp.h"
#include "print.h"

carp_info_t *info;

void init() {
  // Main loop
  rule_t rule_create_1 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 8},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 1},
  };
  rule_t rule_create_2 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 1},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 2},
  };
  rule_t rule_create_3 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 2},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 3},
  };
  rule_t rule_create_4 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 3},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 4},
  };
  rule_t rule_create_5 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 4},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 5},
  };
  rule_t rule_create_6 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 5},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 6},
  };
  rule_t rule_create_7 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 6},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 7},
  };
  rule_t rule_create_8 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 7},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 8},
  };
  rule_t rule_create_9 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 2},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 6},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 8},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 4},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 9},
  };
  // A
  rule_t rule_create_A = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 1},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 0xA},
  };
  rule_t rule_create_7_from_A = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0xA},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 7},
  };
  rule_t rule_destroy_A = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0xA},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 0},
  };
  // B
  rule_t rule_create_B = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 3},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 0xB},
  };
  rule_t rule_create_1_from_B = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0xB},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 1},
  };
  rule_t rule_destroy_B = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0xB},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 0},
  };
  // C
  rule_t rule_create_C = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 5},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 0xC},
  };
  rule_t rule_create_3_from_C = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0xC},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 3},
  };
  rule_t rule_destroy_C = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0xC},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 0},
  };
  // D
  rule_t rule_create_D = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 7},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 0xD},
  };
  rule_t rule_create_5_from_D = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0xD},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 5},
  };
  rule_t rule_destroy_D = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 0xD},
    .result     = {.state_change = false, .state_value = 0, .type_change = true, .type_value = 0},
  };

  int index = 0;

  write_rule(rule_create_1, ++index);
  write_rule(rule_create_2, ++index);
  write_rule(rule_create_3, ++index);
  write_rule(rule_create_4, ++index);
  write_rule(rule_create_5, ++index);
  write_rule(rule_create_6, ++index);
  write_rule(rule_create_7, ++index);
  write_rule(rule_create_8, ++index);
  write_rule(rule_create_9, ++index);

  write_rule(rule_create_A, ++index);
  write_rule(rule_create_7_from_A, ++index);
  write_rule(rule_destroy_A, ++index);

  write_rule(rule_create_B, ++index);
  write_rule(rule_create_1_from_B, ++index);
  write_rule(rule_destroy_B, ++index);

  write_rule(rule_create_C, ++index);
  write_rule(rule_create_3_from_C, ++index);
  write_rule(rule_destroy_C, ++index);

  write_rule(rule_create_D, ++index);
  write_rule(rule_create_5_from_D, ++index);
  write_rule(rule_destroy_D, ++index);

  set_rules_active(index);

  write_type(0,4,4, 1);
}

void step() {
  devstep();

  swap_cell_buffers();

  read_types();
  matrix_t *type_matrix = get_types();
  print_matrix(type_matrix, info->type_bits);
  matrix_dispose(type_matrix);
}

void demo() {
  printf("Demo: Replication 1\n");
  printf("- Simple replicator using 21 rules and 12 types\n");

  init();

  for (int i = 0; i < 10; i++) {
    step();
  }
}

carp_info_t *info;
int main() {
  info = carp_connect();
  carp_reset();
  demo();
  carp_disconnect();
  return 0;
}
