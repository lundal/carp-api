#include "testframework.cinclude"

void test() {
  printf("Test: Write and read state\n");

  int w = info->matrix_width;

  uint8_t states[w];
  for (int x = 0; x < w; x++) {
      states[x] = w % 1 << info->state_bits;
  }

  for (int x = 0; x < w; x++) {
    write_state(0,0,x, states[x]);
  }

  for (int x = 0; x < w; x++) {
    read_state(0,0,x);
  }

  for (int x = 0; x < w; x++) {
    assert_uint32(states[x], get_state());
  }
}
