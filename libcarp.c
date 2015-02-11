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

#include "libcarp.h"
#include "communication.h"
#include "instructions.h"
#include "bitvector.h"

/* Constants */

#define BUFFER_SIZE (4096/4) /* One page of 32bit integers */

/* Buffers */

int buffer_send_pointer;

uint32_t buffer_send[BUFFER_SIZE];
uint32_t buffer_receive[BUFFER_SIZE];

/* System information */

bool matrix_wrap;
int matrix_width;
int matrix_height;
int matrix_depth;
int cell_state_bits;
int cell_type_bits;
int rule_amount;

/* Prototypes */

void process_information();
void print_information();

/* Control */

void carp_connect() {
  communication_open("0xDACA");
  read_information();
  process_information();
}

void process_information() {
  buffer_read(3);

  matrix_wrap = buffer_receive[0] & 0x01;

  matrix_width  = (buffer_receive[0] >>  8) & 0xFF;
  matrix_height = (buffer_receive[0] >> 16) & 0xFF;
  matrix_depth  = (buffer_receive[0] >> 24) & 0xFF;

  cell_state_bits = (buffer_receive[1] >> 0) & 0xFF;
  cell_type_bits  = (buffer_receive[1] >> 8) & 0xFF;

  rule_amount = buffer_receive[2];

#ifdef DEBUG
  print_information();
#endif
}

void print_information() {
  if (matrix_wrap) {
    printf("Matrix wrap: Enabled\n");
  }
  else {
    printf("Matrix wrap: Disabled\n");
  }
  printf("Matrix size: %dx%dx%d\n", matrix_width, matrix_height, matrix_depth);
  printf("Cell type bits: %d\n", cell_type_bits);
  printf("Cell state bits: %d\n", cell_state_bits);
  printf("Rule amount: %d\n", rule_amount);
  fflush(stdout);
}

void carp_disconnect() {
  communication_close();
}

void buffer_insert(uint32_t word) {
  buffer_send[buffer_send_pointer++] = word;

  if (buffer_send_pointer == BUFFER_SIZE) {
    buffer_flush();
  }
}

void buffer_read(int words) {
  buffer_flush();
  communication_receive(buffer_receive, words);
}

void buffer_flush() {
  communication_send(buffer_send, buffer_send_pointer);
  buffer_send_pointer = 0;
}

/* Instructions */

void nop() {
  buffer_insert(INSTRUCTION_NOP);
}

void read_information() {
  buffer_insert(INSTRUCTION_READ_INFORMATION);
}

void read_rule_vectors(uint16_t amount) {
  uint32_t instruction = INSTRUCTION_READ_RULE_VECTORS;

  instruction |= amount << 16;

  buffer_insert(instruction);
}

void read_rule_numbers() {
  buffer_insert(INSTRUCTION_READ_RULE_NUMBERS);
}

void read_state(uint32_t x, uint32_t y, uint32_t z) {
  /* TODO: Check x,y,z? */
  uint32_t instruction = INSTRUCTION_READ_STATE_ONE;

  instruction |= x <<  8;
  instruction |= y << 16;
  instruction |= z << 24;

  buffer_insert(instruction);
}

void read_states() {
  buffer_insert(INSTRUCTION_READ_STATE_ALL);
}

void read_type(uint32_t x, uint32_t y, uint32_t z) {
  /* TODO: Check x,y,z? */
  uint32_t instruction = INSTRUCTION_READ_TYPE_ONE;

  instruction |= x <<  8;
  instruction |= y << 16;
  instruction |= z << 24;

  buffer_insert(instruction);
}

void read_types() {
  buffer_insert(INSTRUCTION_READ_TYPE_ALL);
}

void write_lut(lut_t lut, uint32_t type) {
  uint32_t instruction = INSTRUCTION_WRITE_LUT;

  if (matrix_depth == 1) {
    instruction |= 2 << 5; /* Extra words */
  }
  else {
    instruction |= 5 << 5; /* Extra words */
  }

  buffer_insert(instruction);
  buffer_insert(type);

  if (matrix_depth == 1) {
    buffer_insert(lut.z_none);
  }
  else {
    buffer_insert(lut.z_none);
    buffer_insert(lut.z_positive);
    buffer_insert(lut.z_negative);
    buffer_insert(lut.z_positive_negative);
  }
}

