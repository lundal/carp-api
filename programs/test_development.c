#include "testframework.cinclude"

void test() {
  printf("Test: Development\n");
  printf("Instructions: write_rule, write_state, write_type devstep, read_state, read_type, read_rule_vectors, read_rule_numbers\n");
  printf("\n");

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

  for (int i = 0; i < 4; i++) {
    write_state(i,0,0, (i+1) % 2); // 1 0 1 0
    write_type(i,0,0, i);          // 0 1 2 3
  }

  devstep();
  swap_cell_buffers();

  for (int i = 0; i < 4; i++) {
    read_state(i,0,0);
    read_type(i,0,0);
  }

  assert_uint32(1, get_state());
  assert_uint32(1, get_state());
  assert_uint32(0, get_state());
  assert_uint32(0, get_state());

  assert_uint32(0, get_type());
  assert_uint32(2, get_type());
  assert_uint32(3, get_type());
  assert_uint32(3, get_type());

  read_rule_vectors(1);
  read_rule_numbers();

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
