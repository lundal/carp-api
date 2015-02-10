/*****************************************************************************
 * CARP Library
 *
 * An interface for controlling the coprocessor
 *
 * Asbjørn Djupdal 2003
 * Kjetil Aamodt 2005
 * Ola Martin Tiseth Støvneng 2014
 * Per Thomas Lundal 2015
 *****************************************************************************/

#ifndef LIBCARP_H
#define LIBCARP_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Constants */

#define BUFFER_SIZE (4096/4) /* One page of 32bit integers */

/* Buffers */

extern uint32_t buffer_send[BUFFER_SIZE];
extern uint32_t buffer_receive[BUFFER_SIZE];

/* Control */

void carp_connect();
void carp_disconnect();
void buffer_insert(uint32_t word);
void buffer_read(int words);
void buffer_flush();

/* Instructions */

void nop();
void get_information();
void get_rule_vectors(int amount);
void get_rule_numbers();

void read_state(int x, int y, int z);
void read_states();
void read_type(int x, int y, int z);
void read_types();

void write_lut();
void write_rule();
void set_rules_active(int amount);
void fill_cells(bool state, int type);

void write_state(int x, int y, int z, bool state);
void write_states(int x, int y, int z, bool states[]);
void write_type(int x, int y, int z, int type);
void write_types(int x, int y, int z, int types[]);

void devstep();
void runstep();
void config();
void readback();

void swap_cell_buffers();
/* TODO: Fitness, JumpEqual */

void store();
void end();

void jump();
void break_out();
void counter_increment(int counter);
void counter_reset(int counter);

/* Utility functions */

void print_send_buffer();
void print_send_buffer_for_testbench();

#endif
