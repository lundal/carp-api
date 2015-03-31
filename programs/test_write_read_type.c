#include "testframework.cinclude"

void test() {
  printf("Test: Write and read type\n");

  int w = info->matrix_width;

  uint16_t types[w];
  for (int x = 0; x < w; x++) {
      types[x] = w % 1 << info->type_bits;
  }

  for (int x = 0; x < w; x++) {
    write_type(0,0,x, types[x]);
  }

  for (int x = 0; x < w; x++) {
    read_type(0,0,x);
  }

  for (int x = 0; x < w; x++) {
    assert_uint32(types[x], get_type());
  }
}
