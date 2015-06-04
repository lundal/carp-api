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

  write_type(0,1,1, 2);
  write_type(0,2,1, 1);

  write_state(0,0,1, 1);
  write_state(0,2,0, 1);
  write_state(0,2,2, 1);
  write_state(0,3,1, 1);

  swap_cell_storage();
  config();

  step(1);
  readback();

  swap_cell_storage();
  read_state(0,0,1);
  read_state(0,1,1);
  read_state(0,2,1);
  read_state(0,3,1);

  step(1);
  readback();

  swap_cell_storage();
  read_state(0,0,1);
  read_state(0,1,1);
  read_state(0,2,1);
  read_state(0,3,1);

  assert_uint32(1, get_state());
  assert_uint32(1, get_state());
  assert_uint32(0, get_state());
  assert_uint32(1, get_state());

  assert_uint32(1, get_state());
  assert_uint32(1, get_state());
  assert_uint32(1, get_state());
  assert_uint32(1, get_state());
}
