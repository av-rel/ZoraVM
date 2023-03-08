#ifndef ZORAVM_PROG_C
#define ZORAVM_PROG_C

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "./zoravm.h"
#include "./inst.h"
#include "../zorasm/token.h"
#include "../zorasm/kw.h"

ZoraVM_Program ZoraVM_Parse_Inst(ZORASM_INST inst, Zorasm_token_t* tokens, unsigned int* c);

int ZoraVM_Program_from_tokens(Zorasm_token_t* tokens, unsigned int ctok , ZoraVM_Program* program) {
    unsigned int c = 0, progc = 0;
    Zorasm_token_t token = tokens[c++];

    for (; token.kind != ZORASM_TK_EOF;) {
        if (token.kind == ZORASM_TK_NATIVE) {
            ZORASM_INST inst = Zorasm_char_to_inst(token.value);
            program[progc++] = ZoraVM_Parse_Inst(inst, tokens, &c);
        }
        token = tokens[c++];
    }
    return progc;
}

ZoraVM_Program ZoraVM_Parse_Inst(ZORASM_INST inst, Zorasm_token_t* tokens, unsigned int* c) {
    ZoraVM_Program prog = {0};

    switch (inst) {
        case ZORASM_INST_PUSH: {
            Zorasm_token_t token = tokens[(*c)++];
            if (token.kind == ZORASM_TK_INT) prog = (ZoraVM_Program)ZoraVM_PushInt(atoll(token.value));
            else if (token.kind == ZORASM_TK_FLOAT) prog = (ZoraVM_Program)ZoraVM_PushFloat(atof(token.value));
            else prog = (ZoraVM_Program)ZoraVM_PushStr(token.value);
        } break;
        case ZORASM_INST_STORE: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Store(atoll(token.value));
        } break;
        case ZORASM_INST_LOAD: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Load(atoll(token.value));
        } break;
        case ZORASM_INST_CALL: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Call(atoll(token.value));
        } break;
        case ZORASM_INST_CALLIF: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_CallIf(atoll(token.value));
        } break;
        case ZORASM_INST_CALLIFN: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_CallIfNot(atoll(token.value));
        } break;
        case ZORASM_INST_JMP: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Jmp(atoll(token.value));
        } break;
        case ZORASM_INST_JMPIF: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_JmpIf(atoll(token.value));
        } break;
        case ZORASM_INST_JMPIFN: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_JmpIfNot(atoll(token.value));
        } break;
        case ZORASM_INST_RET: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Ret(atoll(token.value));
        } break;
        case ZORASM_INST_HALT: {
            Zorasm_token_t token = tokens[(*c)++];
            prog = (ZoraVM_Program)ZoraVM_Halt(atoll(token.value));
        } break;
        case ZORASM_INST_SIZEOF: prog = (ZoraVM_Program)ZoraVM_SizeOf(); break;
        case ZORASM_INST_PRINT: prog = (ZoraVM_Program)ZoraVM_Print(); break;
        case ZORASM_INST_SCAN: prog = (ZoraVM_Program)ZoraVM_Scan(); break;
        case ZORASM_INST_DUP: prog = (ZoraVM_Program)ZoraVM_Dup(); break;
        case ZORASM_INST_SWAP: prog = (ZoraVM_Program)ZoraVM_Swap(); break;
        case ZORASM_INST_POP: prog = (ZoraVM_Program)ZoraVM_Pop(); break;
        case ZORASM_INST_INC: prog = (ZoraVM_Program)ZoraVM_Inc(); break;
        case ZORASM_INST_DEC: prog = (ZoraVM_Program)ZoraVM_Dec(); break;
        case ZORASM_INST_POW: prog = (ZoraVM_Program)ZoraVM_Pow(); break;
        case ZORASM_INST_ADD: prog = (ZoraVM_Program)ZoraVM_Add(); break;
        case ZORASM_INST_SUB: prog = (ZoraVM_Program)ZoraVM_Sub(); break;
        case ZORASM_INST_MUL: prog = (ZoraVM_Program)ZoraVM_Mul(); break;
        case ZORASM_INST_DIV: prog = (ZoraVM_Program)ZoraVM_Div(); break;
        case ZORASM_INST_MOD: prog = (ZoraVM_Program)ZoraVM_Mod(); break;
        case ZORASM_INST_AND: prog = (ZoraVM_Program)ZoraVM_And(); break;
        case ZORASM_INST_OR: prog = (ZoraVM_Program)ZoraVM_Or(); break;
        case ZORASM_INST_XOR: prog = (ZoraVM_Program)ZoraVM_Xor(); break;
        case ZORASM_INST_NOT: prog = (ZoraVM_Program)ZoraVM_Not(); break;
        case ZORASM_INST_NEG: prog = (ZoraVM_Program)ZoraVM_Neg(); break;
        case ZORASM_INST_SHL: prog = (ZoraVM_Program)ZoraVM_Shl(); break;
        case ZORASM_INST_SHR: prog = (ZoraVM_Program)ZoraVM_Shr(); break;
        case ZORASM_INST_EQ: prog = (ZoraVM_Program)ZoraVM_CmpEq(); break;
        case ZORASM_INST_GT: prog = (ZoraVM_Program)ZoraVM_CmpGt(); break;
        case ZORASM_INST_GTE: prog = (ZoraVM_Program)ZoraVM_CmpGte(); break;
        case ZORASM_INST_LT: prog = (ZoraVM_Program)ZoraVM_CmpLt(); break;
        case ZORASM_INST_LTE: prog = (ZoraVM_Program)ZoraVM_CmpLte(); break;
        case ZORASM_INST_NEQ: prog = (ZoraVM_Program)ZoraVM_CmpNeq(); break;
        case ZORASM_INST_NGT: prog = (ZoraVM_Program)ZoraVM_CmpNotGt(); break;
        case ZORASM_INST_NGTE: prog = (ZoraVM_Program)ZoraVM_CmpNotGte(); break;
        case ZORASM_INST_NLT: prog = (ZoraVM_Program)ZoraVM_CmpNotLt(); break;
        case ZORASM_INST_NLTE: prog = (ZoraVM_Program)ZoraVM_CmpNotLte(); break;
        case ZORASM_INST_DUMP_STACK: prog = (ZoraVM_Program)ZoraVM_DumpStack(); break;
        case ZORASM_INST_DUMP_MEM: prog = (ZoraVM_Program)ZoraVM_DumpMem(); break;
        default: {assert(0 && "Unimplemented");}
    }

    return prog;
}

#endif
