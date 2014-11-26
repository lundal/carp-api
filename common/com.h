/*****************************************************************************
 * Communication interface
 *
 * TODO
 *
 * Per Thomas Lundal 2014
 *****************************************************************************/

#ifndef COM_H
#define COM_H

#include <stdint.h>

/* Main interface */
void com_open();
void com_close();
void com_send(uint64_t *buffer, int words);
void com_receive(uint64_t *buffer, int words);

/* Special requests */
uint32_t com_tx_count();
uint32_t com_tx_space();
uint32_t com_rx_count();
uint32_t com_rx_space();

#endif

