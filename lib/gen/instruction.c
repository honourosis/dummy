#include "../instruction.h"

Instruction instructions[0x100] = {
        [0x00] = {INS_NOP, ADD_INP},
        [0x01] = {INS_LD, ADD_REG_N16, REG_BC},
        [0x02] = {INS_LD, ADD_MEM_REG, REG_BC, REG_A},
        [0x03] = {INS_INC, ADD_REG, REG_BC},
        [0x04] = {INS_INC, ADD_REG, REG_B},
        [0x05] = {INS_DEC, ADD_REG, REG_B},
        [0x06] = {INS_LD, ADD_REG_N8, REG_B},
        [0x07] = {INS_RLCA, ADD_INP},
        [0x08] = {INS_LD, ADD_A16_REG, REG_NONE, REG_SP},
        [0x09] = {INS_ADD, ADD_REG_REG, REG_HL, REG_BC},
        [0x0A] = {INS_LD, ADD_REG_MEM, REG_A, REG_BC},
        [0x0B] = {INS_DEC, ADD_REG, REG_BC},
        [0x0C] = {INS_INC, ADD_REG, REG_C},
        [0x0D] = {INS_DEC, ADD_REG, REG_C},
        [0x0E] = {INS_LD, ADD_REG_N8, REG_C},
        [0x0F] = {INS_RRCA, ADD_INP},
        [0x10] = {INS_STOP, ADD_N8,},
        [0x11] = {INS_LD, ADD_REG_N16, REG_DE},
        [0x12] = {INS_LD, ADD_MEM_REG, REG_DE, REG_A},
        [0x13] = {INS_INC, ADD_REG, REG_DE},
        [0x14] = {INS_INC, ADD_REG, REG_D},
        [0x15] = {INS_DEC, ADD_REG, REG_D},
        [0x16] = {INS_LD, ADD_REG_N8, REG_D},
        [0x17] = {INS_RLA, ADD_INP},
        [0x18] = {INS_JR, ADD_E8,},
        [0x19] = {INS_ADD, ADD_REG_REG, REG_HL, REG_DE},
        [0x1A] = {INS_LD, ADD_REG_MEM, REG_A, REG_DE},
        [0x1B] = {INS_DEC, ADD_REG, REG_DE},
        [0x1C] = {INS_INC, ADD_REG, REG_E},
        [0x1D] = {INS_DEC, ADD_REG, REG_E},
        [0x1E] = {INS_LD, ADD_REG_N8, REG_E},
        [0x1F] = {INS_RRA, ADD_INP},
        [0x20] = {INS_JR, ADD_E8, REG_NONE, REG_NONE, COND_NZ},
        [0x21] = {INS_LD, ADD_REG_N16, REG_HL},
        [0x22] = {INS_LD, ADD_HLI_REG, REG_HL, REG_A},
        [0x23] = {INS_INC, ADD_REG, REG_HL},
        [0x24] = {INS_INC, ADD_REG, REG_H},
        [0x25] = {INS_DEC, ADD_REG, REG_H},
        [0x26] = {INS_LD, ADD_REG_N8, REG_H},
        [0x27] = {INS_DAA, ADD_INP},
        [0x28] = {INS_JR, ADD_E8, REG_NONE, REG_NONE, COND_Z},
        [0x29] = {INS_ADD, ADD_REG_REG, REG_HL, REG_HL},
        [0x2A] = {INS_LD, ADD_REG_HLI, REG_A, REG_HL},
        [0x2B] = {INS_DEC, ADD_REG, REG_HL},
        [0x2C] = {INS_INC, ADD_REG, REG_L},
        [0x2D] = {INS_DEC, ADD_REG, REG_L},
        [0x2E] = {INS_LD, ADD_REG_N8, REG_L},
        [0x2F] = {INS_CPL, ADD_INP},
        [0x30] = {INS_JR, ADD_E8, REG_NONE, REG_NONE, COND_NZ},
        [0x31] = {INS_LD, ADD_REG_N16, REG_SP},
        [0x32] = {INS_LD, ADD_HLD_REG, REG_HL, REG_A},
        [0x33] = {INS_INC, ADD_REG, REG_SP},
        [0x34] = {INS_INC, ADD_MEM, REG_HL},
        [0x35] = {INS_DEC, ADD_MEM, REG_HL},
        // todo [0x36] = {INS_LD, AM_MR_D8, REG_HL},
        [0x37] = {INS_SCF, ADD_INP},
        [0x38] = {INS_JR, ADD_E8, REG_NONE, REG_NONE, COND_C},
        [0x39] = {INS_ADD, ADD_REG_REG, REG_HL, REG_SP},
        [0x3A] = {INS_LD, ADD_REG_HLD, REG_A, REG_HL},
        [0x3B] = {INS_DEC, ADD_REG, REG_SP},
        [0x3C] = {INS_INC, ADD_REG, REG_A},
        [0x3D] = {INS_DEC, ADD_REG, REG_A},
        [0x3E] = {INS_LD, ADD_REG_N8, REG_A},
        [0x3F] = {INS_CCF, ADD_INP},
        [0x40] = {INS_LD, ADD_REG_REG, REG_B, REG_B},
        [0x41] = {INS_LD, ADD_REG_REG, REG_B, REG_C},
        [0x42] = {INS_LD, ADD_REG_REG, REG_B, REG_D},
        [0x43] = {INS_LD, ADD_REG_REG, REG_B, REG_E},
        [0x44] = {INS_LD, ADD_REG_REG, REG_B, REG_H},
        [0x45] = {INS_LD, ADD_REG_REG, REG_B, REG_L},
        [0x46] = {INS_LD, ADD_REG_MEM, REG_B, REG_HL},
        [0x47] = {INS_LD, ADD_REG_REG, REG_B, REG_A},
        [0x48] = {INS_LD, ADD_REG_REG, REG_C, REG_B},
        [0x49] = {INS_LD, ADD_REG_REG, REG_C, REG_C},
        [0x4A] = {INS_LD, ADD_REG_REG, REG_C, REG_D},
        [0x4B] = {INS_LD, ADD_REG_REG, REG_C, REG_E},
        [0x4C] = {INS_LD, ADD_REG_REG, REG_C, REG_H},
        [0x4D] = {INS_LD, ADD_REG_REG, REG_C, REG_L},
        [0x4E] = {INS_LD, ADD_REG_MEM, REG_C, REG_HL},
        [0x4F] = {INS_LD, ADD_REG_REG, REG_C, REG_A},

        [0x50] = {INS_LD, ADD_REG_REG, REG_D, REG_B},
        [0x51] = {INS_LD, ADD_REG_REG, REG_D, REG_C},
        [0x52] = {INS_LD, ADD_REG_REG, REG_D, REG_D},
        [0x53] = {INS_LD, ADD_REG_REG, REG_D, REG_E},
        [0x54] = {INS_LD, ADD_REG_REG, REG_D, REG_H},
        [0x55] = {INS_LD, ADD_REG_REG, REG_D, REG_L},
        [0x56] = {INS_LD, ADD_REG_MEM, REG_D, REG_HL},
        [0x57] = {INS_LD, ADD_REG_REG, REG_D, REG_A},
        [0x58] = {INS_LD, ADD_REG_REG, REG_E, REG_B},
        [0x59] = {INS_LD, ADD_REG_REG, REG_E, REG_C},
        [0x5A] = {INS_LD, ADD_REG_REG, REG_E, REG_D},
        [0x5B] = {INS_LD, ADD_REG_REG, REG_E, REG_E},
        [0x5C] = {INS_LD, ADD_REG_REG, REG_E, REG_H},
        [0x5D] = {INS_LD, ADD_REG_REG, REG_E, REG_L},
        [0x5E] = {INS_LD, ADD_REG_MEM, REG_E, REG_HL},
        [0x5F] = {INS_LD, ADD_REG_REG, REG_E, REG_A},

        [0x60] = {INS_LD, ADD_REG_REG, REG_H, REG_B},
        [0x61] = {INS_LD, ADD_REG_REG, REG_H, REG_C},
        [0x62] = {INS_LD, ADD_REG_REG, REG_H, REG_D},
        [0x63] = {INS_LD, ADD_REG_REG, REG_H, REG_E},
        [0x64] = {INS_LD, ADD_REG_REG, REG_H, REG_H},
        [0x65] = {INS_LD, ADD_REG_REG, REG_H, REG_L},
        [0x66] = {INS_LD, ADD_REG_MEM, REG_H, REG_HL},
        [0x67] = {INS_LD, ADD_REG_REG, REG_H, REG_A},
        [0x68] = {INS_LD, ADD_REG_REG, REG_L, REG_B},
        [0x69] = {INS_LD, ADD_REG_REG, REG_L, REG_C},
        [0x6A] = {INS_LD, ADD_REG_REG, REG_L, REG_D},
        [0x6B] = {INS_LD, ADD_REG_REG, REG_L, REG_E},
        [0x6C] = {INS_LD, ADD_REG_REG, REG_L, REG_H},
        [0x6D] = {INS_LD, ADD_REG_REG, REG_L, REG_L},
        [0x6E] = {INS_LD, ADD_REG_MEM, REG_L, REG_HL},
        [0x6F] = {INS_LD, ADD_REG_REG, REG_L, REG_A},

        [0x70] = {INS_LD, ADD_MEM_REG, REG_HL, REG_B},
        [0x71] = {INS_LD, ADD_MEM_REG, REG_HL, REG_C},
        [0x72] = {INS_LD, ADD_MEM_REG, REG_HL, REG_D},
        [0x73] = {INS_LD, ADD_MEM_REG, REG_HL, REG_E},
        [0x74] = {INS_LD, ADD_MEM_REG, REG_HL, REG_H},
        [0x75] = {INS_LD, ADD_MEM_REG, REG_HL, REG_L},
        [0x76] = {INS_HALT, ADD_INP},
        [0x77] = {INS_LD, ADD_MEM_REG, REG_HL, REG_A},
        [0x78] = {INS_LD, ADD_REG_REG, REG_A, REG_B},
        [0x79] = {INS_LD, ADD_REG_REG, REG_A, REG_C},
        [0x7A] = {INS_LD, ADD_REG_REG, REG_A, REG_D},
        [0x7B] = {INS_LD, ADD_REG_REG, REG_A, REG_E},
        [0x7C] = {INS_LD, ADD_REG_REG, REG_A, REG_H},
        [0x7D] = {INS_LD, ADD_REG_REG, REG_A, REG_L},
        [0x7E] = {INS_LD, ADD_REG_MEM, REG_A, REG_HL},
        [0x7F] = {INS_LD, ADD_REG_REG, REG_A, REG_A},

        [0x80] = {INS_ADD, ADD_REG_REG, REG_A, REG_B},
        [0x81] = {INS_ADD, ADD_REG_REG, REG_A, REG_C},
        [0x82] = {INS_ADD, ADD_REG_REG, REG_A, REG_D},
        [0x83] = {INS_ADD, ADD_REG_REG, REG_A, REG_E},
        [0x84] = {INS_ADD, ADD_REG_REG, REG_A, REG_H},
        [0x85] = {INS_ADD, ADD_REG_REG, REG_A, REG_L},
        [0x86] = {INS_ADD, ADD_REG_MEM, REG_A, REG_HL},
        [0x87] = {INS_ADD, ADD_REG_REG, REG_A, REG_A},
        [0x88] = {INS_ADC, ADD_REG_REG, REG_A, REG_B},
        [0x89] = {INS_ADC, ADD_REG_REG, REG_A, REG_C},
        [0x8A] = {INS_ADC, ADD_REG_REG, REG_A, REG_D},
        [0x8B] = {INS_ADC, ADD_REG_REG, REG_A, REG_E},
        [0x8C] = {INS_ADC, ADD_REG_REG, REG_A, REG_H},
        [0x8D] = {INS_ADC, ADD_REG_REG, REG_A, REG_L},
        [0x8E] = {INS_ADC, ADD_REG_MEM, REG_A, REG_HL},
        [0x8F] = {INS_ADC, ADD_REG_REG, REG_A, REG_A},

        [0x90] = {INS_SUB, ADD_REG_REG, REG_A, REG_B},
        [0x91] = {INS_SUB, ADD_REG_REG, REG_A, REG_C},
        [0x92] = {INS_SUB, ADD_REG_REG, REG_A, REG_D},
        [0x93] = {INS_SUB, ADD_REG_REG, REG_A, REG_E},
        [0x94] = {INS_SUB, ADD_REG_REG, REG_A, REG_H},
        [0x95] = {INS_SUB, ADD_REG_REG, REG_A, REG_L},
        [0x96] = {INS_SUB, ADD_REG_MEM, REG_A, REG_HL},
        [0x97] = {INS_SUB, ADD_REG_REG, REG_A, REG_A},
        [0x98] = {INS_SBC, ADD_REG_REG, REG_A, REG_B},
        [0x99] = {INS_SBC, ADD_REG_REG, REG_A, REG_C},
        [0x9A] = {INS_SBC, ADD_REG_REG, REG_A, REG_D},
        [0x9B] = {INS_SBC, ADD_REG_REG, REG_A, REG_E},
        [0x9C] = {INS_SBC, ADD_REG_REG, REG_A, REG_H},
        [0x9D] = {INS_SBC, ADD_REG_REG, REG_A, REG_L},
        [0x9E] = {INS_SBC, ADD_REG_MEM, REG_A, REG_HL},
        [0x9F] = {INS_SBC, ADD_REG_REG, REG_A, REG_A},

        [0xA0] = {INS_AND, ADD_REG_REG, REG_A, REG_B},
        [0xA1] = {INS_AND, ADD_REG_REG, REG_A, REG_C},
        [0xA2] = {INS_AND, ADD_REG_REG, REG_A, REG_D},
        [0xA3] = {INS_AND, ADD_REG_REG, REG_A, REG_E},
        [0xA4] = {INS_AND, ADD_REG_REG, REG_A, REG_H},
        [0xA5] = {INS_AND, ADD_REG_REG, REG_A, REG_L},
        [0xA6] = {INS_AND, ADD_REG_MEM, REG_A, REG_HL},
        [0xA7] = {INS_AND, ADD_REG_REG, REG_A, REG_A},
        [0xA8] = {INS_XOR, ADD_REG_REG, REG_A, REG_B},
        [0xA9] = {INS_XOR, ADD_REG_REG, REG_A, REG_C},
        [0xAA] = {INS_XOR, ADD_REG_REG, REG_A, REG_D},
        [0xAB] = {INS_XOR, ADD_REG_REG, REG_A, REG_E},
        [0xAC] = {INS_XOR, ADD_REG_REG, REG_A, REG_H},
        [0xAD] = {INS_XOR, ADD_REG_REG, REG_A, REG_L},
        [0xAE] = {INS_XOR, ADD_REG_MEM, REG_A, REG_HL},
        [0xAF] = {INS_XOR, ADD_REG_REG, REG_A, REG_A},

        [0xB0] = {INS_OR, ADD_REG_REG, REG_A, REG_B},
        [0xB1] = {INS_OR, ADD_REG_REG, REG_A, REG_C},
        [0xB2] = {INS_OR, ADD_REG_REG, REG_A, REG_D},
        [0xB3] = {INS_OR, ADD_REG_REG, REG_A, REG_E},
        [0xB4] = {INS_OR, ADD_REG_REG, REG_A, REG_H},
        [0xB5] = {INS_OR, ADD_REG_REG, REG_A, REG_L},
        [0xB6] = {INS_OR, ADD_REG_MEM, REG_A, REG_HL},
        [0xB7] = {INS_OR, ADD_REG_REG, REG_A, REG_A},
        [0xB8] = {INS_CP, ADD_REG_REG, REG_A, REG_B},
        [0xB9] = {INS_CP, ADD_REG_REG, REG_A, REG_C},
        [0xBA] = {INS_CP, ADD_REG_REG, REG_A, REG_D},
        [0xBB] = {INS_CP, ADD_REG_REG, REG_A, REG_E},
        [0xBC] = {INS_CP, ADD_REG_REG, REG_A, REG_H},
        [0xBD] = {INS_CP, ADD_REG_REG, REG_A, REG_L},
        [0xBE] = {INS_CP, ADD_REG_MEM, REG_A, REG_HL},
        [0xBF] = {INS_CP, ADD_REG_REG, REG_A, REG_A},

        [0xC0] = {INS_RET, ADD_INP, REG_NONE, REG_NONE, COND_NZ},
        [0xC1] = {INS_POP, ADD_REG, REG_BC},
        [0xC2] = {INS_JP, ADD_A16, REG_NONE, REG_NONE, COND_NZ},
        [0xC3] = {INS_JP, ADD_A16,},
        [0xC4] = {INS_CALL, ADD_A16, REG_NONE, REG_NONE, COND_NZ},
        [0xC5] = {INS_PUSH, ADD_REG, REG_BC},
        [0xC6] = {INS_ADD, ADD_REG_N8, REG_A},
        [0xC7] = {INS_RST, ADD_INP, REG_NONE, REG_NONE, COND_NONE},
        [0xC8] = {INS_RET, ADD_INP, REG_NONE, REG_NONE, COND_Z},
        [0xC9] = {INS_RET, ADD_INP},
        [0xCA] = {INS_JP, ADD_A16, REG_NONE, REG_NONE, COND_Z},
        [0xCB] = {INS_PREFIX, ADD_E8},
        [0xCC] = {INS_CALL, ADD_A16, REG_NONE, REG_NONE, COND_Z},
        [0xCD] = {INS_CALL, ADD_A16,},
        [0xCE] = {INS_ADC, ADD_REG_N8, REG_A},
        [0xCF] = {INS_RST, ADD_INP, REG_NONE, REG_NONE, COND_NONE},

        [0xD0] = {INS_RET, ADD_INP, REG_NONE, REG_NONE, COND_NZ},
        [0xD1] = {INS_POP, ADD_REG, REG_DE},
        [0xD2] = {INS_JP, ADD_A16, REG_NONE, REG_NONE, COND_NZ},
        [0xD4] = {INS_CALL, ADD_A16, REG_NONE, REG_NONE, COND_NZ},
        [0xD5] = {INS_PUSH, ADD_REG, REG_DE},
        [0xD6] = {INS_SUB, ADD_REG_N8, REG_A},
        [0xD7] = {INS_RST, ADD_INP, REG_NONE, REG_NONE, COND_NONE},
        [0xD8] = {INS_RET, ADD_INP, REG_NONE, REG_NONE, COND_C},
        [0xD9] = {INS_RETI, ADD_INP},
        [0xDA] = {INS_JP, ADD_A16, REG_NONE, REG_NONE, COND_C},
        [0xDC] = {INS_CALL, ADD_A16, REG_NONE, REG_NONE, COND_C},
        [0xDF] = {INS_RST, ADD_INP, REG_NONE, REG_NONE, COND_NONE},

        [0xE0] = {INS_LDH, ADD_A8_REG, REG_NONE, REG_A},
        [0xE1] = {INS_POP, ADD_REG, REG_HL},
        [0xE2] = {INS_LD, ADD_MEM_REG, REG_C, REG_A},
        [0xE5] = {INS_PUSH, ADD_REG, REG_HL},
        [0xE6] = {INS_AND, ADD_E8},
        [0xE7] = {INS_RST, ADD_INP, REG_NONE, REG_NONE, COND_NONE},
        [0xE8] = {INS_ADD, ADD_REG_N8, REG_SP},
        [0xE9] = {INS_JP, ADD_MEM, REG_HL},
        [0xEA] = {INS_LD, ADD_A16_REG, REG_NONE, REG_A},
        [0xEE] = {INS_XOR, ADD_E8},
        [0xEF] = {INS_RST, ADD_INP, REG_NONE, REG_NONE, COND_NONE},

        [0xF0] = {INS_LDH, ADD_REG_N8, REG_A},
        [0xF1] = {INS_POP, ADD_REG, REG_AF},
        [0xF2] = {INS_LD, ADD_REG_MEM, REG_A, REG_C},
        [0xF3] = {INS_DI, ADD_INP},
        [0xF5] = {INS_PUSH, ADD_REG, REG_AF},
        [0xF6] = {INS_OR, ADD_E8},
        [0xF7] = {INS_RST, ADD_INP, REG_NONE, REG_NONE, COND_NONE},
        [0xFA] = {INS_LD, ADD_REG_A16, REG_A},
        [0xFB] = {INS_EI, ADD_INP},
        [0xFE] = {INS_CP, ADD_E8},
        [0xFF] = {INS_RST, ADD_INP, REG_NONE, REG_NONE, COND_NONE},
};

Instruction *lookup_instruction(uint8_t opcode) {
    return &instructions[opcode];
}
    