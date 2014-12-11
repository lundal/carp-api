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
void test_write_read_states();
void test_development();
void test_config_readback();
void test_sblockmatrix();
void test_instruction_storage();
void test_development_counter();

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
      test_write_read_states();
      break;
    case 2:
      test_development();
      break;
    case 3:
      test_config_readback();
      break;
    case 4:
      test_sblockmatrix();
      break;
    case 5:
      test_instruction_storage();
      break;
    case 6:
      test_development_counter();
      break;
    default:
      break;
    }

    closeCard();
  }
  else {
    fprintf(stderr, "Arguments: <test number>\n");
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
  for (int y = 0; y < (ROWS / 2); y++) {
    for (int x = 0; x < (COLUMNS / 8); x++) {
      writeStates(0x5555, x * 8, y * 2);
    }
  }
}

void printAllTypes() {
  readDMATypes();
  printTypes(stdout);
}

void printAllStates() {
  readDMAStates();
  printStates(stdout);
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

  writeType(0, 0,0);
  writeType(1, 1,1);
  writeType(2, 2,2);
  writeType(3, 3,3);

  writeTypes(0x3333333333333333, 0,4);

  readTypes();

  flushDMA();

  printAllTypes();

  printRemainingData();
}

void test_write_read_states() {
  printf("Test Write Read States\n");

  writeState(true, 0,0);
  writeState(true, 1,1);
  writeState(true, 2,2);
  writeState(true, 3,3);

  writeStates(0x3333333333333333, 0,4);

  readStates();

  flushDMA();

  printAllStates();

  printRemainingData();
}

void test_development() {
  printf("Test Development\n");

  writeRule(create_rule_1_to_2(), 0);
  writeRule(create_rule_2_to_3(), 1);
  setNumberOfLastRule(1);

  writeType(0, 0,0);
  writeType(1, 1,1);
  writeType(2, 2,2);
  writeType(3, 3,3);

  devstep();
  switchSBMs();

  readTypes();
  readRuleVector(1);

  flushDMA();

  printAllTypes();

  printRemainingData();
}

void test_config_readback() {
  /* Expected output:
   * 1 */
  printf("Test config and readback\n");

  writeState(true, 1,1);

  switchSBMs();

  config();
  readback();

  switchSBMs();

  readState(1,1);

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

  writeLUTConv(EMPTY, 0);
  writeLUTConv(AND4, 1);
  writeLUTConv(OR4, 2);

  writeType(1, 1,1);
  writeType(2, 1,2);

  writeState(true, 1,0);
  writeState(true, 0,2);
  writeState(true, 2,2);
  writeState(true, 1,3);

  switchSBMs();
  config();

  run(1);
  readback();

  switchSBMs();
  readState(1,1);
  readState(1,2);

  run(1);
  readback();

  switchSBMs();
  readState(1,1);
  readState(1,2);

  flushDMA();

  printRemainingData();
}

void test_instruction_storage() {
  /* Expected output:
   * 1
   * 1
   * 1 */
  printf("Test instruction storage\n");

  writeState(true, 1,1);

  store(PROGRAM_ADDRESS);
    readState(1,1);
    break_prg();
  end();

  jump(PROGRAM_ADDRESS);
  jump(PROGRAM_ADDRESS);
  jump(PROGRAM_ADDRESS);

  flushDMA();

  printRemainingData();
}

void test_development_counter() {
  /* Expected output:
   * 1
   * 1
   * 1 */
  printf("Test development counter\n");

  writeState(true, 1,1);

  store(PROGRAM_ADDRESS);
    readState(1,1);
    devstep();
    jumpEqual(3, PROGRAM_ADDRESS + 20);
    jump(PROGRAM_ADDRESS);
  end();

  store(PROGRAM_ADDRESS + 20);
    break_prg();
  end();

  jump(PROGRAM_ADDRESS);

  flushDMA();

  printRemainingData();
}

