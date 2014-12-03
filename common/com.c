/*****************************************************************************
 * Communication interface
 *
 * An abstraction layer above the pci interface
 *
 * Per Thomas Lundal 2014
 *****************************************************************************/

#include "com.h"
#include "pci.h"

#include <stdio.h>
#include <unistd.h>

/* Globals */

int resource0_file;
int resource1_file;
volatile uint64_t *resource0_base;
volatile uint32_t *resource1_base;

/* Main interface
 * Note: The vendor id is currently set do 0xDACA in the PCIe core */

void com_open() {
  resource0_file = pci_resource_open("0xDACA", 0);
  resource1_file = pci_resource_open("0xDACA", 1);
  resource0_base = (uint64_t*)pci_resource_map(resource0_file);
  resource1_base = (uint32_t*)pci_resource_map(resource1_file);
}

void com_close() {
  pci_resource_unmap((void*)resource0_base);
  pci_resource_unmap((void*)resource1_base);
  pci_resource_close(resource0_file);
  pci_resource_close(resource1_file);
}

void com_send(uint64_t *buffer, int words) {
  while (com_rx_space() < words) {
    printf("Waiting for buffer space... (%d/%d)\n", com_rx_space(), words);
    fflush(stdout);
    sleep(1);
  }
  for (int i = 0; i < words; i++) {
    resource0_base[i] = buffer[i];
  }
}

void com_receive(uint64_t *buffer, int words) {
  while (com_tx_count() < words) {
    printf("Waiting for buffer data... (%d/%d)\n", com_tx_count(), words);
    fflush(stdout);
    sleep(1);
  }
  for (int i = 0; i < words; i++) {
    buffer[i] = resource0_base[i];
  }
}

/* Special requests
 * Note: The special request handler reports the number of words in the
 * communication buffers, which are 32 bit wide. Hence the divide by two. */

uint32_t com_tx_count() {
  return resource1_base[0] / 2;
}

uint32_t com_tx_space() {
  return resource1_base[1] / 2;
}

uint32_t com_rx_count() {
  return resource1_base[2] / 2;
}

uint32_t com_rx_space() {
  return resource1_base[3] / 2;
}

