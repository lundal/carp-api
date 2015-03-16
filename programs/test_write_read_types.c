#include "testframework.cinclude"

void test() {
  printf("Test: Write and read types\n");
  printf("Instructions: write_types, read_types\n");
  printf("\n");

  int n = types_per_instruction();

  uint16_t types[n];
  for (int i = 0; i < n; i++) {
      types[i] = n % 1 << info->type_bits;
  }

  write_types(0,0,0, types);

  read_types();

  matrix_t *type_matrix = get_types();

  for (int i = 0; i < n; i++) {
    assert_uint32(types[i], type_matrix->values[0][0][i]);
  }

  matrix_dispose(type_matrix);
}
