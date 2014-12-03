/*****************************************************************************
 * Tests
 *
 * Various tests to verify the correctness of the platform
 *
 * Asbjørn Djupdal 2003
 * Kjetil Aamodt 2005
 * Ola Martin Tiseth Støvneng 2014
 * Per Thomas Lundal 2014
 *****************************************************************************/

#include "constants.h"
#include "sblocklib.h"
#include "read_print.h"
#include "rules.h"
#include "testrules.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

/* Protypes */

void reset();
void setStatesAlternating();
void printAllTypes();

void test_write_read_types();
void test_development();

/* Globals */

enum test_t {TEST_WRITE_READ_TYPES, TEST_DEVELOPMENT};
enum test_t test;

/* Main */

int main (int argc, char* argv[]) {
  if (argc > 1) {
    test = atoi(argv[1]);

    printf("Test: %i\n", test);
    fflush(stdout);

    openCard();

    reset();

    switch (test) {
    case TEST_WRITE_READ_TYPES:
      printf("Test Write Read Types\n");
      test_write_read_types();
      break;
    case TEST_DEVELOPMENT:
      printf("Test Development\n");
      test_development();
      break;
    default:
      break;
    }

    closeCard();
  }
  else {
    fprintf(stderr, "Arguments: <test>\n");
  }
  return 0;
}

/* Utility */

void reset() {
  clearBRAM(0, 0);
  resetDevCounter();
  flushDMA();
}

void setStatesAlternating() {
  for (int z = 0; z < (LAYERS / 2); z++) {
    for (int y = 0; y < (ROWS / 2); y++) {
      for (int x = 0; x < (COLUMNS / 16); x++) {
        writeStates(0x5555555555555555, x * 16, y * 2, z * 2);
      }
    }
  }
}

void printAllTypes() {
  for (int z = 0; z < LAYERS; z++) {
    printf("Layer %d:\n", z);
    readDMATypes();
    printTypes(stdout);
  }
}

/* Tests */

void test_write_read_types() {
  writeType(0, 0,0,0);
  writeType(1, 1,1,0);
  writeType(2, 2,2,0);
  writeType(3, 3,3,0);

  readTypes();

  flushDMA();

  printAllTypes();
}

void test_development() {
  writeRule(create_rule_1_to_2(), 0);
  writeRule(create_rule_2_to_3(), 1);
  setNumberOfLastRule(1);

  writeType(0, 0,0,0);
  writeType(1, 1,1,0);
  writeType(2, 2,2,0);
  writeType(3, 3,3,0);

  devstep();
  switchSBMs();

  readTypes();

  flushDMA();

  printAllTypes();
}