void write_rule(rule_t rule, uint32_t index) {
  uint32_t instruction = INSTRUCTION_WRITE_RULE;

  int neighborhood_size = (matrix_depth = 1) ? 5 : 7;
  int rule_bits = (cell_type_bits + 1 + cell_state_bits + 1) * (neighborhood_size + 1);

  bitvector_t rule_bitvector = bitvector_create(rule_bits);

  int extra_words = 1 + rule_bitvector.number_of_parts;

  instruction |= extra_words << 5;

  buffer_insert(instruction);

  buffer_insert(index);

  bitvector_add(&rule_bitvector, rule.result.state_change, 1);
  bitvector_add(&rule_bitvector, rule.result.state_value, cell_state_bits);
  bitvector_add(&rule_bitvector, rule.result.type_change, 1);
  bitvector_add(&rule_bitvector, rule.result.type_value, cell_type_bits);

  bitvector_add(&rule_bitvector, rule.self.state_check, 1);
  bitvector_add(&rule_bitvector, rule.self.state_value, cell_state_bits);
  bitvector_add(&rule_bitvector, rule.self.type_check, 1);
  bitvector_add(&rule_bitvector, rule.self.type_value, cell_type_bits);

  bitvector_add(&rule_bitvector, rule.x_positive.state_check, 1);
  bitvector_add(&rule_bitvector, rule.x_positive.state_value, cell_state_bits);
  bitvector_add(&rule_bitvector, rule.x_positive.type_check, 1);
  bitvector_add(&rule_bitvector, rule.x_positive.type_value, cell_type_bits);

  bitvector_add(&rule_bitvector, rule.x_negative.state_check, 1);
  bitvector_add(&rule_bitvector, rule.x_negative.state_value, cell_state_bits);
  bitvector_add(&rule_bitvector, rule.x_negative.type_check, 1);
  bitvector_add(&rule_bitvector, rule.x_negative.type_value, cell_type_bits);

  bitvector_add(&rule_bitvector, rule.y_positive.state_check, 1);
  bitvector_add(&rule_bitvector, rule.y_positive.state_value, cell_state_bits);
  bitvector_add(&rule_bitvector, rule.y_positive.type_check, 1);
  bitvector_add(&rule_bitvector, rule.y_positive.type_value, cell_type_bits);

  bitvector_add(&rule_bitvector, rule.y_negative.state_check, 1);
  bitvector_add(&rule_bitvector, rule.y_negative.state_value, cell_state_bits);
  bitvector_add(&rule_bitvector, rule.y_negative.type_check, 1);
  bitvector_add(&rule_bitvector, rule.y_negative.type_value, cell_type_bits);

  if (matrix_depth > 1) {
    bitvector_add(&rule_bitvector, rule.z_positive.state_check, 1);
    bitvector_add(&rule_bitvector, rule.z_positive.state_value, cell_state_bits);
    bitvector_add(&rule_bitvector, rule.z_positive.type_check, 1);
    bitvector_add(&rule_bitvector, rule.z_positive.type_value, cell_type_bits);

    bitvector_add(&rule_bitvector, rule.z_negative.state_check, 1);
    bitvector_add(&rule_bitvector, rule.z_negative.state_value, cell_state_bits);
    bitvector_add(&rule_bitvector, rule.z_negative.type_check, 1);
    bitvector_add(&rule_bitvector, rule.z_negative.type_value, cell_type_bits);
  }

  for (int i = 0; i < rule_bitvector.number_of_parts; i++) {
    buffer_insert(rule_bitvector.vector_parts[i]);
  }

  bitvector_dispose(&rule_bitvector);
}

void set_rules_active(uint32_t amount) {
  /* TODO */
}

void fill_cells(bool state, uint32_t type) {
  uint32_t instruction = INSTRUCTION_FILL_CELLS;

  if (cell_type_bits > 16) {
    instruction |= 1 << 5; /* Extra words */
  }

  instruction |= state <<  8;
  instruction |= type  << 16;

  buffer_insert(instruction);

  if (cell_type_bits > 16) {
    buffer_insert(type >> 16);
  }
}

