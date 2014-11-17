#include "sblocklib.c"
#include "pci.c"

void main() {
  openCard();

  writeState(1, 0,0,0);
  writeType(11, 0,0,0);

  flushDMA();

  closeCard();
}
