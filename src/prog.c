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
        case ZORASM_N_POP: prog = (ZoraVM_Program)ZoraVM_Pop(); break;
        case ZORASM_N_STORE: {
            Zorasm_token_t token = tokens[(*c)++];
            assert(token.kind == ZORASM_TK_INT);
            prog = (ZoraVM_Program)ZoraVM_Store(atoll(token.value));
        } break;
        case ZORASM_N_LOAD: {
            Zorasm_token_t token = tokens[(*c)++];
            assert(token.kind == ZORASM_TK_INT);
            prog = (ZoraVM_Program)ZoraVM_Load(atoll(token.value));
        } break;
        case ZORASM_N_PRINT: prog = (ZoraVM_Program)ZoraVM_Print(); break;
        case ZORASM_N_INC: prog = (ZoraVM_Program)ZoraVM_Inc(); break;
        case ZORASM_N_DEC: prog = (ZoraVM_Program)ZoraVM_Dec(); break;
        case ZORASM_N_ADD: prog = (ZoraVM_Program)ZoraVM_Add(); break;
        case ZORASM_N_SUB: prog = (ZoraVM_Program)ZoraVM_Sub(); break;
        case ZORASM_N_MUL: prog = (ZoraVM_Program)ZoraVM_Mul(); break;
        case ZORASM_N_DIV: prog = (ZoraVM_Program)ZoraVM_Div(); break;
        case ZORASM_N_HALT: {
            Zorasm_token_t token = tokens[(*c)++];
            assert(token.kind == ZORASM_TK_INT);
            prog = (ZoraVM_Program)ZoraVM_Halt(atoll(token.value));
        } break;
        default: {assert(0 && "TODO:");}
    }

    return prog;
};

#endif