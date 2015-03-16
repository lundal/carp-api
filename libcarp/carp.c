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

#include "carp.h"
#include "communication.h"
#include "instructions.h"
#include "bitvector.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Globals */

carp_info_t *info;

int buffer_send_pointer;

uint32_t buffer_send[BUFFER_SIZE];
uint32_t buffer_receive[BUFFER_SIZE];

/* Prototypes */

carp_info_t *infer_information();

void buffer_insert(uint32_t word);
void buffer_read(int words);
void buffer_flush();

void clear_remaining_data();

int entries_per_word(uint8_t entry_bits);
int words_per_row(uint8_t entry_bits);

matrix_t *get_matrix(uint8_t entry_bits);

/* Control */

carp_info_t *carp_connect() {
#ifdef TESTBENCH
  info = infer_information();
  return info;
#endif
  communication_open("0xDACA");
  clear_remaining_data();
  read_information();
  info = get_information();
  return info;
}

#ifdef TESTBENCH
carp_info_t *infer_information() {
  carp_info_t *info = malloc(sizeof(carp_info_t));

  /* From compiler flags */

  info->matrix_wrap = WRAP;
  info->matrix_width = WIDTH;
  info->matrix_height = HEIGHT;
  info->matrix_depth = DEPTH;

  info->state_bits = STATE_BITS;
  info->type_bits = TYPE_BITS;
  info->counter_amount = COUNTER_AMOUNT;
  info->counter_bits = COUNTER_BITS;

  info->rule_amount = RULE_AMOUNT;

  return info;
}
#endif

void carp_disconnect() {
  clear_remaining_data();
  free(info);
  communication_close();
}

void carp_reset() {
#ifdef DEBUG
  printf("Resetting...\n");
#endif

  /* Cell Buffer A */
  fill_cells(0, 0);

  /* SBlock Matrix */
  write_lut(LUT_SELF, 0);
  config();

  /* Clears RuleNumbers BRAM and Cell Buffer B */
  set_rules_active(0);
  devstep();

  /* Clears RuleVector, Live Count and Fitness Buffers
   * Must be last to assure that fitness is done processing */
  reset_buffers();

  buffer_flush();

#ifdef DEBUG
  printf("\n");
  fflush(stdout);
#endif
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
#ifdef TESTBENCH
  print_send_buffer_for_testbench();
  exit(0);
#else
  communication_send(buffer_send, buffer_send_pointer);
#endif
  buffer_send_pointer = 0;
}

