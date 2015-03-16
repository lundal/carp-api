#include "testframework.cinclude"

void test() {
  printf("Test: Fill Cells\n");
  printf("Instructions: fill_cells, read_states, read_types\n");
  printf("\n");

  int w = info->matrix_width;
  int h = info->matrix_height;
  int d = info->matrix_depth;

  fill_cells(1, 7);

  read_states();
  read_types();

  matrix_t *state_matrix = get_states();
  matrix_t *type_matrix = get_states();

  for (int z = 0; z < d; z++) {
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        assert_uint32(1, state_matrix->values[z][y][x]);
        assert_uint32(7, type_matrix->values[z][y][x]);
      }
    }
  }

  matrix_dispose(state_matrix);
  matrix_dispose(type_matrix);
}
