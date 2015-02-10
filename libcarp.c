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
    get_information();
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
        printf("Matrix wrap enabled\n");
    }
    else {
        printf("Matrix wrap disabled\n");
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
}

/* Instructions */

void nop() {
    buffer_insert(INSTRUCTION_NOP);
}

void get_information() {
    buffer_insert(INSTRUCTION_GET_INFORMATION);
}

void get_rule_vectors(int amount) {
    uint32_t instruction = INSTRUCTION_GET_RULE_VECTORS;

    instruction |= amount << 16;

    buffer_insert(instruction);
}

void get_rule_numbers() {
    buffer_insert(INSTRUCTION_GET_RULE_NUMBERS);
}

void read_state(int x, int y, int z) {
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

void read_type(int x, int y, int z) {
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

void write_lut() {
    /* TODO */
}

void write_rule() {
    /* TODO */
}

void set_rules_active(int amount) {
    /* TODO */
}

void fill_cells(bool state, int type) {
    uint32_t instruction = INSTRUCTION_WRITE_STATE_ONE;

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

void write_state(int x, int y, int z, bool state) {
    uint32_t instruction = INSTRUCTION_WRITE_STATE_ONE;

    instruction |= 1 << 5; /* Extra words */

    instruction |= x <<  8;
    instruction |= y << 16;
    instruction |= z << 24;

    buffer_insert(instruction);
    buffer_insert(state);
};

void write_states(int x, int y, int z, bool states[]) {
    uint32_t instruction = INSTRUCTION_WRITE_STATE_ROW;

    instruction |= 1 << 5; /* Extra words */

    instruction |= x <<  8;
    instruction |= y << 16;
    instruction |= z << 24;

    buffer_insert(instruction);

    /* TODO */
};

void write_type(int x, int y, int z, int type) {
    uint32_t instruction = INSTRUCTION_WRITE_TYPE_ONE;

    instruction |= 1 << 5; /* Extra words */

    instruction |= x <<  8;
    instruction |= y << 16;
    instruction |= z << 24;

    buffer_insert(instruction);
    buffer_insert(type);
};

void write_types(int x, int y, int z, int types[]) {
    uint32_t instruction = INSTRUCTION_WRITE_TYPE_ROW;

    instruction |= 1 << 5; /* Extra words */

    instruction |= x <<  8;
    instruction |= y << 16;
    instruction |= z << 24;

    buffer_insert(instruction);

    /* TODO */
};

void devstep() {
    buffer_insert(INSTRUCTION_DEVSTEP);
}

void runstep() {
    buffer_insert(INSTRUCTION_RUNSTEP);
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

void jump() {
    buffer_insert(INSTRUCTION_JUMP);
}

void break_out() {
    buffer_insert(INSTRUCTION_BREAK);
}

void counter_increment(int counter) {
    /* TODO */
}

void counter_reset(int counter) {
    /* TODO */
}
