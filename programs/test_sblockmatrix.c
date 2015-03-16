#include "testframework.cinclude"

void test() {
  /* Matrix:
   * 0 1 0
   * 0 | 0
   * 1 & 1
   * 0 1 0 */

  printf("Test: Sblock Matrix\n");

  write_lut(LUT_SELF, 0);
  write_lut(LUT_AND4, 1);
  write_lut(LUT_OR,   2);

  write_type(1,1,0, 2);
  write_type(1,2,0, 1);

  write_state(1,0,0, 1);
  write_state(0,2,0, 1);
  write_state(2,2,0, 1);
  write_state(1,3,0, 1);

  swap_cell_buffers();
  config();

  runstep(1);
  readback();

  swap_cell_buffers();
  read_state(1,0,0);
  read_state(1,1,0);
  read_state(1,2,0);
  read_state(1,3,0);

  runstep(1);
  readback();

  swap_cell_buffers();
  read_state(1,0,0);
  read_state(1,1,0);
  read_state(1,2,0);
  read_state(1,3,0);

  assert_uint32(1, get_state());
  assert_uint32(1, get_state());
  assert_uint32(0, get_state());
  assert_uint32(1, get_state());

  assert_uint32(1, get_state());
  assert_uint32(1, get_state());
  assert_uint32(1, get_state());
  assert_uint32(1, get_state());
}
