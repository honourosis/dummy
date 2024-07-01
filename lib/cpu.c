#include "cpu.h"
#include "mem.h"
#include "executor.h"

CPU_context ctx = {};

char *instruction_names[34] = {
        "NOP",
        "LD",
        "INC",
        "RLCA",
        "ADD",
        "DEC",
        "RRCA",
        "STOP",
        "RLA",
        "JR",
        "RRA",
        "DAA",
        "CPL",
        "SCF",
        "CCF",
        "HALT",
        "SUB",
        "SBC",
        "AND",
        "XOR",
        "OR",
        "CP",
        "RET",
        "POP",
        "JP",
        "CALL",
        "PUSH",
        "RST",
        "PREFIX",
        "LDH",
        "ADC",
        "RETI",
        "DI",
        "EI"
};

void set_register_val(Register reg, uint16_t val) {
    switch (reg) {
        case REG_A:
            ctx.registers.A = val & 0xFF;
            break;
        case REG_B:
            ctx.registers.B = val & 0xFF;
            break;
        case REG_C:
            ctx.registers.C = val & 0xFF;
            break;
        case REG_D:
            ctx.registers.D = val & 0xFF;
            break;
        case REG_E:
            ctx.registers.E = val & 0xFF;
            break;
        case REG_H:
            ctx.registers.H = val & 0xFF;
            break;
        case REG_L:
            ctx.registers.L = val & 0xFF;
            break;
        case REG_HL:
            ctx.registers.H = swap_int16(val);
            break;
        case REG_DE:
            ctx.registers.D = swap_int16(val);
            break;
        case REG_AF:
            ctx.registers.A = swap_int16(val);
            break;
        case REG_BC:
            ctx.registers.B = swap_int16(val);
            break;
        case REG_SP:
            ctx.registers.SP = val;
            break;
        case REG_PC:
            ctx.registers.PC = val;
            break;
        default:
            printf("Unexpected register value: %x", reg);
            exit(-1);
    }
}

uint16_t get_register_val(Register reg) {
    switch (reg) {
        case REG_A:
            return ctx.registers.A;
        case REG_B:
            return ctx.registers.B;
        case REG_C:
            return ctx.registers.C;
        case REG_D:
            return ctx.registers.D;
        case REG_E:
            return ctx.registers.E;
        case REG_H:
            return ctx.registers.H;
        case REG_L:
            return ctx.registers.L;
        case REG_AF:
        TODO
        case REG_HL:
            return join_8b_16b(ctx.registers.L, ctx.registers.H);
        case REG_BC:
            return join_8b_16b(ctx.registers.C, ctx.registers.B);
        case REG_DE:
            return join_8b_16b(ctx.registers.E, ctx.registers.D);
        case REG_PC:
            return ctx.registers.PC;
        case REG_SP:
            return ctx.registers.SP;
        default:
        TODO
    }
}

void next_instruction() {
    ctx.opcode = read_mem(ctx.registers.PC++);
    ctx.instruction = lookup_instruction(ctx.opcode);
    if (ctx.instruction == NULL) {
        printf("Unknown instruction: %02x", ctx.opcode);
        exit(1);
    }
}

void next_data() {
    switch (ctx.instruction->addressing) {
        case ADD_INP:
        case ADD_REG:
        case ADD_REG_REG:
        case ADD_HLI_REG:
        case ADD_REG_HLI:
        case ADD_HLD_REG:
        case ADD_MEM_REG:
        case ADD_REG_HLD: {
            ctx.data = 0;
            return;
        }
        case ADD_MEM:
            ctx.data = read_mem(ctx.registers.PC);
            return;
        case ADD_REG_MEM: {
            uint8_t addr = get_register_val(ctx.instruction->reg_2);
            ctx.data = read_mem(addr);
            return;
        }
        case ADD_E8:
        case ADD_N8:
        case ADD_REG_N8:
        case ADD_A8_REG: {
            ctx.data = read_mem(ctx.registers.PC);
            ctx.registers.PC++;
            return;
        }
        case ADD_A16:
        case ADD_A16_REG:
        case ADD_REG_A16:
        case ADD_REG_N16: {
            ctx.data = swap_int16(join_8b_16b(read_mem(ctx.registers.PC), read_mem(ctx.registers.PC + 1)));
            ctx.registers.PC += 2;
            return;
        }
    }
}

void print_cpu_state() {
    printf("\nInstruction: %s: (%02x %02x %02x) \n",
           instruction_names[ctx.instruction->type],
           ctx.opcode,
           read_mem(ctx.registers.PC),
           read_mem(ctx.registers.PC + 1)
    );
    printf("Registers:\n[ A: %02x; B: %02x; C: %02x ]\n[ D: %02x; E: %02x; F: %02x ]\n[ H: %02x; L: %02x;]\n",
           ctx.registers.A, ctx.registers.B, ctx.registers.C,
           ctx.registers.D, ctx.registers.F, ctx.registers.E,
           ctx.registers.H, ctx.registers.L);
    printf("SP: (%02x), PC: (%02x)\n", ctx.registers.SP, ctx.registers.PC);
}

void execute() {
    print_cpu_state();
    Executor executor = lookup_executor(ctx.instruction);
    if (executor != NULL) {
        executor(&ctx);
    }
}

void cpu_step() {
    next_instruction();
    next_data();
    execute();
}

void init_cpu() {
    ctx.registers.PC = 0x100;
}
