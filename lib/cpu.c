#include "cpu.h"
#include "mem.h"
#include "executor.h"

CPU cpu = {};
CPU_context ctx = {};

uint16_t get_8bit_register_val(Register reg) {
    switch (reg) {
        case REG_A:
            return cpu.registers.A;
        case REG_B:
            return cpu.registers.B;
        case REG_C:
            return cpu.registers.C;
        case REG_D:
            return cpu.registers.D;
        case REG_E:
            return cpu.registers.E;
        case REG_H:
            return cpu.registers.H;
        case REG_L:
            return cpu.registers.L;
        case REG_AF:
        TODO
        case REG_HL:
            return join_8b_16b(cpu.registers.H, cpu.registers.L);
        case REG_BC:
            return join_8b_16b(cpu.registers.B, cpu.registers.C);
        case REG_DE:
            return join_8b_16b(cpu.registers.D, cpu.registers.E);
        case REG_PC:
            return cpu.registers.PC;
        case REG_SP:
            return cpu.registers.SP;
    }
}

void next_instruction() {
    ctx.opcode = read_mem(cpu.registers.PC++);
    ctx.instruction = lookup_instruction(ctx.opcode);
    if (ctx.instruction == NULL) {
        printf("Unknown instruction: %02x", ctx.opcode);
        exit(1);
    }
    cpu.current_instruction = ctx.instruction;
}

void next_data() {
    switch (cpu.current_instruction->addressing) {
        case ADD_INP:
            return;
        case ADD_REG:
            ctx.operand_one = get_8bit_register_val(ctx.instruction->reg_1);
            return;
        case ADD_REG_REG:
            ctx.operand_one = get_8bit_register_val(ctx.instruction->reg_1);
            ctx.operand_two = get_8bit_register_val(ctx.instruction->reg_2);
            return;
        case ADD_REG_N8:
            ctx.operand_one = get_8bit_register_val(ctx.instruction->reg_1);
            ctx.operand_two = read_mem(cpu.registers.PC);
            cpu.registers.PC++;
            return;
        case ADD_REG_N16:
            ctx.operand_one = get_8bit_register_val(ctx.instruction->reg_1);
            uint8_t low_bytes = read_mem(cpu.registers.PC);
            uint8_t high_bytes = read_mem(cpu.registers.PC + 1);
            cpu.registers.PC += 2;
            ctx.operand_two = join_8b_16b(low_bytes, high_bytes);
            return;
        case ADD_REG_A8:
            ctx.operand_one = get_8bit_register_val(ctx.instruction->reg_1);
            ctx.operand_two = read_mem(cpu.registers.PC);
            cpu.registers.PC += 1;
            break;
        case ADD_ADDR:
            ctx.operand_one = read_mem(cpu.registers.PC);
            cpu.registers.PC += 1;
            break;
        case ADD_REG_A16:
            ctx.operand_one = get_8bit_register_val(ctx.instruction->reg_1);
            ctx.operand_two = swap_int16(
                    join_8b_16b(
                            read_mem(cpu.registers.PC),
                            read_mem(cpu.registers.PC + 1)
                    )
            );
            cpu.registers.PC += 2;
            break;
        case ADD_NZ:
            printf("Addressing for ADD_NZ!\n");
            break;
        case ADD_NZ_A16:
            ctx.operand_two = swap_int16(
                    join_8b_16b(
                            read_mem(cpu.registers.PC),
                            read_mem(cpu.registers.PC + 1)
                    )
            );
            cpu.registers.PC += 2;
            break;
        case ADD_A16:
            ctx.operand_one = swap_int16(
                    join_8b_16b(
                            read_mem(cpu.registers.PC),
                            read_mem(cpu.registers.PC + 1)
                    )
            );
            cpu.registers.PC += 2;
            break;
        case ADD_A16_REG:
            ctx.operand_one = swap_int16(
                    join_8b_16b(
                            read_mem(cpu.registers.PC),
                            read_mem(cpu.registers.PC + 1)
                    )
            );
            cpu.registers.PC += 2;
            ctx.operand_two = get_8bit_register_val(ctx.instruction->reg_1);
            break;
        case ADD_Z_A16:
            ctx.operand_two = swap_int16(
                    join_8b_16b(
                            read_mem(cpu.registers.PC),
                            read_mem(cpu.registers.PC + 1)
                    )
            );
            cpu.registers.PC += 2;
            break;
        case ADD_Z:
            printf("Addressing for ADD_Z!\n");
            break;
        case ADD_N8:
            ctx.operand_one = read_mem(cpu.registers.PC);
            cpu.registers.PC += 1;
            break;
        case ADD_E8:
            printf("Addressing for ADD_E8!\n");
            break;
        default:
            printf("Addressing for '%02x' not implemented!\n", cpu.current_instruction->addressing);
    }
}

void execute() {
    printf("Opcode (%u): %02x; SP: %i, PC: %i\n", ctx.instruction->type, ctx.opcode, cpu.registers.SP,
           cpu.registers.PC);
    Executor executor = lookup_executor(ctx.instruction);
    executor(&ctx);
}

void cpu_step() {
    next_instruction();
    next_data();
    execute();
}
