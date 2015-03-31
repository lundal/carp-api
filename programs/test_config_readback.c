#include "testframework.cinclude"

void test() {
  printf("Test: Config Readback\n");

  for (int i = 0; i < 4; i++) {
    write_state(0,i,i, 1);
  }

  swap_cell_buffers();

  config();
  readback();

  swap_cell_buffers();

  for (int i = 0; i < 4; i++) {
    read_state(0,i,i);
  }

  for (int i = 0; i < 4; i++) {
    assert_uint32(1, get_state());
  }
}
