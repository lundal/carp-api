#include "testframework.cinclude"

void test() {
  printf("Test: Write and read types\n");

  int tpi = types_per_instruction();

  uint16_t types[tpi];
  for (int x = 0; x < tpi; x++) {
      types[x] = tpi % 1 << info->type_bits;
  }

  write_types(0,0,0, types);

  read_types();

  matrix_t *type_matrix = get_types();

  for (int x = 0; x < tpi; x++) {
    assert_uint32(types[x], type_matrix->values[0][0][x]);
  }

  matrix_dispose(type_matrix);
}
