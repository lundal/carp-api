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

#include "lut.h"
#include "rule.h"
#include "matrix.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Constants */

#define BUFFER_SIZE (4096/4) /* One page of 32bit integers */

/* Types */

typedef struct {
  bool    matrix_wrap;
  uint8_t matrix_width;
  uint8_t matrix_height;
  uint8_t matrix_depth;

  uint8_t state_bits;
  uint8_t type_bits;
  uint8_t counter_amount;
  uint8_t counter_bits;

  uint32_t rule_amount;
} carp_info_t;

/* Control */

carp_info_t *carp_connect();
void carp_disconnect();

/* Instructions */

void nop();
void read_information();
void read_rule_vectors(uint16_t amount);
void read_rule_numbers();

void read_state(uint32_t x, uint32_t y, uint32_t z);
void read_states();
void read_type(uint32_t x, uint32_t y, uint32_t z);
void read_types();

void write_lut(lut_t lut, uint32_t type);
void write_rule(rule_t rule, uint32_t index);
void set_rules_active(uint32_t amount);
void fill_cells(bool state, uint32_t type);

void write_state(uint32_t x, uint32_t y, uint32_t z, bool state);
void write_states(uint32_t x, uint32_t y, uint32_t z, bool states[]);
void write_type(uint32_t x, uint32_t y, uint32_t z, uint32_t type);
void write_types(uint32_t x, uint32_t y, uint32_t z, uint32_t types[]);

void devstep();
void runstep(uint16_t amount);
void config();
void readback();

void swap_cell_buffers();

void read_fitness();

void break_out();
void store(uint16_t address);
void end();

void jump(uint16_t address);
void jump_equal(uint16_t address, uint8_t counter, uint32_t value);
void counter_increment(uint8_t counter);
void counter_reset(uint8_t counter);

/* Get functions */

carp_info_t *get_information();

matrix_t *get_states();
matrix_t *get_types();
matrix_t *get_rule_numbers();

bool **get_rule_vectors(uint16_t amount);
bool *get_rule_vector();

void print_fitness_dft(uint16_t result_bits, uint16_t transform_size);

/* Utility print functions */

void print_send_buffer();
void print_send_buffer_for_testbench();
void print_remaining_data();

#endif
