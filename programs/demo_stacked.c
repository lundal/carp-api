#include "carp.h"
#include "print.h"

carp_info_t *info;

lut_t lut_to_2D(lut_t lut) {
  lut.z_positive_negative = lut.z_none;
  lut.z_positive = lut.z_none;
  lut.z_negative = lut.z_none;
  return lut;
}

void swap_run_swap() {
  swap_cell_buffers();
  config();
  runstep(7);
  readback();
  swap_cell_buffers();
}

void print_states() {
  read_states();
  matrix_t *state_matrix = get_states();
  print_matrix(state_matrix, info->state_bits);
}

void demo() {
  printf("Demo: Stacked mode\n");
  printf("- Multiple 2D CA are run as layers within a 3D CA\n");

  if (info->matrix_depth == 1) {
    printf("ERROR: A matrix depth of 2 or greater is required\n");
    return;
  }

  write_lut(lut_to_2D(LUT_XOR), 0);

  printf("Same init state for each layer:\n");
  for (int z = 0; z < info->matrix_depth; z++) {
    for (int i = 0; i < 1; i++) {
      write_state(i,i,z, 1);
    }
  }

  swap_run_swap();
  print_states();

  printf("Different init state for each layer:\n");
  for (int z = 0; z < info->matrix_depth; z++) {
    for (int i = 0; i < z; i++) {
      write_state(i,i,z, 1);
    }
  }

  swap_run_swap();
  print_states();
}

int main() {
  info = carp_connect();
  carp_reset();
  demo();
  carp_disconnect();
  return 0;
}
