#include "cpu.h"
#include "mem.h"
#include "executor.h"

CPU_context ctx = {};

void set_8bit_register_val(Register reg, uint8_t val) {
    switch (reg) {
        case REG_A:
            ctx.cpu.registers.A = val;
            break;
        case REG_B:
            ctx.cpu.registers.B = val;
            break;
        case REG_C:
            ctx.cpu.registers.C = val;
            break;
        case REG_D:
            ctx.cpu.registers.D = val;
            break;
        case REG_E:
            ctx.cpu.registers.E = val;
            break;
        case REG_H:
            ctx.cpu.registers.H = val;
            break;
        case REG_L:
            ctx.cpu.registers.L = val;
            break;
        default:
        TODO;
    }
}

uint16_t get_register_val(Register reg) {
    switch (reg) {
        case REG_A:
            return ctx.cpu.registers.A;
        case REG_B:
            return ctx.cpu.registers.B;
        case REG_C:
            return ctx.cpu.registers.C;
        case REG_D:
            return ctx.cpu.registers.D;
        case REG_E:
            return ctx.cpu.registers.E;
        case REG_H:
            return ctx.cpu.registers.H;
        case REG_L:
            return ctx.cpu.registers.L;
        case REG_AF:
        TODO
        case REG_HL:
            return join_8b_16b(ctx.cpu.registers.H, ctx.cpu.registers.L);
        case REG_BC:
            return join_8b_16b(ctx.cpu.registers.B, ctx.cpu.registers.C);
        case REG_DE:
            return join_8b_16b(ctx.cpu.registers.D, ctx.cpu.registers.E);
        case REG_PC:
            return ctx.cpu.registers.PC;
        case REG_SP:
            return ctx.cpu.registers.SP;
    }
}

void next_instruction() {
    ctx.opcode = read_mem(ctx.cpu.registers.PC++);
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
            ctx.operand_two = read_mem(ctx.cpu.registers.PC);
            ctx.cpu.registers.PC++;
            return;
        case ADD_REG_N16:
            ctx.operand_one = get_register_val(ctx.instruction->reg_1);
            uint8_t low_bytes = read_mem(ctx.cpu.registers.PC);
            uint8_t high_bytes = read_mem(ctx.cpu.registers.PC + 1);
            ctx.cpu.registers.PC += 2;
            ctx.operand_two = join_8b_16b(low_bytes, high_bytes);
            return;
        case ADD_REG_A8:
            ctx.operand_one = get_register_val(ctx.instruction->reg_1);
            ctx.operand_two = read_mem(ctx.cpu.registers.PC);
            ctx.cpu.registers.PC += 1;
            break;
        case ADD_ADDR:
            ctx.operand_one = read_mem(ctx.cpu.registers.PC);
            ctx.cpu.registers.PC += 1;
            break;
        case ADD_REG_A16:
            ctx.operand_one = get_register_val(ctx.instruction->reg_1);
            ctx.operand_two = swap_int16(
                    join_8b_16b(
                            read_mem(ctx.cpu.registers.PC),
                            read_mem(ctx.cpu.registers.PC + 1)
                    )
            );
            ctx.cpu.registers.PC += 2;
            break;
        case ADD_NZ:
            printf("Addressing for ADD_NZ!\n");
            break;
        case ADD_NZ_A16:
            ctx.operand_two = swap_int16(
                    join_8b_16b(
                            read_mem(ctx.cpu.registers.PC),
                            read_mem(ctx.cpu.registers.PC + 1)
                    )
            );
            ctx.cpu.registers.PC += 2;
            break;
        case ADD_A16:
            ctx.operand_one = swap_int16(
                    join_8b_16b(
                            read_mem(ctx.cpu.registers.PC),
                            read_mem(ctx.cpu.registers.PC + 1)
                    )
            );
            ctx.cpu.registers.PC += 2;
            break;
        case ADD_A16_REG:
            ctx.operand_one = swap_int16(
                    join_8b_16b(
                            read_mem(ctx.cpu.registers.PC),
                            read_mem(ctx.cpu.registers.PC + 1)
                    )
            );
            ctx.cpu.registers.PC += 2;
            ctx.operand_two = get_register_val(ctx.instruction->reg_1);
            break;
        case ADD_Z_A16:
            ctx.operand_two = swap_int16(
                    join_8b_16b(
                            read_mem(ctx.cpu.registers.PC),
                            read_mem(ctx.cpu.registers.PC + 1)
                    )
            );
            ctx.cpu.registers.PC += 2;
            break;
        case ADD_Z:
            printf("Addressing for ADD_Z!\n");
            break;
        case ADD_N8:
            ctx.operand_one = read_mem(ctx.cpu.registers.PC);
            ctx.cpu.registers.PC += 1;
            break;
        case ADD_E8:
            printf("Addressing for ADD_E8!\n");
            break;
        default:
            printf("Addressing for '%02x' not implemented!\n", ctx.instruction->addressing);
    }
}

void print_cpu_state() {
    printf("\nOp: (%u): %02x\n", ctx.instruction->type, ctx.opcode);
    printf("Registers:\n[ A: %x; B: %x; C: %x ]\n[ D: %x; E: %x; F: %x ]\n[ H: %x; L: %x;]\n",
           ctx.cpu.registers.A, ctx.cpu.registers.B, ctx.cpu.registers.C,
           ctx.cpu.registers.D, ctx.cpu.registers.F, ctx.cpu.registers.E,
           ctx.cpu.registers.H, ctx.cpu.registers.L);
    printf("SP: %i, PC: %i\n", ctx.cpu.registers.SP, ctx.cpu.registers.PC);
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
