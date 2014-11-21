/* sblocktest.c
 *
 * A testprogram for sblockmatrix project
 *
 * This runs same test experiments that is described in the master
 * thesis report.  
 *
 * Asbjorn Djupdal 2003
 * Kjetil Aamodt 2005
 * Ola Martin Tiseth Stoevneng 2014
 *
 * Stripped down to just generate a modelsim script file for the tests
 */

#include "sblocklib.h"
#include "read_print.h"
#include "types.h"
#include "rules.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

/*****************************************************************************/
/* protos */

/* write a specific state pattern to BRAM-0 */
void setStatesAlternating (void);

/* write program to co-processor */
void store_program_test_funct(void);
void store_program_test_rule(void);
void store_program_test_speed(void);
void store_program_test_fitness(void);
void store_program_test_fitness_speed_new(int runstep);

/*****************************************************************************/
/* globals */

enum test_t {TEST_FUNCT = 0, TEST_SPEED, TEST_RULE, TEST_FITNESS, TEST_FITNESS_SPEED_NEW};
enum test_t test;

int card;
char *modelsim;

/*****************************************************************************/
/* functions */

int main (int argc, char* argv[]) {
  card = 1; //default
  if(argc > 1){
    test = atoi(argv[1]);
    modelsim = argv[2];

    printf("Test: \t\t%i\nModelsim: \t%s\n\n", test, modelsim);
    fflush(stdout);
    
    /* write to lut conv table */
    writeLUTConv(EMPTY_LO, EMPTY_HI, 0); /* sblock type 0 is empty */
    writeLUTConv(XOR4_LO, XOR4_HI, 1);   /* sblock type 1 is XOR4 */
    writeLUTConv(OR4_LO, OR4_HI, 2);     /* sblock type 2 is OR4 */
    writeLUTConv(AND4_LO, AND4_HI, 3);   /* sblock type 3 is AND4 */

    /* write rules to rule storage */
    writeRule(create_rule_grow_south_1(), 0);
    writeRule(create_rule_grow_south_2(), 1);
    writeRule(create_rule_grow_east_1(), 2);
    writeRule(create_rule_grow_east_2(), 3);
    writeRule(create_rule_grow_north_1(), 4);
    writeRule(create_rule_grow_north_2(), 5);
    writeRule(create_rule_grow_west_1(), 6);
    writeRule(create_rule_grow_west_2(), 7);
    writeRule(create_rule_change_a_1(), 8);
    writeRule(create_rule_change_a_2(), 9);
    writeRule(create_rule_change_b_1(), 10);
    writeRule(create_rule_change_b_2(), 11);

    setNumberOfLastRule  (11);
    resetDevCounter();
    clearBRAM(0, 0);

    switch (test){
    case TEST_FUNCT:
      printf("Test Function\n");
      store_program_test_funct();
      saveSendBuffer (modelsim);
      break;
    case TEST_SPEED:
      printf("Test Speed\n");
      store_program_test_speed();
      saveSendBuffer (modelsim);
      break;
    case TEST_RULE:
      printf("Test Rule\n");
      store_program_test_rule();
      saveSendBuffer (modelsim);
      break;
    case TEST_FITNESS:
      printf("Test Fitness\n");
      store_program_test_fitness();
      saveSendBuffer(modelsim);
      break;
    case TEST_FITNESS_SPEED_NEW:
      printf("Test Fitness speed new\n");
      store_program_test_fitness_speed_new(1000);
      saveSendBuffer(modelsim);
      break;
    default:
      break;
    }

  } else fprintf (stderr, "Arguments: <test> <modelsim scriptfile>\n");
  return 0;
}

void setStatesAlternating (void) {
  int i, j, k;
  for (k = 0; k < (LAYERS / 2); k++) {
    for (i = 0; i < (ROWS / 2); i++) {
      for (j = 0; j < (COLUMNS / 16); j++) {
        writeStates (0x5555555555555555, j * 16, i * 2, k * 2);
      }
    }
  }
}

void store_program_test_rule(){
  switchSBMs();

  store(PROGRAM_ADDRESS);{
    config();
    readback();
    switchSBMs();
    readTypes();
    devstep();
    readUsedRules();
    
    jumpEqual(20, PROGRAM_ADDRESS + 30);

    jump(PROGRAM_ADDRESS);
  }end();

  store(PROGRAM_ADDRESS + 30);{
    readRuleVector(20);
    jump(PROGRAM_ADDRESS);
  }end();
  jump(PROGRAM_ADDRESS);
}

void store_program_test_funct(){
  /* set states */
  setStatesAlternating();
  
  /* set types */
  writeType (2, 4, 1, 1);

  /* change so that initial data is in BRAM-1 */
  switchSBMs();
  
  /* store program */
  store (PROGRAM_ADDRESS); {
    config();
    run (77);
    readback();
    
    switchSBMs();

    devstep();
    jumpEqual(10, PROGRAM_ADDRESS + 30);
    jump (PROGRAM_ADDRESS);
  }end();
  store (PROGRAM_ADDRESS + 30); {
    readTypes();
    readStates();
  }end();
  jump(PROGRAM_ADDRESS);
}

void store_program_test_speed(){
  /* set states */
  setStatesAlternating();
  
  /* set types */
  writeType (2, 4, 1, 0);

  /* change so that initial data is in BRAM-1 */
  switchSBMs();
  
  /* store program */
  store (PROGRAM_ADDRESS); {
    config();
    run (50000);
    readback();
    
    switchSBMs();

    readTypes();
    readStates();

    devstep();

    jump (PROGRAM_ADDRESS);
  }end();
  jump(PROGRAM_ADDRESS);
}

void store_program_test_fitness(void){
  /* set states */
  setStatesAlternating();
  /* set types */
  writeType (2, 4, 1, 0);
  /* change so that initial data is in BRAM-1 */
  switchSBMs();
  
  /* store program */
  store (PROGRAM_ADDRESS); {
    config();
    run (100);
    readback();
    
    switchSBMs();

    readStates();
    readSums(100);

    doFitness(100);
    readFitness();
    readFitness();
    readFitness();
    readFitness();
    devstep();

    jump (PROGRAM_ADDRESS);
  }end();
  jump(PROGRAM_ADDRESS);
}

void store_program_test_fitness_speed_new(int runstep){
  /* set states */
  setStatesAlternating();
  /* set types */
  writeType (2, 4, 1, 0);
  /* change so that initial data is in BRAM-1 */
  switchSBMs();
  
  /* store program */
  store (PROGRAM_ADDRESS); {
    config();
    run (runstep);
    readback();
    
    switchSBMs();

    doFitness(runstep);
    readFitness();
    readFitness();
    readFitness();
    readFitness();
    devstep();

    jump (PROGRAM_ADDRESS);
  }end();
  jump(PROGRAM_ADDRESS);
}

