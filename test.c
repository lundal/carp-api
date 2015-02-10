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
void test_write_read_state();

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
  case 2:
    test_write_read_state();
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
  printf("- Verifies instructions: writeType, readType\n");
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

void test_write_read_state() {
  printf("Test: Write and read state\n");
  printf("- Verifies instructions: writeState, readState\n");
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