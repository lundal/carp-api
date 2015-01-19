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

void test_run(int test_number);

void reset();
void setStatesAlternating();
void printAllTypes();
void printAllStates();
void printRemainingData();

void test_write_read_type();
void test_write_read_types();
void test_write_read_state();
void test_write_read_states();
void test_clearBRAM();
void test_switch();
void test_development();
void test_config_readback();
void test_sblockmatrix();
void test_instruction_storage();
void test_development_counter();

/* Main */

int main (int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Arguments: <test number>\n");
    return 0;
  }

  openCard();

  test_run(atoi(argv[1]));

  closeCard();

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
    test_clearBRAM();
    break;
  case 5:
    test_switch();
    break;
  case 6:
    test_development();
    break;
  case 7:
    test_config_readback();
    break;
  case 8:
    test_sblockmatrix();
    break;
  case 9:
    test_instruction_storage();
    break;
  case 10:
    test_development_counter();
    break;
  default:
    printf("Unknown test %d\n", test_number);
    break;
  }

  printRemainingData();
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

void test_write_read_type() {
  printf("Test: Write and read type\n");
  printf("- Verifies instructions: writeType, readType\n");
  printf("- Expected output: 2, 3, 4, 5\n");

  writeType(2, 0,0);
  writeType(3, 1,1);
  writeType(4, 2,2);
  writeType(5, 3,3);

  readType(0,0);
  readType(1,1);
  readType(2,2);
  readType(3,3);

  flushDMA();
}

void test_write_read_types() {
  printf("Test: Write and read types\n");
  printf("- Verifies instructions: writeTypes, readTypes\n");
  printf("- Requires manual inspection!\n");

  writeType(5, 0,0);
  writeType(6, 1,1);
  writeType(7, 2,2);
  writeType(8, 3,3);

  writeTypes(0x0102030405060708, 0,4);

  readTypes();

  flushDMA();

  printAllTypes();
}

void test_write_read_state() {
  printf("Test: Write and read state\n");
  printf("- Verifies instructions: writeState, readState\n");
  printf("- Expected output: 1, 1, 0, 1\n");

  writeState(true, 0,0);
  writeState(true, 1,1);
  writeState(false, 2,2);
  writeState(true, 3,3);

  readState(0,0);
  readState(1,1);
  readState(2,2);
  readState(3,3);

  flushDMA();
}

void test_write_read_states() {
  printf("Test: Write and read states\n");
  printf("- Verifies instructions: writeStates, readStates\n");
  printf("- Requires manual inspection!\n");

  writeState(true, 0,0);
  writeState(true, 1,1);
  writeState(true, 2,2);
  writeState(true, 3,3);

  writeStates(0x1122334455667788, 0,4);

  readStates();

  flushDMA();

  printAllStates();
}

void test_clearBRAM() {
  printf("Test: Clear BRAM\n");
  printf("- Verifies instructions: clearBRAM\n");
  printf("- Expected output: All zeroes\n");

  writeState(true, 0,0);
  writeState(true, 1,1);
  writeState(true, 2,2);
  writeState(true, 3,3);

  writeType(5, 0,0);
  writeType(6, 1,1);
  writeType(7, 2,2);
  writeType(8, 3,3);

  clearBRAM(0,0);

  readStates();
  readTypes();

  flushDMA();

  printAllStates();
  printAllTypes();
}

void test_switch() {
  printf("Test: Switch BRAM\n");
  printf("- Verifies instructions: switch\n");
  printf("- Expected output: 0, 0, 1, 2\n");

  clearBRAM(2,1);

  switchSBMs();

  readState(0,0);
  readType(0,0);

  switchSBMs();

  readState(0,0);
  readType(0,0);

  flushDMA();
}

void test_development() {
  printf("Test: Development\n");
  printf("- Verifies instructions: devstep, writeRule, readRuleVector, readUsedRules\n");
  printf("- Requires manual inspection!\n");

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
  readUsedRules();

  flushDMA();

  printAllTypes();
}

void test_config_readback() {
  printf("Test: Config and readback\n");
  printf("- Verifies instructions: config, readback\n");
  printf("- Expected output: 1\n");

  writeState(true, 1,1);

  switchSBMs();

  config();
  readback();

  switchSBMs();

  readState(1,1);

  flushDMA();
}

void test_sblockmatrix() {
  /* Matrix:
   * 0 1 0
   * 0 + 0
   * 1 * 1
   * 0 1 0 */
  printf("Test: Sblockmatrix\n");
  printf("- Verifies instructions: run, writeLUTConv\n");
  printf("- Expected output: 1, 1, 0, 1, 1, 1\n");

  writeLUTConv(EMPTY, 0);
  writeLUTConv(AND4, 1);
  writeLUTConv(OR4, 2);

  writeType(2, 1,1);
  writeType(1, 1,2);

  writeState(true, 1,0);
  writeState(true, 0,2);
  writeState(true, 2,2);
  writeState(true, 1,3);

  switchSBMs();
  config();

  run(1);
  readback();

  switchSBMs();
  readState(1,0);
  readState(1,1);
  readState(1,2);

  run(1);
  readback();

  switchSBMs();
  readState(1,0);
  readState(1,1);
  readState(1,2);

  flushDMA();
}

void test_instruction_storage() {
  printf("Test: Instruction storage\n");
  printf("- Verifies instructions: store, end, jump, break\n");
  printf("- Expected output: 1, 1, 1\n");

  writeState(true, 1,1);

  store(PROGRAM_ADDRESS);
    readState(1,1);
    break_prg();
  end();

  jump(PROGRAM_ADDRESS);
  jump(PROGRAM_ADDRESS);
  jump(PROGRAM_ADDRESS);

  flushDMA();
}

void test_development_counter() {
  printf("Test: Development counter\n");
  printf("- Verifies instructions: jumpEqual, resetDevCounter (implicit)\n");
  printf("- Expected output: 1, 1, 1\n");

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
}

