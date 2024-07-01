#include "executor.h"
#include "mem.h"

bool check_condition(CPU_context *ctx) {
    if (ctx->instruction->condition == COND_NONE) {
        return true;
    }
    int8_t reg_l = get_register_val(REG_L);
    int8_t z = bit_at_index(reg_l, 7);
    int8_t c = bit_at_index(reg_l, 4);
    switch (ctx->instruction->condition) {
        case COND_Z:
            return z;
        case COND_NZ:
            return !z;
        case COND_C:
            return c;
        case COND_NC:
            return !c;
        default:
            printf("Unhandled condition! %x", ctx->instruction->condition);
            exit(1);
    }
}

void set_flags(CPU_context *ctx, int8_t zero, int8_t nsub, int8_t halt, int8_t carry) {
    if (zero != -1) {
        ctx->registers.L = set_bit_at_index(ctx->registers.L, 7, zero);
    }
    if (nsub != -1) {
        ctx->registers.L = set_bit_at_index(ctx->registers.L, 6, nsub);
    }
    if (halt != -1) {
        ctx->registers.L = set_bit_at_index(ctx->registers.L, 5, halt);
    }
    if (carry != -1) {
        ctx->registers.L = set_bit_at_index(ctx->registers.L, 4, carry);
    }
}

void exec_and(CPU_context *ctx) {
    printf("exec_and");
    TODO
}

void exec_add(CPU_context *ctx) {
    printf("exec_add");
    TODO
}

void exec_ld(CPU_context *ctx) {
    Addressing addressing = ctx->instruction->addressing;
    if (addressing == ADD_REG_REG) {
        set_register_val(ctx->instruction->reg_1, get_register_val(ctx->instruction->reg_2));
    } else if (addressing == ADD_REG_N16 || addressing == ADD_REG_N8) {
        set_register_val(ctx->instruction->reg_1, ctx->data);
    } else if (addressing == ADD_HLD_REG) {
        uint16_t address = get_register_val(ctx->instruction->reg_1);
        uint16_t value = get_register_val(ctx->instruction->reg_2);
        write_mem(address, value);
        set_register_val(ctx->instruction->reg_1, address - 1);
    } else if (addressing == ADD_REG_MEM) {
        set_register_val(ctx->instruction->reg_1, ctx->data);
    } else if (addressing == ADD_MEM_REG) {
        uint16_t address = get_register_val(ctx->instruction->reg_1);
        uint16_t value = get_register_val(ctx->instruction->reg_2);
        write_mem(address, value);
    } else {
        printf("NOT IMPLEMENTED!");
        exit(1);
    }
}

void exec_xor(CPU_context *ctx) {
    if (ctx->instruction->addressing == ADD_REG_REG) {
        uint16_t value = get_register_val(ctx->instruction->reg_2) ^ get_register_val(ctx->instruction->reg_1);
        set_flags(ctx, value == 0, 0, 0, 0);
    } else {
        TODO
    }
}

void exec_rrca(CPU_context *ctx) {
    printf("exec_rrca");
    TODO
}

void exec_dec(CPU_context *ctx) {
    if (ctx->instruction->addressing == ADD_REG) {
        uint8_t value = get_register_val(ctx->instruction->reg_1) - 1;
        set_register_val(ctx->instruction->reg_1, value);
        set_flags(ctx, value == 0, 1, 0, 0);
    } else {
        printf("Not implemented for exec_dec");
        TODO
    }
}

void exec_inc(CPU_context *ctx) {
    if (ctx->instruction->addressing == ADD_REG) {
        int8_t value = get_register_val(ctx->instruction->reg_1) + 1;
        set_register_val(ctx->instruction->reg_1, value);
        set_flags(ctx, value == 0, 0, -1, -1);
    } else if (ctx->instruction->addressing == ADD_MEM) {
        uint16_t address = get_register_val(ctx->instruction->reg_1);
        uint8_t curr_value = read_mem(address);
        write_mem(address, curr_value + 1);
    } else {
        printf("Should not happen");
        exit(-2);
    }
}

void exec_rlca(CPU_context *ctx) {
    printf("exec_rlca");
    TODO
}

void exec_nop(CPU_context *ctx) {
    // nothing to do
}

void exec_or(CPU_context *ctx) {
    printf("exec_or");
    TODO
}

// can be executed only for register A
void exec_cp(CPU_context *ctx) {
    int8_t n = (int8_t) ctx->registers.A - (int8_t) ctx->data;
    int8_t halt = ((int8_t) ctx->registers.A & 0x0F) - ((int8_t) ctx->data & 0x0F) < 0;
    set_flags(ctx, n == 0, 1, halt, n < 0);
}

