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
void printAllStates();

void test_write_read_types();
void test_development();
void test_config_readback();
void test_sblockmatrix();

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
    case 2:
      test_config_readback();
      break;
    case 3:
      test_sblockmatrix();
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

void printAllStates() {
  for (int z = 0; z < LAYERS; z++) {
    printf("Layer %d:\n", z);
    readDMAStates();
    printStates(stdout);
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
  readRuleVector(1);

  flushDMA();

  printAllTypes();

  printRemainingData();
}

void test_config_readback() {
  printf("Test config and readback\n");

  writeState(true, 1,1,0);

  switchSBMs();

  config();
  readback();

  switchSBMs();

  readState(1,1,0);

  flushDMA();

  printRemainingData();
}

void test_sblockmatrix() {
  /* Matrix:
   * 010
   * 0+0
   * 1*1
   * 010
   * Expected output:
   * 1
   * 0
   * 1
   * 1 */
  printf("Test Sblockmatrix\n");

  writeLUTConv(EMPTY_LO, EMPTY_HI, 0);
  writeLUTConv(AND4_LO, AND4_HI, 1);
  writeLUTConv(OR4_LO, OR4_HI, 2);

  writeType(1, 1,1,0);
  writeType(2, 1,2,0);

  writeState(true, 1,0,0);
  writeState(true, 0,2,0);
  writeState(true, 2,2,0);
  writeState(true, 1,3,0);

  switchSBMs();
  config();

  run(1);
  readback();

  switchSBMs();
  readState(1,1,0);
  readState(1,2,0);

  run(1);
  readback();

  switchSBMs();
  readState(1,1,0);
  readState(1,2,0);

  flushDMA();

  printRemainingData();
}

