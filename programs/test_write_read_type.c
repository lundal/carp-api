#include "testframework.cinclude"

void test() {
  printf("Test: Write and read type\n");

  int n = info->matrix_width;

  uint16_t types[n];
  for (int i = 0; i < n; i++) {
      types[i] = n % 1 << info->type_bits;
  }

  for (int i = 0; i < n; i++) {
    write_type(0,0,i, types[i]);
  }

  for (int i = 0; i < n; i++) {
    read_type(0,0,i);
  }

  for (int i = 0; i < n; i++) {
    assert_uint32(types[i], get_type());
  }
}
