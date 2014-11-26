/* sblocklib.c
 *
 * Sblocklib is an abstraction layer above FUSE API for controlling the
 * coprosessor 
 * 
 * Asbjorn Djupdal 2003
 * Kjetil Aamodt 2005
 * Ola Martin Tiseth Stoevneng 2014
 *
 * Stripped down to just generate a modelsim script file for the tests
 */

/* For information about functions in this file, see comments
   in sblocklib.h */

#include "sblocklib.h"
#include "../common/com.h"

static int bufferPtr;

uint64_t sendBuffer[BUFFER_SIZE];
uint64_t receiveBuffer[BUFFER_SIZE];

void openCard() {
  com_open();
}

void closeCard() {
  com_close();
}

void flushDMA() {
  com_send(sendBuffer, bufferPtr);
  bufferPtr = 0;
}

void insertDMA(uint64_t data) {
  sendBuffer[bufferPtr++] = data;

  if (bufferPtr == BUFFER_SIZE) {
    flushDMA();
  }
}

void readDMA(int words) {
  com_receive(receiveBuffer, words);
}

/*****************************************************************************/
/* instructions */

void readSums(uint32_t numberOfReadbacks){
  insertDMA(0x0000000000000014 | (numberOfReadbacks << 8));
}

void readUsedRules(void){
  insertDMA(0x0000000000000015);
}

void resetDevCounter(void){
  insertDMA(0x0000000000000017);
}

void jumpEqual(uint64_t value, uint32_t addr){
  insertDMA(0x0000000000000016 | (value << 48) | (addr << 8));
} 

void readRuleVector(uint32_t number){
  insertDMA(0x0000000000000018 | (number << 8));
}

void readFitness(void){
  insertDMA(0x0000000000000019);
}

void doFitness(uint32_t number){
  insertDMA(0x000000000000001A | (number << 8));
}

void store (uint32_t addr) {
  insertDMA (0x000000000000000e | (addr << 8));
}  

void end (void) {
  insertDMA (0x000000000000000f);
}

inline void nop (void) {
  insertDMA (0x0000000000000000);
}

void jump (uint32_t addr) {
  insertDMA (0x000000000000000c | (addr << 8));
}

void break_prg (void) {
  insertDMA (0x000000000000000d);
}

void switchSBMs (void) {
  insertDMA (0x0000000000000003);
}

void run (int cycles) {
  insertDMA (0x0000000000000009 | (cycles << 8));
}  

void writeLUTConv (uint64_t lut_lo, uint64_t lut_hi, uint64_t number) {
  insertDMA (0x0000000000000086 | (number << 32));
  insertDMA (0x0000000000000000 | lut_lo);
  insertDMA (0x0000000000000000 | lut_hi);
}

void config (void) {
  insertDMA (0x0000000000000007);
}

void readback (void) {
  insertDMA (0x0000000000000008);
}

void devstep (void) {
  insertDMA (0x000000000000000a);
}

void writeRule (struct RuleStruct rule, int number) {
  uint64_t rule_hi = 0L;
  uint64_t rule_lo = 0L;

  rule_hi |= (uint64_t)(rule.valid ? 1 : 0) << 63;
  rule_hi |= (uint64_t)(rule.type  ? 1 : 0) << 62;

  rule_hi |= (uint64_t)(rule.north.state_dc        ? 1 : 0) << 61;
  rule_hi |= (uint64_t)(rule.north.state_value     ? 1 : 0) << 60;
  rule_hi |= (uint64_t)(rule.north.type_dc         ? 1 : 0) << 59;
  rule_hi |= (uint64_t)(rule.north.type_value      & 0x1f)  << 51;

  rule_hi |= (uint64_t)(rule.south.state_dc      ? 1 : 0) << 50;
  rule_hi |= (uint64_t)(rule.south.state_value   ? 1 : 0) << 49;
  rule_hi |= (uint64_t)(rule.south.type_dc       ? 1 : 0) << 48;
  rule_hi |= (uint64_t)(rule.south.type_value    & 0x1f)  << 40;

  rule_hi |= (uint64_t)(rule.up.state_dc     ? 1 : 0) << 39;
  rule_hi |= (uint64_t)(rule.up.state_value  ? 1 : 0) << 38;
  rule_hi |= (uint64_t)(rule.up.type_dc      ? 1 : 0) << 37;
  rule_hi |= (uint64_t)(rule.up.type_value   & 0x1f)  << 29;

  rule_hi |= (uint64_t)(rule.down.state_dc     ? 1 : 0) << 28;
  rule_hi |= (uint64_t)(rule.down.state_value  ? 1 : 0) << 27;
  rule_hi |= (uint64_t)(rule.down.type_dc      ? 1 : 0) << 26;
  rule_hi |= (uint64_t)(rule.down.type_value   & 0x1f)  << 18;

  rule_hi |= (uint64_t)(rule.east.state_dc      ? 1 : 0) << 17;
  rule_hi |= (uint64_t)(rule.east.state_value   ? 1 : 0) << 16;
  rule_hi |= (uint64_t)(rule.east.type_dc       ? 1 : 0) << 15;
  rule_hi |= (uint64_t)(rule.east.type_value    & 0x1f)  << 7;

  rule_hi |= (uint64_t)(rule.west.state_dc      ? 1 : 0) << 6;
  rule_hi |= (uint64_t)(rule.west.state_value   ? 1 : 0) << 5;
  rule_hi |= (uint64_t)(rule.west.type_dc       ? 1 : 0) << 4;
  rule_hi |= (uint64_t)(rule.west.type_value/16 & 0x1f)  << 0;
  rule_lo |= (uint64_t)(rule.west.type_value%16 & 0x1f)  << 60;

  rule_lo |= (uint64_t)(rule.center.state_dc    ? 1 : 0) << 59;
  rule_lo |= (uint64_t)(rule.center.state_value ? 1 : 0) << 58;
  rule_lo |= (uint64_t)(rule.center.type_dc     ? 1 : 0) << 57;
  rule_lo |= (uint64_t)(rule.center.type_value  & 0x1f)  << 49;

  rule_lo |= (uint64_t)(rule.dont_change_state ? 1 : 0) << 48;

  if (rule.type == CHANGE) {
    rule_lo |= (uint64_t)(rule.result.change.state ? 1 : 0) << 47;
    rule_lo |= (uint64_t)(rule.result.change.type & 0x1f)   << 39;
  } else {
    rule_lo |= (uint64_t)(rule.result.copyFrom & 3) << 39;
  }

  insertDMA (0x000000000000004b | ((number & 0xff) << 8) | rule_lo);
  insertDMA (rule_hi);
}

