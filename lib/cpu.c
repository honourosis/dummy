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

void set_8bit_register_val(Register reg, uint8_t val) {
    switch (reg) {
        case REG_A:
            ctx.registers.A = val;
            break;
        case REG_B:
            ctx.registers.B = val;
            break;
        case REG_C:
            ctx.registers.C = val;
            break;
        case REG_D:
            ctx.registers.D = val;
            break;
        case REG_E:
            ctx.registers.E = val;
            break;
        case REG_H:
            ctx.registers.H = val;
            break;
        case REG_L:
            ctx.registers.L = val;
            break;
        default:
        TODO;
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
            return join_8b_16b(ctx.registers.H, ctx.registers.L);
        case REG_BC:
            return join_8b_16b(ctx.registers.B, ctx.registers.C);
        case REG_DE:
            return join_8b_16b(ctx.registers.D, ctx.registers.E);
        case REG_PC:
            return ctx.registers.PC;
        case REG_SP:
            return ctx.registers.SP;
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
            return;
        case ADD_REG:
            ctx.operand_one = get_register_val(ctx.instruction->reg_1);
            return;
        case ADD_REG_REG:
            ctx.operand_one = get_register_val(ctx.instruction->reg_1);
            ctx.operand_two = get_register_val(ctx.instruction->reg_2);
            return;
        case ADD_REG_N8:
            ctx.operand_one = get_register_val(ctx.instruction->reg_1);
            ctx.operand_two = read_mem(ctx.registers.PC);
            ctx.registers.PC++;
            return;
        case ADD_REG_N16:
            ctx.operand_one = get_register_val(ctx.instruction->reg_1);
            uint8_t low_bytes = read_mem(ctx.registers.PC);
            uint8_t high_bytes = read_mem(ctx.registers.PC + 1);
            ctx.registers.PC += 2;
            ctx.operand_two = join_8b_16b(low_bytes, high_bytes);
            return;
        case ADD_REG_A8:
            ctx.operand_one = get_register_val(ctx.instruction->reg_1);
            ctx.operand_two = read_mem(ctx.registers.PC);
            ctx.registers.PC += 1;
            break;
        case ADD_ADDR:
            ctx.operand_one = read_mem(ctx.registers.PC);
            ctx.registers.PC += 1;
            break;
        case ADD_REG_A16:
            ctx.operand_one = get_register_val(ctx.instruction->reg_1);
            ctx.operand_two = swap_int16(
                    join_8b_16b(
                            read_mem(ctx.registers.PC),
                            read_mem(ctx.registers.PC + 1)
                    )
            );
            ctx.registers.PC += 2;
            break;
        case ADD_NZ:
            printf("Addressing for ADD_NZ!\n");
            break;
        case ADD_NZ_A16:
            ctx.operand_two = swap_int16(
                    join_8b_16b(
                            read_mem(ctx.registers.PC),
                            read_mem(ctx.registers.PC + 1)
                    )
            );
            ctx.registers.PC += 2;
            break;
        case ADD_A16:
            ctx.operand_one = swap_int16(
                    join_8b_16b(
                            read_mem(ctx.registers.PC),
                            read_mem(ctx.registers.PC + 1)
                    )
            );
            ctx.registers.PC += 2;
            break;
        case ADD_A16_REG:
            ctx.operand_one = swap_int16(
                    join_8b_16b(
                            read_mem(ctx.registers.PC),
                            read_mem(ctx.registers.PC + 1)
                    )
            );
            ctx.registers.PC += 2;
            ctx.operand_two = get_register_val(ctx.instruction->reg_1);
            break;
        case ADD_Z_A16:
            ctx.operand_two = swap_int16(
                    join_8b_16b(
                            read_mem(ctx.registers.PC),
                            read_mem(ctx.registers.PC + 1)
                    )
            );
            ctx.registers.PC += 2;
            break;
        case ADD_Z:
            printf("Addressing for ADD_Z!\n");
            break;
        case ADD_N8:
            ctx.operand_one = read_mem(ctx.registers.PC);
            ctx.registers.PC += 1;
            break;
        case ADD_E8:
            printf("Addressing for ADD_E8!\n");
            break;
        default:
            printf("Addressing for '%02x' not implemented!\n", ctx.instruction->addressing);
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
