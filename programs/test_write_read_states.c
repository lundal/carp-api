#include "testframework.cinclude"

void test() {
  printf("Test: Write and read states\n");
  printf("Instructions: write_states, read_states\n");
  printf("\n");

  int n = states_per_instruction();
  uint8_t states[n];
  for (int i = 0; i < n; i++) {
      states[i] = n % 2;
  }

  write_states(0,0,0, states);

  read_states();

  matrix_t *state_matrix = get_states();

  for (int i = 0; i < n; i++) {
    assert_uint32(states[i], state_matrix->values[0][0][i]);
  }

  matrix_dispose(state_matrix);
}
