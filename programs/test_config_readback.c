#include "testframework.cinclude"

void test() {
  printf("Test: Config Readback\n");
  printf("Instructions: write_state, config, readback, read_states, swap_cell_buffers\n");
  printf("\n");

  for (int i = 0; i < 4; i++) {
    write_state(i,i,0, i % 2); // 0 1 0 1
  }

  swap_cell_buffers();

  config();
  readback();

  swap_cell_buffers();


  for (int i = 0; i < 4; i++) {
    read_state(i,i,0);
  }

  for (int i = 0; i < 4; i++) {
    assert_uint32(i % 2, get_state());
  }
}
