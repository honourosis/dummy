#pragma once

#include "common.h"
#include "instruction.h"

typedef struct {
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t F;
    uint8_t H;
    uint8_t L;
    uint16_t SP;
    uint16_t PC;
} Registers;

typedef struct {
    uint8_t opcode;
    uint16_t operand_one;
    uint16_t operand_two;
    Instruction *instruction;
    Registers registers;
} CPU_context;

void cpu_step();

void set_8bit_register_val(Register reg, uint8_t val);

uint16_t get_register_val(Register reg);
