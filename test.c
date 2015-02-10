/*****************************************************************************
 * Tests
 *
 * Various tests to verify the correctness of the platform
 *
 * Asbjørn Djupdal 2003
 * Kjetil Aamodt 2005
 * Ola Martin Tiseth Støvneng 2014
 * Per Thomas Lundal 2015
 *****************************************************************************/

#include "libcarp.h"

#include <stdio.h>
#include <stdlib.h>

/* Protypes */

void test_run(int test_number);

void reset();
void print_remaining_data();

void test_write_read_type();
void test_write_read_types();
void test_write_read_state();
void test_write_read_states();
void test_fill_cells();
void test_swap_cell_buffers();
void test_instruction_storage();
void test_config_readback();

/* Main */

int main (int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Arguments: <test number>\n");
    return 0;
  }

  carp_connect();

  test_run(atoi(argv[1]));

  carp_disconnect();

  return 0;
}

void test_run(int test_number) {
  reset();

  switch (test_number) {
  case 0:
    test_write_read_type();
    break;
  case 1:
    test_write_read_types();
    break;
  case 2:
    test_write_read_state();
    break;
  case 3:
    test_write_read_states();
    break;
  case 4:
    test_fill_cells();
    break;
  case 5:
    test_swap_cell_buffers();
    break;
  case 7:
    test_config_readback();
    break;
  case 9:
    test_instruction_storage();
    break;
  default:
    printf("Unknown test %d\n", test_number);
    break;
  }

  print_remaining_data();
}

/* Utility */

void reset() {
  fill_cells(0, 0);
  swap_cell_buffers();
  fill_cells(0, 0);
  config();
}

void print_remaining_data() {
  printf("Remaining data: (force cancel when waiting)\n");
  for (int i = 0; true; i++) {
    buffer_read(1);
    printf("%02d: %08X\n", i, buffer_receive[0]);
    fflush(stdout);
  }
}

/* Tests */

void test_write_read_type() {
  printf("Test: Write and read type\n");
  printf("- Verifies instructions: write_type, read_type\n");
  printf("- Expected output: 2, 3, 4, 5\n");

  write_type(0,0,0, 2);
  write_type(1,1,0, 3);
  write_type(2,2,0, 4);
  write_type(3,3,0, 5);

  read_type(0,0,0);
  read_type(1,1,0);
  read_type(2,2,0);
  read_type(3,3,0);
}

void test_write_read_types() {
  printf("Test: Write and read types\n");
  printf("- Verifies instructions: write_types, read_types\n");
  printf("- Requires manual inspection!\n");

  write_type(0,0,0, 5);
  write_type(1,1,0, 6);
  write_type(2,2,0, 7);
  write_type(3,3,0, 8);

  int types[] = {8,7,6,5,4,3,2,1};

  write_types(0,4,0, types);

  read_types();
}

void test_write_read_state() {
  printf("Test: Write and read state\n");
  printf("- Verifies instructions: write_state, read_state\n");
  printf("- Expected output: 1, 1, 0, 1\n");

  write_state(0,0,0, true);
  write_state(1,1,0, true);
  write_state(2,2,0, false);
  write_state(3,3,0, true);

  read_state(0,0,0);
  read_state(1,1,0);
  read_state(2,2,0);
  read_state(3,3,0);
}

void test_write_read_states() {
  printf("Test: Write and read states\n");
  printf("- Verifies instructions: write_states, read_states\n");
  printf("- Requires manual inspection!\n");

  write_state(0,0,0, true);
  write_state(1,1,0, true);
  write_state(2,2,0, true);
  write_state(3,3,0, true);

  bool states[] = {1,1,1,1,1,1,1,1};

  write_states(0,4,0, states);

  read_states();
}

void test_fill_cells() {
  printf("Test: Fill cells\n");
  printf("- Verifies instructions: fill_cells\n");
  printf("- Expected output: All zeroes\n");

  write_state(0,0,0, true);
  write_state(1,1,0, true);
  write_state(2,2,0, true);
  write_state(3,3,0, true);

  write_type(0,0,0, 5);
  write_type(1,1,0, 6);
  write_type(2,2,0, 7);
  write_type(3,3,0, 8);

  fill_cells(false, 0);

  read_states();
  read_types();

  /* TODO: Beautiful print */
}

void test_swap_cell_buffers() {
  printf("Test: Swap cell buffers\n");
  printf("- Verifies instructions: swap_cell_buffers\n");
  printf("- Expected output: 0, 0, 1, 2\n");

  fill_cells(1,2);

  swap_cell_buffers();

  read_state(0,0,0);
  read_type(0,0,0);

  swap_cell_buffers();

  read_state(0,0,0);
  read_type(0,0,0);
}

void test_config_readback() {
  printf("Test: Config and readback\n");
  printf("- Verifies instructions: config, readback\n");
  printf("- Expected output: 1\n");

  write_state(1,1,0, true);

  swap_cell_buffers();

  config();
  readback();

  swap_cell_buffers();

  read_state(1,1,0);
}

void test_instruction_storage() {
  printf("Test: Instruction storage\n");
  printf("- Verifies instructions: store, end, jump, break\n");
  printf("- Expected output: 1, 1, 1\n");

  write_state(1,1,0, true);

  store(0);
    read_state(1,1,0);
    break_out();
  end();

  jump(0);
  jump(0);
  jump(0);
}
