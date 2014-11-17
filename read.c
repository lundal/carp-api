#include "sblocklib.c"
#include "pci.c"

void main() {
  openCard();

  readState(0,0,0);
  readType(0,0,0);

  flushDMA();

  sleep(1);

  readDMA(2);

  printf("State: 0x%08X%08X\n", receiveBuffer[0] >> 32, receiveBuffer[0]);
  printf("Type: 0x%08X%08X\n", receiveBuffer[1] >> 32, receiveBuffer[1]);

  closeCard();
}