void writeState (bool state, uint64_t x, uint64_t y, uint64_t z) {
  uint64_t one = 1;
  insertDMA (0x0000000000000004 | (state ? (one << 63) : 0) | (z << 24) | (y << 16) | (x << 8));
}

void writeStates (uint64_t states, uint64_t x, uint64_t y, uint64_t z) {
  insertDMA (0x0000000000000064 | (z << 24) | (y << 16) | (x << 8));
  insertDMA (0x0000000000000000 | states);
}

void readState (uint64_t x, uint64_t y, uint64_t z) {
  insertDMA (0x0000000000000005 | (z << 24) | (y << 16) | (x << 8));
}

void writeType (uint64_t type, uint64_t x, uint64_t y, uint64_t z) {
  insertDMA (0x0000000000000001 | (type << 32) | (z << 24) | (y << 16) | (x << 8));
}

void writeTypes (uint64_t types, uint64_t x, uint64_t y, uint64_t z) {
  insertDMA (0x0000000000000061 | (z << 24) | (y << 16) | (x << 8));
  insertDMA (0x0000000000000000 | types);
}

void readType (uint64_t x, uint64_t y, uint64_t z) {
  insertDMA (0x0000000000000002 | (z << 24) | (y << 16) | (x << 8));
}

void readStates (void) {
  insertDMA (0x0000000000000011);
}

void readTypes (void) {
  insertDMA (0x0000000000000010);
}

void setNumberOfLastRule (int numberOfLastRule) {
  insertDMA (0x0000000000000012 | (numberOfLastRule << 8));
}

void clearBRAM (uint64_t type, bool state) {
  insertDMA (0x0000000000000013 | (type << 32) | (state ? (1UL << 63) : 0));
}

void startDFT (uint64_t addr) {
  insertDMA (0x0000000000000038 | (addr << 32));
}

/*****************************************************************************/
/* utility functions */

void saveSendBuffer (char* modelsim) {
  FILE* modelsimfile;

  if(modelsim[0] != ' '){ //save buffer only if filename is given
    if ((modelsimfile = fopen (modelsim, "wb"))) {
      fprintf(modelsimfile, "run 250ns\n");
      for (int i = 0; i < bufferPtr; i++) {
        fprintf(modelsimfile, "force -freeze sim:/toplevel_tb/pciempty 0 0\n"
          "run 25ns\n"
          "force -drive sim:/toplevel_tb/pcidata 16#%08X%08X 0\n"
          "run 25ns\n"
          "force -freeze sim:/toplevel_tb/pciempty 1 0\n"
          "noforce sim:/toplevel_tb/pcidata\n"
          "run 200ns\n\n",
          (uint32_t)(sendBuffer[i]>>32), (uint32_t)(sendBuffer[i]));
        if ( (sendBuffer[i] & 0x000000000000003F) == 0x0000000000000013 ) {
          fprintf(modelsimfile, "run 1000ns\n\n");
        }
      }
      fprintf(modelsimfile,"run 200000ns\n\n");
      fclose (modelsimfile);
    }
    else{
      printf("Can't open modelsimfile\n");
    }
  }
}