void exec_rra(CPU_context *ctx) {
    printf("exec_rra");
    TODO
}

void exec_stop(CPU_context *ctx) {
    printf("exec_stop");
    TODO
}

void exec_jr(CPU_context *ctx) {
    if (!check_condition(ctx)) {
        return;
    }
    int8_t offset = (int8_t) (ctx->data & 0xFF);
    ctx->registers.PC += offset;
}

void exec_rla(CPU_context *ctx) {
    printf("exec_rla");
    TODO
}

void exec_jp(CPU_context *ctx) {
    if (!check_condition(ctx)) {
        return;
    }
    Addressing addressing = ctx->instruction->addressing;
    if (addressing == ADD_REG) {
        ctx->registers.PC = get_register_val(ctx->instruction->reg_1);
    } else if (addressing == ADD_A16) {
        ctx->registers.PC = ctx->data;
    } else {
        printf("Not implemented! exec_jp for %x", addressing);
        TODO
    }
}

void exec_pop(CPU_context *ctx) {
    printf("exec_pop");
    TODO
}

void exec_ret(CPU_context *ctx) {
    printf("exec_ret");
    TODO
}

void exec_cpl(CPU_context *ctx) {
    printf("exec_cpl");
    TODO
}

void exec_rst(CPU_context *ctx) {
    printf("exec_rst");
    TODO
}

void exec_push(CPU_context *ctx) {
    printf("exec_push");
    TODO
}

void exec_call(CPU_context *ctx) {
    printf("exec_call");
    TODO
}

void exec_daa(CPU_context *ctx) {
    printf("exec_daa");
    TODO
}

void exec_reti(CPU_context *ctx) {
    printf("exec_reti");
    TODO
}

void exec_ccf(CPU_context *ctx) {
    printf("exec_ccf");
    TODO
}

void exec_sub(CPU_context *ctx) {
    int8_t value = get_register_val(ctx->instruction->reg_2) - get_register_val(ctx->instruction->reg_1);
    set_register_val(ctx->instruction->reg_1, value);
    set_flags(ctx, value == 0, 1, /*todo*/ -1, -1);
}

void exec_scf(CPU_context *ctx) {
    printf("exec_scf");
    TODO
}

void exec_adc(CPU_context *ctx) {
    printf("exec_adc");
    TODO
}

void exec_ldh(CPU_context *ctx) {
    printf("exec_ldh");
    TODO
}

void exec_sbc(CPU_context *ctx) {
    if (ctx->instruction->addressing == ADD_REG_REG) {
        int8_t value = get_register_val(ctx->instruction->reg_1) - get_register_val(ctx->instruction->reg_2);
        set_register_val(ctx->instruction->reg_1, value);
        set_flags(ctx, value == 0, 1, /*todo*/ -1, -1);
    } else {
        printf("not implemented exec_sbc");
        exit(1);
    }
}

void exec_di(CPU_context *ctx) {
    printf("exec_di");
    TODO
}

void exec_ei(CPU_context *ctx) {
    printf("exec_ei");
    TODO
}

void exec_halt(CPU_context *ctx) {
    printf("exec_halt");
    TODO
}

Executor executors[0x22] = {
        [INS_NOP] = &exec_nop,
        [INS_LD] = &exec_ld,
        [INS_INC] = &exec_inc,
        [INS_RLCA] = &exec_rlca,
        [INS_ADD] = &exec_add,
        [INS_DEC] = &exec_dec,
        [INS_RRCA] = &exec_rrca,
        [INS_STOP] = &exec_stop,
        [INS_RLA] = &exec_rla,
        [INS_JR] = &exec_jr,
        [INS_RRA] = &exec_rra,
        [INS_DAA] = &exec_daa,
        [INS_CPL] = &exec_cpl,
        [INS_SCF] = &exec_scf,
        [INS_CCF] = &exec_ccf,
        [INS_HALT] = &exec_halt,
        [INS_SUB] = &exec_sub,
        [INS_SBC] = &exec_sbc,
        [INS_AND] = &exec_and,
        [INS_XOR] = &exec_xor,
        [INS_OR] = &exec_or,
        [INS_CP] = &exec_cp,
        [INS_RET] = &exec_ret,
        [INS_POP] = &exec_pop,
        [INS_JP] = &exec_jp,
        [INS_CALL] = &exec_call,
        [INS_PUSH] = &exec_push,
        [INS_RST] = &exec_rst,
        [INS_LDH] = &exec_ldh,
        [INS_ADC] = &exec_adc,
        [INS_RETI] = &exec_reti,
        [INS_DI] = &exec_di,
        [INS_EI] = &exec_ei
};

Executor lookup_executor(Instruction *instruction) {
    return executors[instruction->type];
}