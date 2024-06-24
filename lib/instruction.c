#include "instruction.h"

Instruction instructions[0x100] = {
        [0x00] = {INS_NOP, ADD_INP},
        [0x01] = {INS_LD, ADD_REG_N16, REG_BC},
        [0x02] = {INS_LD, ADD_REG, REG_BC, REG_A},
        [0x03] = {INS_INC, ADD_REG, REG_BC},
        [0x04] = {INS_INC, ADD_REG, REG_B}
};

Instruction *lookup_instruction(uint8_t opcode) {
    return &instructions[opcode];
}