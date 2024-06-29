#pragma once

#include "common.h"
#include "instruction.h"

typedef struct {
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t H;
    uint8_t L;
    uint16_t SP;
    uint16_t PC;
} Registers;

typedef struct {
    Registers registers;
    Instruction *current_instruction;
} CPU;

void cpu_step();
