#ifndef ZORAVM_PROG_C
#define ZORAVM_PROG_C

#include "../Zorasm/src/zorasm.c"
#include "./zoravm.h"
#include "./inst.h"
#include <assert.h>
#include <stdlib.h>

ZoraVM_Program ZoraVM_Parse_Native(ZORASM_NATIVES native, Zorasm_token_t* tokens, unsigned int* c);

int ZoraVM_Program_from_tokens(Zorasm_token_t* tokens, unsigned int ctok , ZoraVM_Program* program) {
    unsigned int c = 0, progc = 0;
    Zorasm_token_t token = tokens[c++];

    for (; token.kind != ZORASM_TK_EOF;) {
        if (token.kind == ZORASM_TK_NATIVE) {
            ZORASM_NATIVES native = Zorasm_char_to_native(token.value);
            program[progc++] = ZoraVM_Parse_Native(native, tokens, &c);
        }
        token = tokens[c++];
    }
    return progc;
}

ZoraVM_Program ZoraVM_Parse_Native(ZORASM_NATIVES native, Zorasm_token_t* tokens, unsigned int* c) {
    ZoraVM_Program prog = {0};

    switch (native) {
        case ZORASM_N_PUSH: {
            Zorasm_token_t token = tokens[(*c)++];
            if (token.kind == ZORASM_TK_INT) prog = (ZoraVM_Program)ZoraVM_PushInt(atoll(token.value));
            else if (token.kind == ZORASM_TK_FLOAT) prog = (ZoraVM_Program)ZoraVM_PushFloat(atof(token.value));
            else prog = (ZoraVM_Program)ZoraVM_PushStr(token.value);
        } break;
        case ZORASM_N_STORE: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Store(atoll(token.value));
        } break;
        case ZORASM_N_LOAD: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Load(atoll(token.value));
        } break;
        case ZORASM_N_CALL: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Call(atoll(token.value));
        } break;
        case ZORASM_N_CALLIF: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_CallIf(atoll(token.value));
        } break;
        case ZORASM_N_CALLIFN: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_CallIfNot(atoll(token.value));
        } break;
        case ZORASM_N_JMP: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Jmp(atoll(token.value));
        } break;
        case ZORASM_N_JMPIF: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_JmpIf(atoll(token.value));
        } break;
        case ZORASM_N_JMPIFN: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_JmpIfNot(atoll(token.value));
        } break;
        case ZORASM_N_RET: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Ret(atoll(token.value));
        } break;
        case ZORASM_N_HALT: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Halt(atoll(token.value));
        } break;
        case ZORASM_N_SIZEOF: prog = (ZoraVM_Program)ZoraVM_SizeOf(); break;
        case ZORASM_N_PRINT: prog = (ZoraVM_Program)ZoraVM_Print(); break;
        case ZORASM_N_SCAN: prog = (ZoraVM_Program)ZoraVM_Scan(); break;
        case ZORASM_N_DUP: prog = (ZoraVM_Program)ZoraVM_Dup(); break;
        case ZORASM_N_SWAP: prog = (ZoraVM_Program)ZoraVM_Swap(); break;
        case ZORASM_N_POP: prog = (ZoraVM_Program)ZoraVM_Pop(); break;
        case ZORASM_N_INC: prog = (ZoraVM_Program)ZoraVM_Inc(); break;
        case ZORASM_N_DEC: prog = (ZoraVM_Program)ZoraVM_Dec(); break;
        case ZORASM_N_POW: prog = (ZoraVM_Program)ZoraVM_Pow(); break;
        case ZORASM_N_ADD: prog = (ZoraVM_Program)ZoraVM_Add(); break;
        case ZORASM_N_SUB: prog = (ZoraVM_Program)ZoraVM_Sub(); break;
        case ZORASM_N_MUL: prog = (ZoraVM_Program)ZoraVM_Mul(); break;
        case ZORASM_N_DIV: prog = (ZoraVM_Program)ZoraVM_Div(); break;
        case ZORASM_N_MOD: prog = (ZoraVM_Program)ZoraVM_Mod(); break;
        case ZORASM_N_AND: prog = (ZoraVM_Program)ZoraVM_And(); break;
        case ZORASM_N_OR: prog = (ZoraVM_Program)ZoraVM_Or(); break;
        case ZORASM_N_XOR: prog = (ZoraVM_Program)ZoraVM_Xor(); break;
        case ZORASM_N_NOT: prog = (ZoraVM_Program)ZoraVM_Not(); break;
        case ZORASM_N_NEG: prog = (ZoraVM_Program)ZoraVM_Neg(); break;
        case ZORASM_N_SHL: prog = (ZoraVM_Program)ZoraVM_Shl(); break;
        case ZORASM_N_SHR: prog = (ZoraVM_Program)ZoraVM_Shr(); break;
        case ZORASM_N_EQ: prog = (ZoraVM_Program)ZoraVM_CmpEq(); break;
        case ZORASM_N_GT: prog = (ZoraVM_Program)ZoraVM_CmpGt(); break;
        case ZORASM_N_GTE: prog = (ZoraVM_Program)ZoraVM_CmpGte(); break;
        case ZORASM_N_LT: prog = (ZoraVM_Program)ZoraVM_CmpLt(); break;
        case ZORASM_N_LTE: prog = (ZoraVM_Program)ZoraVM_CmpLte(); break;
        case ZORASM_N_NEQ: prog = (ZoraVM_Program)ZoraVM_CmpNeq(); break;
        case ZORASM_N_NGT: prog = (ZoraVM_Program)ZoraVM_CmpNotGt(); break;
        case ZORASM_N_NGTE: prog = (ZoraVM_Program)ZoraVM_CmpNotGte(); break;
        case ZORASM_N_NLT: prog = (ZoraVM_Program)ZoraVM_CmpNotLt(); break;
        case ZORASM_N_NLTE: prog = (ZoraVM_Program)ZoraVM_CmpNotLte(); break;
        case ZORASM_N_DUMP_STACK: prog = (ZoraVM_Program)ZoraVM_DumpStack(); break;
        case ZORASM_N_DUMP_MEM: prog = (ZoraVM_Program)ZoraVM_DumpMem(); break;
        default: {assert(0 && "Unimplemented");}
    }

    return prog;
};

#endif