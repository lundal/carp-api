#include "testframework.cinclude"
#include "print.h"

void test() {
  printf("Test: Development\n");

  rule_t rule_change_1_to_2_state_1 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 1},
    .result     = {.state_change = true, .state_value = 1, .type_change = true, .type_value = 2},
  };
  rule_t rule_change_2_to_3_state_0 = {
    .z_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .z_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .y_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_negative = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .x_positive = {.state_check = false, .state_value = 0, .type_check = false, .type_value = 0},
    .self       = {.state_check = false, .state_value = 0, .type_check = true,  .type_value = 2},
    .result     = {.state_change = true, .state_value = 0, .type_change = true, .type_value = 3},
  };

  write_rule(rule_change_1_to_2_state_1, 1);
  write_rule(rule_change_2_to_3_state_0, 2);

  set_rules_active(2);

  for (int x = 0; x < 4; x++) {
    write_state(0,0,x, (x+1) % 2); // 1 0 1 0
    write_type(0,0,x, x);          // 0 1 2 3
  }

  devstep();
  swap_cell_storage();

  for (int x = 0; x < 4; x++) {
    read_state(0,0,x);
  }
  for (int x = 0; x < 4; x++) {
    read_type(0,0,x);
  }

  read_rule_vectors(1);
  read_rule_numbers();

  assert_uint32(1, get_state());
  assert_uint32(1, get_state());
  assert_uint32(0, get_state());
  assert_uint32(0, get_state());

  assert_uint32(0, get_type());
  assert_uint32(2, get_type());
  assert_uint32(3, get_type());
  assert_uint32(3, get_type());

  bool *rule_vector = get_rule_vector();

  assert_uint32(1, rule_vector[0]);
  assert_uint32(1, rule_vector[1]);
  assert_uint32(1, rule_vector[2]);
  assert_uint32(0, rule_vector[3]);

  matrix_t *rule_number_matrix = get_rule_numbers();

  assert_uint32(0, rule_number_matrix->values[0][0][0]);
  assert_uint32(1, rule_number_matrix->values[0][0][1]);
  assert_uint32(2, rule_number_matrix->values[0][0][2]);
  assert_uint32(0, rule_number_matrix->values[0][0][3]);

  free(rule_vector);
  matrix_dispose(rule_number_matrix);
}
