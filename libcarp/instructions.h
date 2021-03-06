/*****************************************************************************
 * Instructions
 *
 * Contains instruction opcodes
 *
 * Per Thomas Lundal 2015
 *****************************************************************************/

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#define INSTRUCTION_NOP               0x00
#define INSTRUCTION_READ_INFORMATION  0x01
#define INSTRUCTION_READ_RULE_VECTORS 0x02
#define INSTRUCTION_READ_RULE_NUMBERS 0x03

#define INSTRUCTION_READ_STATE_ONE    0x04
#define INSTRUCTION_READ_STATE_ALL    0x05
#define INSTRUCTION_READ_TYPE_ONE     0x06
#define INSTRUCTION_READ_TYPE_ALL     0x07

#define INSTRUCTION_WRITE_LUT         0x08
#define INSTRUCTION_WRITE_RULE        0x09
#define INSTRUCTION_SET_RULES_ACTIVE  0x0A
#define INSTRUCTION_FILL_CELLS        0x0B

#define INSTRUCTION_WRITE_STATE_ONE   0x0C
#define INSTRUCTION_WRITE_STATE_ROW   0x0D
#define INSTRUCTION_WRITE_TYPE_ONE    0x0E
#define INSTRUCTION_WRITE_TYPE_ROW    0x0F

#define INSTRUCTION_DEVELOP           0x10
#define INSTRUCTION_STEP              0x11
#define INSTRUCTION_CONFIG            0x12
#define INSTRUCTION_READBACK          0x13

#define INSTRUCTION_SWAP_CELL_STORAGE 0x14
#define INSTRUCTION_RESET_BUFFERS     0x15

#define INSTRUCTION_READ_FITNESS      0x16

#define INSTRUCTION_BREAK             0x18
#define INSTRUCTION_STORE             0x1A
#define INSTRUCTION_END               0x1B

#define INSTRUCTION_JUMP              0x1C
#define INSTRUCTION_JUMP_EQUAL        0x1D
#define INSTRUCTION_COUNTER_INCREMENT 0x1E
#define INSTRUCTION_COUNTER_RESET     0x1F

#endif
