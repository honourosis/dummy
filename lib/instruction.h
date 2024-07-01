#pragma once

#include "common.h"

/**
 * Any of the 8-bit registers (A, B, C, D, E, H, L) r8
 * Any of the general-purpose 16-bit registers (BC, DE, HL). r16
 * 8-bit integer constant. n8
 * 16-bit integer constant. n16
 * 8-bit offset (-128 to 127). e8
 * 3-bit unsigned integer constant (0 to 7). u3
 */

typedef enum {
    // un-prefixed instructions
    INS_NOP,
    INS_LD,
    INS_INC,
    INS_RLCA,
    INS_ADD,
    INS_DEC,
    INS_RRCA,
    INS_STOP,
    INS_RLA,
    INS_JR,
    INS_RRA,
    INS_DAA,
    INS_CPL,
    INS_SCF,
    INS_CCF,
    INS_HALT,
    INS_SUB,
    INS_SBC,
    INS_AND,
    INS_XOR,
    INS_OR,
    INS_CP,
    INS_RET,
    INS_POP,
    INS_JP,
    INS_CALL,
    INS_PUSH,
    INS_RST,
    INS_PREFIX,
    INS_LDH,
    INS_ADC,
    INS_RETI,
    INS_DI,
    INS_EI,
} Type;

typedef enum {
    COND_NONE,
    COND_Z,
    COND_NZ,
    COND_C,
    COND_NC
} Condition;

typedef enum {
    ADD_INP, // in place
    ADD_REG,
    ADD_MEM,
    ADD_REG_REG,
    ADD_MEM_REG,
    ADD_REG_MEM,
    ADD_REG_N8, // 8-bit data
    ADD_REG_N16, // little-endian 16-bit data
    ADD_HLI_REG, // increment HL afterwards
    ADD_REG_HLI,
    ADD_HLD_REG,
    ADD_REG_HLD,
    ADD_REG_A16, // little-endian 16-bit address
    ADD_A16, // little-endian 16-bit address
    ADD_A8_REG,
    ADD_A16_REG, // little-endian 16-bit address
    ADD_N8, // 8-bit data
    ADD_E8 // 8-bit signed
} Addressing;

typedef enum {
    FL_ZERO,
    FL_NSUB,
    FL_HALT,
    FL_CARRY
} Flag;

typedef enum {
    //r8
    REG_NONE,
    REG_A,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L,
    REG_SP,
    REG_PC,
    REG_AF,
    REG_BC,
    REG_DE,
    REG_HL
} Register;

typedef struct {
    Type type;
    Addressing addressing;
    Register reg_1;
    Register reg_2;
    Condition condition;
    Flag flags[];
} Instruction;

Instruction *lookup_instruction(uint8_t opcode);
