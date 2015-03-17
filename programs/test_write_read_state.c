#include "testframework.cinclude"

void test() {
  printf("Test: Write and read state\n");

  int n = info->matrix_width;

  uint8_t states[n];
  for (int i = 0; i < n; i++) {
      states[i] = n % 1 << info->state_bits;
  }

  for (int i = 0; i < n; i++) {
    write_state(0,0,i, states[i]);
  }

  for (int i = 0; i < n; i++) {
    read_state(0,0,i);
  }

  for (int i = 0; i < n; i++) {
    assert_uint32(states[i], get_state());
  }
}
