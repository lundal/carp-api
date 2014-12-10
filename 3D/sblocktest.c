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
#include "testrules.h"

#include <stdio.h>
#include <stdlib.h>

/* Protypes */

void reset();
void setStatesAlternating();
void printAllTypes();

void test_write_read_types();
void test_development();

/* Main */

int main (int argc, char* argv[]) {
  if (argc > 1) {
    int test = atoi(argv[1]);

    openCard();

    reset();

    switch (test) {
    case 0:
      test_write_read_types();
      break;
    case 1:
      test_development();
      break;
    default:
      break;
    }

    closeCard();
  }
  else {
    fprintf(stderr, "Arguments: <0-1>\n");
  }
  return 0;
}

/* Utility */

void reset() {
  clearBRAM(0, 0);
  switchSBMs();
  clearBRAM(0, 0);
  resetDevCounter();
  config();
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

void printRemainingData() {
  printf("Remaining data: (force cancel when waiting)\n");
  for (int i = 0; true; i++) {
    readDMA(1);
    printf("%02d: %08X%08X\n", i, (uint32_t)(receiveBuffer[0]>>32), (uint32_t)(receiveBuffer[0]));
    fflush(stdout);
  }
}

/* Tests */

void test_write_read_types() {
  printf("Test Write Read Types\n");

  writeType(0, 0,0,0);
  writeType(1, 1,1,0);
  writeType(2, 2,2,0);
  writeType(3, 3,3,0);

  readTypes();

  flushDMA();

  printAllTypes();
}

void test_development() {
  printf("Test Development\n");

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

  printRemainingData();
}

