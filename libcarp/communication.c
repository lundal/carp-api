/*****************************************************************************
 * Communication interface
 *
 * An abstraction layer above the PCI interface.
 * Resource 0 is used for data and resource 1 is used for special requests.
 *
 * Per Thomas Lundal 2014
 *****************************************************************************/

#include "communication.h"
#include "pci.h"

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

/* Globals */

int resource0_file;
int resource1_file;
volatile uint32_t *resource0_base;
volatile uint32_t *resource1_base;

/* Main interface */

void communication_open(char *vendor_id) {
  resource0_file = pci_resource_open(vendor_id, 0);
  resource1_file = pci_resource_open(vendor_id, 1);
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
  int words_sent = 0;
  while (true) {
    int space = communication_rx_space();
    int words_left = words - words_sent;
    int words_to_send = (words_left < space) ? words_left : space;
    for (int i = words_sent; i < words_sent + words_to_send; i++) {
      resource0_base[i] = buffer[i];
    }
    words_sent += words_to_send;
    if (words_sent >= words) {
      return;
    }
#ifdef DEBUG
    printf("Waiting for buffer space... (%d/%d)\n", words_sent, words);
    fflush(stdout);
    struct timespec time_to_sleep;
    time_to_sleep.tv_sec = 0;
    time_to_sleep.tv_nsec = 100 * 1000 * 1000;
    nanosleep(&time_to_sleep, NULL);
#endif
#ifndef LOWLATENCY
    struct timespec time_to_sleep_2;
    time_to_sleep_2.tv_sec = 0;
    time_to_sleep_2.tv_nsec = 1000;
    nanosleep(&time_to_sleep_2, NULL);
#endif
  }
}

void communication_receive(uint32_t *buffer, int words) {
  int words_received = 0;
  while (true) {
    int count = communication_tx_count();
    int words_left = words - words_received;
    int words_to_send = (words_left < count) ? words_left : count;
    for (int i = words_received; i < words_received + words_to_send; i++) {
      buffer[i] = resource0_base[i];
    }
    words_received += words_to_send;
    if (words_received >= words) {
      return;
    }
#ifdef DEBUG
    printf("Waiting for buffer data... (%d/%d)\n", words_received, words);
    fflush(stdout);
    struct timespec time_to_sleep;
    time_to_sleep.tv_sec = 0;
    time_to_sleep.tv_nsec = 100 * 1000 * 1000;
    nanosleep(&time_to_sleep, NULL);
#endif
#ifndef LOWLATENCY
    struct timespec time_to_sleep_2;
    time_to_sleep_2.tv_sec = 0;
    time_to_sleep_2.tv_nsec = 1000;
    nanosleep(&time_to_sleep_2, NULL);
#endif
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

