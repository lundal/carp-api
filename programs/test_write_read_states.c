#include "testframework.cinclude"

void test() {
  printf("Test: Write and read states\n");

  int spi = states_per_instruction();

  uint8_t states[spi];
  for (int x = 0; x < spi; x++) {
      states[x] = spi % 1 << info->state_bits;
  }

  write_states(0,0,0, states);

  read_states();

  matrix_t *state_matrix = get_states();

  for (int x = 0; x < spi; x++) {
    assert_uint32(states[x], state_matrix->values[0][0][x]);
  }

  matrix_dispose(state_matrix);
}
