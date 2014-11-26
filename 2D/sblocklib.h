/* sblocklib.h
 *
 * Sblocklib is an abstraction layer above FUSE API for controlling the
 * coprosessor 
 * 
 * Asbjorn Djupdal 2003
 * Kjetil Aamodt 2005
 */

#ifndef SBLOCKLIB_H
#define SBLOCKLIB_H

#include "rules.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/*****************************************************************************/
/* constants and globals */

/* size of DMA buffers
   this may be changed to whatever is suitable */
#define BUFFER_SIZE (4096/8) /* One page of 64bit integers */

/* memory used for transferring data from user-FPGA
   After a readDMA() this buffer should hold the read data */
extern uint64_t sendBuffer[BUFFER_SIZE];
extern uint64_t receiveBuffer[BUFFER_SIZE];

/*****************************************************************************/
/* - functions related to card control
   - forms an abstraction layer above the FUSE API
*/

/* select a card and open it */
void openCard (void);

/* close card after it is no longer used */
void closeCard (void);

/* configure user FPGA */
//bool configureCard (char* bitfilename);

/* - insert word into send buffer.
   - all words in send buffer will be sent at once when flushDMA() is called */
void insertDMA (uint64_t data);

/* send all data currently waiting in send buffer to card */
void flushDMA (void);

/* - transfer data from card and place in receiveBuffer
   - data in receiveBuffer will be overwritten
   - you must do a flushDMA() before calling this to make sure no
     instructions are pending in the send buffer
   - "words" is number of words to receive, and must be less than
     BUFFER_SIZE */
void readDMA (int words);

/*****************************************************************************/
/* - instructions
   - all these functions assembles an instruction for the coprocessor and
     places it into the send buffer
   - for more information about these instructions, see master thesis report
*/
void break_prg (void);
void clearBRAM (uint64_t type, bool state);
void config (void);
void devstep (void);
void end (void);
void jump (uint32_t addr);
void nop (void);
void readback (void);
void readState (uint64_t x, uint64_t y);
void readStates (void);
void readType (uint64_t x, uint64_t y);
void readTypes (void);
void readSums(uint32_t numberOfReadbacks);
void readUsedRules(void);
void resetDevCounter(void);
void jumpEqual(uint64_t value, uint32_t addr);
void readRuleVector(uint32_t number);
void readFitness(void);
void doFitness(uint32_t number);
void run (int cycles);
void setNumberOfLastRule (int numberOfLastRule);
void store (uint32_t addr);
void switchSBMs (void);
void writeLUTConv (uint64_t lut, uint64_t number);
void writeRule (struct RuleStruct rule, int number);
void writeState (bool state, uint64_t x, uint64_t y);
void writeStates (uint64_t states, uint64_t x, uint64_t y);
void writeType (uint64_t type, uint64_t x, uint64_t y);
void writeTypes (uint64_t types, uint64_t x, uint64_t y);
void startDFT (uint64_t addr);

/*****************************************************************************/
/* utility functions */

/* - write everything currently in send buffer to a ModelSim script file
   - useful for making complex ModelSim script testbenches */
void saveSendBuffer (char* modelsim);

#endif

