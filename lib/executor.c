#include "executor.h"

/**
 *     FL_ZERO,
    FL_NSUB,
    FL_HALT,
    FL_CARRY

 * @param ctx
 * @param flag_z
 */

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
    TODO
}

void exec_add(CPU_context *ctx) {
    TODO
}

void exec_ld(CPU_context *ctx) {
    Addressing addressing = ctx->instruction->addressing;
    if (addressing == ADD_REG_REG) {
        set_8bit_register_val(ctx->instruction->reg_1, ctx->operand_two);
    } else {
        TODO
    }
}

void exec_xor(CPU_context *ctx) {
    TODO
}

void exec_rrca(CPU_context *ctx) {
    TODO
}

void exec_dec(CPU_context *ctx) {
    TODO
}

void exec_inc(CPU_context *ctx) {
    TODO
}

void exec_rlca(CPU_context *ctx) {
    TODO
}

void exec_nop(CPU_context *ctx) {
    // nothing to do
}

void exec_or(CPU_context *ctx) {
    TODO
}

// can be executed only for register A
void exec_cp(CPU_context *ctx) {
    int8_t n = (int8_t) ctx->registers.A - (int8_t) ctx->operand_one;
    int8_t halt = ((int8_t) ctx->registers.A & 0x0F) - ((int8_t) ctx->operand_one & 0x0F) < 0;
    set_flags(ctx, n == 0, 1, halt, n < 0);
}

void exec_rra(CPU_context *ctx) {
    TODO
}

void exec_stop(CPU_context *ctx) {
    TODO
}

void exec_jr(CPU_context *ctx) {
    TODO
}

void exec_rla(CPU_context *ctx) {
    TODO
}

void exec_jp(CPU_context *ctx) {
    Addressing addressing = ctx->instruction->addressing;
    if (addressing == ADD_REG) {
        ctx->registers.PC = ctx->operand_one;
    } else if (addressing == ADD_A16) {
        ctx->registers.PC = ctx->operand_one;
    } else {
        printf("Not implemented! exec_jp for %x", addressing);
        TODO
    }
}

void exec_pop(CPU_context *ctx) {
    TODO
}

void exec_ret(CPU_context *ctx) {
    TODO
}

void exec_cpl(CPU_context *ctx) {
    TODO
}

void exec_rst(CPU_context *ctx) {
    TODO
}

void exec_push(CPU_context *ctx) {
    TODO
}

void exec_call(CPU_context *ctx) {
    TODO
}

void exec_daa(CPU_context *ctx) {
    TODO
}

void exec_reti(CPU_context *ctx) {
    TODO
}

void exec_ccf(CPU_context *ctx) {
    TODO
}

void exec_sub(CPU_context *ctx) {
    TODO
}

void exec_scf(CPU_context *ctx) {
    TODO
}

void exec_adc(CPU_context *ctx) {
    TODO
}

void exec_ldh(CPU_context *ctx) {
    TODO
}

void exec_sbc(CPU_context *ctx) {
    TODO
}

void exec_di(CPU_context *ctx) {
    TODO
}

void exec_ei(CPU_context *ctx) {
    TODO
}

void exec_halt(CPU_context *ctx) {
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