/*****************************************************************************
 * Communication interface
 *
 * An abstraction layer above the pci interface
 *
 * Per Thomas Lundal 2014
 *****************************************************************************/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>

/* Main interface */
void communication_open();
void communication_close();
void communication_send(uint32_t *buffer, int words);
void communication_receive(uint32_t *buffer, int words);

/* Special requests */
uint32_t communication_tx_count();
uint32_t communication_tx_space();
uint32_t communication_rx_count();
uint32_t communication_rx_space();

#endif

