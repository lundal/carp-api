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

#include "sblocklib.h"
#include "../common/com.h"

/* Globals */

static int bufferPtr;

uint64_t sendBuffer[BUFFER_SIZE];
uint64_t receiveBuffer[BUFFER_SIZE];

/* Card control */

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

/* Instructions */

void readSums(uint32_t numberOfReadbacks){
  insertDMA(0x0000000000000014 | (numberOfReadbacks << 8));
}

void readUsedRules(){
  insertDMA(0x0000000000000015);
}

void resetDevCounter(){
  insertDMA(0x0000000000000017);
}

void jumpEqual(uint64_t value, uint32_t addr){
  insertDMA(0x0000000000000016 | (value << 48) | (addr << 8));
} 

void readRuleVector(uint32_t number){
  insertDMA(0x0000000000000018 | (number << 8));
}

void readFitness(){
  insertDMA(0x0000000000000019);
}

void doFitness(uint32_t number){
  insertDMA(0x000000000000001A | (number << 8));
}

void store(uint32_t addr) {
  insertDMA(0x000000000000000e | (addr << 8));
}  

void end() {
  insertDMA(0x000000000000000f);
}

void nop() {
  insertDMA(0x0000000000000000);
}

void jump(uint32_t addr) {
  insertDMA(0x000000000000000c | (addr << 8));
}

void break_prg() {
  insertDMA(0x000000000000000d);
}

void switchSBMs() {
  insertDMA(0x0000000000000003);
}

void run(int cycles) {
  insertDMA(0x0000000000000009 | (cycles << 8));
}  

void writeLUTConv(uint64_t lut, uint64_t number) {
  insertDMA(0x0000000000000046 | (number << 32));
  insertDMA(0x0000000000000000 | lut);
}

void config() {
  insertDMA(0x0000000000000007);
}

void readback() {
  insertDMA(0x0000000000000008);
}

void devstep() {
  insertDMA(0x000000000000000a);
}

void writeRule(struct RuleStruct rule, int number) {
  uint64_t rule_hi = 0L;
  uint64_t rule_lo = 0L;

  rule_hi |= (uint64_t)(rule.valid ? 1 : 0) << 63;
  rule_hi |= (uint64_t)(rule.type  ? 1 : 0) << 62;

  rule_hi |= (uint64_t)(rule.north.state_dc     ? 1 : 0) << 39;
  rule_hi |= (uint64_t)(rule.north.state_value  ? 1 : 0) << 38;
  rule_hi |= (uint64_t)(rule.north.type_dc      ? 1 : 0) << 37;
  rule_hi |= (uint64_t)(rule.north.type_value   & 0x1f)  << 29;

  rule_hi |= (uint64_t)(rule.south.state_dc     ? 1 : 0) << 28;
  rule_hi |= (uint64_t)(rule.south.state_value  ? 1 : 0) << 27;
  rule_hi |= (uint64_t)(rule.south.type_dc      ? 1 : 0) << 26;
  rule_hi |= (uint64_t)(rule.south.type_value   & 0x1f)  << 18;

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

  insertDMA(0x000000000000004b | ((number & 0xff) << 8) | rule_lo);
  insertDMA(rule_hi);
}

void writeState(bool state, uint64_t x, uint64_t y) {
  insertDMA(0x0000000000000004 | (state ? (1UL << 63) : 0) | (y << 16) | (x << 8));
}

void writeStates(uint64_t states, uint64_t x, uint64_t y) {
  insertDMA(0x0000000000000024 | (states << (64-16)) | (y << 16) | (x << 8));
}

void readState(uint64_t x, uint64_t y) {
  insertDMA(0x0000000000000005 | (y << 16) | (x << 8));
}

void writeType(uint64_t type, uint64_t x, uint64_t y) {
  insertDMA(0x0000000000000001 | (type << 32) | (y << 16) | (x << 8));
}

void writeTypes(uint64_t types, uint64_t x, uint64_t y) {
  insertDMA(0x0000000000000021 | (types << 32) | (y << 16) | (x << 8));
}

void readType(uint64_t x, uint64_t y) {
  insertDMA(0x0000000000000002 | (y << 16) | (x << 8));
}

void readStates() {
  insertDMA(0x0000000000000011);
}

void readTypes() {
  insertDMA(0x0000000000000010);
}

void setNumberOfLastRule(int numberOfLastRule) {
  insertDMA(0x0000000000000012 | (numberOfLastRule << 8));
}

void clearBRAM(uint64_t type, bool state) {
  insertDMA(0x0000000000000013 | (type << 32) | (state ? (1UL << 63) : 0));
}

void startDFT(uint64_t addr) {
  insertDMA(0x0000000000000038 | (addr << 32));
}

/* Utility functions */

void saveSendBuffer(char* modelsim) {
  FILE* modelsimfile;

  if(modelsim[0] != ' '){ /* save buffer only if filename is given */
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