void clear_remaining_data() {
  /* Flush buffer in case instructions are pending */
  buffer_flush();

#ifdef DEBUG
  printf("Clearing remaining data...\n");
#endif

  /* There has to be no new data for this long */
  struct timespec time_to_sleep;
  time_to_sleep.tv_sec = 0;
  time_to_sleep.tv_nsec = 100 * 1000 * 1000;

  int remaining;
#ifdef DEBUG
  int word = 0;
#endif

  do {
    /* Sleep */
    nanosleep(&time_to_sleep, NULL);
    /* Check for data */
    remaining = communication_tx_count();
    buffer_read(remaining);
#ifdef DEBUG
    for (int i = 0; i < remaining; i++) {
      printf("- %02X: %08X\n", word++, buffer_receive[i]);
    }
    fflush(stdout);
#endif
    /* Repeat if there was any */
  } while (remaining > 0);

#ifdef DEBUG
  printf("\n");
  fflush(stdout);
#endif
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

void read_state(uint8_t x, uint8_t y, uint8_t z) {
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

void read_type(uint8_t x, uint8_t y, uint8_t z) {
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

void write_lut(lut_t lut, uint16_t type) {
  uint32_t instruction = INSTRUCTION_WRITE_LUT;

  if (info->matrix_depth == 1) {
    instruction |= 2 << 5; /* Extra words */
  }
  else {
    instruction |= 5 << 5; /* Extra words */
  }

  buffer_insert(instruction);
  buffer_insert(type);

  if (info->matrix_depth == 1) {
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

  int neighborhood_size = (info->matrix_depth == 1) ? 5 : 7;
  int rule_bits = (info->type_bits + 1 + info->state_bits + 1) * (neighborhood_size + 1);

  bitvector_t *rule_bitvector = bitvector_create(rule_bits);

  int extra_words = 1 + rule_bitvector->number_of_parts;

  instruction |= extra_words << 5;

  buffer_insert(instruction);

  buffer_insert(index);

  bitvector_add(rule_bitvector, rule.result.state_change, 1);
  bitvector_add(rule_bitvector, rule.result.state_value, info->state_bits);
  bitvector_add(rule_bitvector, rule.result.type_change, 1);
  bitvector_add(rule_bitvector, rule.result.type_value, info->type_bits);

  bitvector_add(rule_bitvector, rule.self.state_check, 1);
  bitvector_add(rule_bitvector, rule.self.state_value, info->state_bits);
  bitvector_add(rule_bitvector, rule.self.type_check, 1);
  bitvector_add(rule_bitvector, rule.self.type_value, info->type_bits);

  bitvector_add(rule_bitvector, rule.x_positive.state_check, 1);
  bitvector_add(rule_bitvector, rule.x_positive.state_value, info->state_bits);
  bitvector_add(rule_bitvector, rule.x_positive.type_check, 1);
  bitvector_add(rule_bitvector, rule.x_positive.type_value, info->type_bits);

  bitvector_add(rule_bitvector, rule.x_negative.state_check, 1);
  bitvector_add(rule_bitvector, rule.x_negative.state_value, info->state_bits);
  bitvector_add(rule_bitvector, rule.x_negative.type_check, 1);
  bitvector_add(rule_bitvector, rule.x_negative.type_value, info->type_bits);

  bitvector_add(rule_bitvector, rule.y_positive.state_check, 1);
  bitvector_add(rule_bitvector, rule.y_positive.state_value, info->state_bits);
  bitvector_add(rule_bitvector, rule.y_positive.type_check, 1);
  bitvector_add(rule_bitvector, rule.y_positive.type_value, info->type_bits);

  bitvector_add(rule_bitvector, rule.y_negative.state_check, 1);
  bitvector_add(rule_bitvector, rule.y_negative.state_value, info->state_bits);
  bitvector_add(rule_bitvector, rule.y_negative.type_check, 1);
  bitvector_add(rule_bitvector, rule.y_negative.type_value, info->type_bits);

  if (info->matrix_depth > 1) {
    bitvector_add(rule_bitvector, rule.z_positive.state_check, 1);
    bitvector_add(rule_bitvector, rule.z_positive.state_value, info->state_bits);
    bitvector_add(rule_bitvector, rule.z_positive.type_check, 1);
    bitvector_add(rule_bitvector, rule.z_positive.type_value, info->type_bits);

    bitvector_add(rule_bitvector, rule.z_negative.state_check, 1);
    bitvector_add(rule_bitvector, rule.z_negative.state_value, info->state_bits);
    bitvector_add(rule_bitvector, rule.z_negative.type_check, 1);
    bitvector_add(rule_bitvector, rule.z_negative.type_value, info->type_bits);
  }

  for (int i = 0; i < rule_bitvector->number_of_parts; i++) {
    buffer_insert(rule_bitvector->parts[i]);
  }

  bitvector_dispose(rule_bitvector);
}

void set_rules_active(uint32_t amount) {
  uint32_t instruction = INSTRUCTION_SET_RULES_ACTIVE;

  if (info->rule_amount > (1<<16)) {
    instruction |= 1 << 5; /* Extra words */
  }

  instruction |= amount << 16;

  buffer_insert(instruction);

  if (info->rule_amount > (1<<16)) {
    buffer_insert(amount >> 16);
  }
}

void fill_cells(uint8_t state, uint16_t type) {
  uint32_t instruction = INSTRUCTION_FILL_CELLS;

  instruction |= state <<  8;
  instruction |= type  << 16;

  buffer_insert(instruction);
}

void write_state(uint8_t x, uint8_t y, uint8_t z, uint8_t state) {
  uint32_t instruction = INSTRUCTION_WRITE_STATE_ONE;

  instruction |= 1 << 5; /* Extra words */

  instruction |= x <<  8;
  instruction |= y << 16;
  instruction |= z << 24;

  buffer_insert(instruction);
  buffer_insert(state);
}

void write_states(uint8_t x, uint8_t y, uint8_t z, uint8_t states[]) {
  uint32_t instruction = INSTRUCTION_WRITE_STATE_ROW;

  int write_width = info->matrix_width;
  if (write_width * info->state_bits > (256-32)) write_width = (256-32) / info->state_bits;

  bitvector_t *states_bitvector = bitvector_create(write_width * info->state_bits);

  int extra_words = states_bitvector->number_of_parts;

  instruction |= extra_words << 5;

  instruction |= x <<  8;
  instruction |= y << 16;
  instruction |= z << 24;

  buffer_insert(instruction);

  for (int i = 0; i < write_width; i ++) {
    bitvector_add(states_bitvector, states[i], info->state_bits);
  }

  for (int i = 0; i < states_bitvector->number_of_parts; i++) {
    buffer_insert(states_bitvector->parts[i]);
  }

  bitvector_dispose(states_bitvector);
}

void write_type(uint8_t x, uint8_t y, uint8_t z, uint16_t type) {
  uint32_t instruction = INSTRUCTION_WRITE_TYPE_ONE;

  instruction |= 1 << 5; /* Extra words */

  instruction |= x <<  8;
  instruction |= y << 16;
  instruction |= z << 24;

  buffer_insert(instruction);
  buffer_insert(type);
}

void write_types(uint8_t x, uint8_t y, uint8_t z, uint16_t types[]) {
  uint32_t instruction = INSTRUCTION_WRITE_TYPE_ROW;

  int write_width = info->matrix_width;
  if (write_width * info->type_bits > (256-32)) write_width = (256-32) / info->type_bits;

  bitvector_t *types_bitvector = bitvector_create(write_width * info->type_bits);

  int extra_words = types_bitvector->number_of_parts;

  instruction |= extra_words << 5;

  instruction |= x <<  8;
  instruction |= y << 16;
  instruction |= z << 24;

  buffer_insert(instruction);

  for (int i = 0; i < write_width; i ++) {
    bitvector_add(types_bitvector, types[i], info->type_bits);
  }

  for (int i = 0; i < types_bitvector->number_of_parts; i++) {
    buffer_insert(types_bitvector->parts[i]);
  }

  bitvector_dispose(types_bitvector);
}

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

void reset_buffers() {
  buffer_insert(INSTRUCTION_RESET_BUFFERS);
}

void read_fitness() {
  buffer_insert(INSTRUCTION_READ_FITNESS);
}

void break_out() {
  buffer_insert(INSTRUCTION_BREAK);
}

void store(uint16_t address) {
  uint32_t instruction = INSTRUCTION_STORE;

  instruction |= address << 16;

  buffer_insert(instruction);
}

void end() {
  buffer_insert(INSTRUCTION_END);
}

void jump(uint16_t address) {
  uint32_t instruction = INSTRUCTION_JUMP;

  instruction |= address << 16;

  buffer_insert(instruction);
}

void jump_equal(uint16_t address, uint8_t counter, uint32_t value) {
  uint32_t instruction = INSTRUCTION_JUMP_EQUAL;

  instruction |= 1 << 5; /* Extra words */

  instruction |= counter << 8;
  instruction |= address << 16;

  buffer_insert(instruction);
  buffer_insert(value);
}

void counter_increment(uint8_t counter) {
  uint32_t instruction = INSTRUCTION_COUNTER_INCREMENT;

  instruction |= counter << 8;

  buffer_insert(instruction);
}

void counter_reset(uint8_t counter) {
  uint32_t instruction = INSTRUCTION_COUNTER_RESET;

  instruction |= counter << 8;

  buffer_insert(instruction);
}

/* Information functions */

int states_per_instruction() {
  int max = (256-32) / info->state_bits;
  return (max > info->matrix_width) ? info->matrix_width : max;
}

int types_per_instruction() {
  int max = (256-32) / info->type_bits;
  return (max > info->matrix_width) ? info->matrix_width : max;
}

int entries_per_word(uint8_t entry_bits) {
  int max = 32 / entry_bits;
  return (max > info->matrix_width) ? info->matrix_width : max;
}

int words_per_row(uint8_t entry_bits) {
  return div_ceil(info->matrix_width, entries_per_word(entry_bits));
}

/* Get functions */

carp_info_t *get_information() {
  carp_info_t *info = malloc(sizeof(carp_info_t));

  buffer_read(4);

  info->matrix_wrap   = (buffer_receive[0] >>  0) & 0x01;
  info->matrix_width  = (buffer_receive[0] >>  8) & 0xFF;
  info->matrix_height = (buffer_receive[0] >> 16) & 0xFF;
  info->matrix_depth  = (buffer_receive[0] >> 24) & 0xFF;

  info->state_bits     = (buffer_receive[1] >>  0) & 0xFF;
  info->type_bits      = (buffer_receive[1] >>  8) & 0xFF;
  info->counter_amount = (buffer_receive[1] >> 16) & 0xFF;
  info->counter_bits   = (buffer_receive[1] >> 24) & 0xFF;

  info->rule_amount = buffer_receive[2];

  info->fitness_id     = (buffer_receive[3] >>  0) & 0xFF;
  info->fitness_words  = (buffer_receive[3] >>  8) & 0xFF;
  info->fitness_params = (buffer_receive[3] >> 16) & 0xFFFF;

  return info;
}

uint8_t get_state() {
  buffer_read(1);
  return buffer_receive[0];
}

uint16_t get_type() {
  buffer_read(1);
  return buffer_receive[0];
}

matrix_t *get_states() {
  return get_matrix(info->state_bits);
}

matrix_t *get_types() {
  return get_matrix(info->type_bits);
}

matrix_t *get_rule_numbers() {
  return get_matrix(bits(info->rule_amount));
}

matrix_t *get_matrix(uint8_t entry_bits) {
  matrix_t *matrix = matrix_create(info->matrix_depth, info->matrix_height, info->matrix_width);

  int entries_per_word_i = entries_per_word(entry_bits);
  int words_per_row_i = words_per_row(entry_bits);
  int words_total = info->matrix_depth * info->matrix_height * words_per_row_i;
  int word_index = 0;

  buffer_read(words_total);

  uint32_t bitmask = create_bitmask(entry_bits);

  for (int z = 0; z < info->matrix_depth; z++) {
    for (int y = 0; y < info->matrix_height; y++) {
      for (int w = 0; w < words_per_row_i; w++) {

        /* Get next word */
        uint32_t word = buffer_receive[word_index++];

        for (int i = 0; i < entries_per_word_i; i++) {
          int x = w*entries_per_word_i + i;

          /* Do an out-of-bound check */
          if (x == info->matrix_width) {
            break;
          }

          /* Use it like a shift register */
          uint32_t entry = word & bitmask;
          word = word >> entry_bits;

          matrix->values[z][y][x] = entry;
        }
      }
    }
  }
  return matrix;
}

bool **get_rule_vectors(uint16_t amount) {
  bool **rule_vectors = malloc(amount * sizeof(bool*));
  for (int i = 0; i < amount; i++) {
    rule_vectors[i] = get_rule_vector();
  }
  return rule_vectors;
}

bool *get_rule_vector() {
  bool *rule_vector = malloc(info->rule_amount * sizeof(bool));

  int words = div_ceil(info->rule_amount, 32);

  buffer_read(words);

  for (int w = 0; w < words; w++) {

    /* Get word */
    uint32_t word = buffer_receive[w];

    for (int i = 0; i < 32; i++) {
      int index = w*32 + i;

      /* Do an out-of-bound check */
      if (index == info->rule_amount) {
        break;
      }

      /* Use it like a shift register */
      bool rule_hit = word & 1;
      word = word >> 1;

      rule_vector[index] = rule_hit;
    }
  }
  return rule_vector;
}

uint32_t *get_fitness() {
  uint32_t *fitness_data = malloc(info->fitness_words * sizeof(uint32_t));

  buffer_read(info->fitness_words);

  for (int w = 0; w < info->fitness_words; w++) {
    fitness_data[w] = buffer_receive[w];
  }

  return fitness_data;
}

/* Utility print functions */

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
