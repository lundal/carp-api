#include "testframework.cinclude"

void test() {
  printf("Test: Swap Cell Buffers\n");

  uint8_t state = 1;
  uint16_t type = 3;

  write_state(0,0,0, state);
  write_type(0,0,0, type);

  swap_cell_storage();

  read_state(0,0,0);
  read_type(0,0,0);

  assert_uint32(0, get_state());
  assert_uint32(0, get_type());

  swap_cell_storage();

  read_state(0,0,0);
  read_type(0,0,0);

  assert_uint32(state, get_state());
  assert_uint32(type, get_type());
}