void write_state(uint32_t x, uint32_t y, uint32_t z, bool state) {
  uint32_t instruction = INSTRUCTION_WRITE_STATE_ONE;

  instruction |= 1 << 5; /* Extra words */

  instruction |= x <<  8;
  instruction |= y << 16;
  instruction |= z << 24;

  buffer_insert(instruction);
  buffer_insert(state);
};

void write_states(uint32_t x, uint32_t y, uint32_t z, bool states[]) {
  uint32_t instruction = INSTRUCTION_WRITE_STATE_ROW;

  int write_width = matrix_width;
  if (matrix_width * cell_state_bits > (256-32)) write_width = (256-32) / cell_state_bits;

  bitvector_t states_bitvector = bitvector_create(write_width * cell_state_bits);

  int extra_words = states_bitvector.number_of_parts;

  instruction |= extra_words << 5;

  instruction |= x <<  8;
  instruction |= y << 16;
  instruction |= z << 24;

  buffer_insert(instruction);

  for (int i = 0; i < write_width; i ++) {
    bitvector_add(&states_bitvector, states[i], cell_state_bits);
  }

  for (int i = 0; i < states_bitvector.number_of_parts; i++) {
    buffer_insert(states_bitvector.vector_parts[i]);
  }

  bitvector_dispose(&states_bitvector);
};

void write_type(uint32_t x, uint32_t y, uint32_t z, uint32_t type) {
  uint32_t instruction = INSTRUCTION_WRITE_TYPE_ONE;

  instruction |= 1 << 5; /* Extra words */

  instruction |= x <<  8;
  instruction |= y << 16;
  instruction |= z << 24;

  buffer_insert(instruction);
  buffer_insert(type);
};

void write_types(uint32_t x, uint32_t y, uint32_t z, uint32_t types[]) {
  uint32_t instruction = INSTRUCTION_WRITE_TYPE_ROW;

  int write_width = matrix_width;
  if (matrix_width * cell_type_bits > (256-32)) write_width = (256-32) / cell_type_bits;

  bitvector_t types_bitvector = bitvector_create(write_width * cell_type_bits);

  int extra_words = types_bitvector.number_of_parts;

  instruction |= extra_words << 5;

  instruction |= x <<  8;
  instruction |= y << 16;
  instruction |= z << 24;

  buffer_insert(instruction);

  for (int i = 0; i < write_width; i ++) {
    bitvector_add(&types_bitvector, types[i], cell_type_bits);
  }

  for (int i = 0; i < types_bitvector.number_of_parts; i++) {
    buffer_insert(types_bitvector.vector_parts[i]);
  }

  bitvector_dispose(&types_bitvector);
};

void devstep() {
  buffer_insert(INSTRUCTION_DEVSTEP);
}

void runstep(uint16_t amount) {
  uint32_t instruction = INSTRUCTION_RUNSTEP;

  instruction |= amount << 16;

  buffer_insert(instruction);
}

void config() {
  buffer_insert(INSTRUCTION_CONFIG);
}

void readback() {
  buffer_insert(INSTRUCTION_READBACK);
}

void swap_cell_buffers() {
  buffer_insert(INSTRUCTION_SWAP_CELL_BUFFERS);
}

/* TODO: Fitness, JumpEqual */

void store() {
  buffer_insert(INSTRUCTION_STORE);
}

void end() {
  buffer_insert(INSTRUCTION_END);
}

void jump(uint16_t address) {
  uint32_t instruction = INSTRUCTION_JUMP;

  instruction |= address <<  16;

  buffer_insert(instruction);
}

void break_out() {
  buffer_insert(INSTRUCTION_BREAK);
}

void counter_increment(uint8_t counter) {
  /* TODO */
}

void counter_reset(uint8_t counter) {
  /* TODO */
}

/* Utility functions */

void print_send_buffer() {
  printf("Send buffer contents:\n");
  for (int i = 0; i < buffer_send_pointer; i++) {
    printf("%02d: %08X\n", i, buffer_send[i]);
  }
  printf("\n");
  fflush(stdout);
}

void print_send_buffer_for_testbench() {
  char *indentation = "    ";
  for (int i = 0; i < buffer_send_pointer; i++) {
    printf("%swait for clock_period;\n", indentation);
    printf("%srx_buffer_write <= '1';\n", indentation);
    printf("%srx_buffer_data <= x\"%08X\";\n", indentation, buffer_send[i]);
    printf("\n");
  }
  fflush(stdout);
}
