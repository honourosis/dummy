#pragma once

#include "common.h"

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
    INS_EL
} Type;

typedef enum {
    COND_NZ,
    COND_Z,
    COND_NC,
    COND_C
} Condition;

typedef enum {
    ADD_INP, // in place
    ADD_REG,
    ADD_REG_REG,
    ADD_REG_N8,
    ADD_REG_N16,
    ADD_REG_A8,
    ADD_ADDR,
    ADD_REG_A16,
    ADD_NZ,
    ADD_NZ_A16,
    ADD_A16,
    ADD_A16_REG,
    ADD_Z_A16,
    ADD_Z,
    ADD_N8,
    ADD_E8
} Addressing;

typedef enum {
    FL_ZERO,
    FL_NSUB,
    FL_HALT,
    FL_CARRY
} Flag;

typedef enum {
    //r8
    REG_A,
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L,
    //r16
    REG_AF,
    REG_BC,
    REG_DE,
    REG_HL,
    REG_PC,
    REG_SP
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
