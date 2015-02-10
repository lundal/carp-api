/*****************************************************************************
 * Communication interface
 *
 * An abstraction layer above the pci interface
 *
 * Per Thomas Lundal 2014
 *****************************************************************************/

#include "communication.h"
#include "pci.h"

#include <stdio.h>
#include <time.h>

/* Globals */

int resource0_file;
int resource1_file;
volatile uint32_t *resource0_base;
volatile uint32_t *resource1_base;

/* Main interface
 * Note: The vendor id is currently set do 0xDACA in the PCIe core */

void communication_open(char *vendor_id) {
  resource0_file = pci_resource_open("0xDACA", 0);
  resource1_file = pci_resource_open("0xDACA", 1);
  resource0_base = (uint32_t*)pci_resource_map(resource0_file);
  resource1_base = (uint32_t*)pci_resource_map(resource1_file);
}

void communication_close() {
  pci_resource_unmap((void*)resource0_base);
  pci_resource_unmap((void*)resource1_base);
  pci_resource_close(resource0_file);
  pci_resource_close(resource1_file);
}

void communication_send(uint32_t *buffer, int words) {
  while (communication_rx_space() < words) {
#ifdef DEBUG
    printf("Waiting for buffer space... (%d/%d)\n", communication_rx_space(), words);
    fflush(stdout);
#endif
    struct timespec time_to_sleep;
    time_to_sleep.tv_sec = 0;
    time_to_sleep.tv_nsec = 100 * 1000 * 1000;
    nanosleep(&time_to_sleep, NULL);
  }
  for (int i = 0; i < words; i++) {
    resource0_base[i] = buffer[i];
  }
}

void communication_receive(uint32_t *buffer, int words) {
  while (communication_tx_count() < words) {
#ifdef DEBUG
    printf("Waiting for buffer data... (%d/%d)\n", communication_tx_count(), words);
    fflush(stdout);
#endif
    struct timespec time_to_sleep;
    time_to_sleep.tv_sec = 0;
    time_to_sleep.tv_nsec = 100 * 1000 * 1000;
    nanosleep(&time_to_sleep, NULL);
  }
  for (int i = 0; i < words; i++) {
    buffer[i] = resource0_base[i];
  }
}

/* Special requests */

uint32_t communication_tx_count() {
  return resource1_base[0];
}

uint32_t communication_tx_space() {
  return resource1_base[1];
}

uint32_t communication_rx_count() {
  return resource1_base[2];
}

uint32_t communication_rx_space() {
  return resource1_base[3];
}

