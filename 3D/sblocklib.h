/*****************************************************************************
 * SBlock library
 *
 * An abstraction layer above the communication interface for controlling the
 * coprocessor
 *
 * Asbjørn Djupdal 2003
 * Kjetil Aamodt 2005
 * Ola Martin Tiseth Støvneng 2014
 * Per Thomas Lundal 2014
 *****************************************************************************/

#ifndef SBLOCKLIB_H
#define SBLOCKLIB_H

#include "rules.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Constants */

#define BUFFER_SIZE (4096/8) /* One page of 64bit integers */

/* Globals */

extern uint64_t sendBuffer[BUFFER_SIZE];
extern uint64_t receiveBuffer[BUFFER_SIZE];

/* Card control
 * Note: flushDMA() should be called before readDMA() to make sure any
 * remaining instructions in the buffer are sent to the card and executed.
 * Note: readDMA() will overwrite any previous data in the receiveBuffer. */

void openCard();
void closeCard();

void insertDMA(uint64_t data); /* Places data into sendBuffer */
void flushDMA(); /* Transfers everything in sendBuffer to card */
void readDMA(int words); /* Reads n words from card to receiveBuffer */

/* Instructions
 * Note: Instructions are buffered in the sendBuffer, a flushDMA() is required
 * to send them to the coprocessor for execution. */

void break_prg();
void clearBRAM(uint64_t type, bool state);
void config();
void devstep();
void end();
void jump(uint32_t addr);
void nop();
void readback();
void readState(uint64_t x, uint64_t y, uint64_t z);
void readStates();
void readType(uint64_t x, uint64_t y, uint64_t z);
void readTypes();
void readSums(uint32_t numberOfReadbacks);
void readUsedRules();
void resetDevCounter();
void jumpEqual(uint64_t value, uint32_t addr);
void readRuleVector(uint32_t number);
void readFitness();
void doFitness(uint32_t number);
void run(int cycles);
void setNumberOfLastRule(int numberOfLastRule);
void store(uint32_t addr);
void switchSBMs();
void writeLUTConv(uint64_t lut_lo, uint64_t lut_hi, uint64_t number);
void writeRule(struct RuleStruct rule, int number);
void writeState(bool state, uint64_t x, uint64_t y, uint64_t z);
void writeStates(uint64_t states, uint64_t x, uint64_t y, uint64_t z);
void writeType(uint64_t type, uint64_t x, uint64_t y, uint64_t z);
void writeTypes(uint64_t types, uint64_t x, uint64_t y, uint64_t z);
void startDFT(uint64_t addr);

/* Utility functions */

void printSendBuffer();
void printSendBufferForTestbench();
void saveSendBuffer(char* modelsim); /* Creates ModelSim file from sendBuffer */

#endif

