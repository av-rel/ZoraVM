#ifndef ZORAVM_INST_C
#define ZORAVM_INST_C

#include "./inst.h"

char *ZoraVM_Inst[] = {
    [ZORAVM_INST_STORE]   =   "store",
    [ZORAVM_INST_LOAD]    =   "load",
    [ZORAVM_INST_PUSH]    =   "push",
    [ZORAVM_INST_POP]     =   "pop",
    [ZORAVM_INST_DUP]     =   "dup",
    [ZORAVM_INST_SWAP]    =   "swap",

    [ZORAVM_INST_PRINT]   =   "print",
    [ZORAVM_INST_SCAN]    =   "scan",
    [ZORAVM_INST_SIZEOF]  =   "sizeof",

    [ZORAVM_INST_AND]     =   "and",
    [ZORAVM_INST_OR]      =   "or",
    [ZORAVM_INST_XOR]     =   "xor",
    [ZORAVM_INST_NOT]     =   "not",
    [ZORAVM_INST_NEG]     =   "neg",
    [ZORAVM_INST_SHL]     =   "shl",
    [ZORAVM_INST_SHR]     =   "shr",

    [ZORAVM_INST_ADD]     =   "add",
    [ZORAVM_INST_SUB]     =   "sub",
    [ZORAVM_INST_MUL]     =   "mul",
    [ZORAVM_INST_DIV]     =   "div",
    [ZORAVM_INST_MOD]     =   "mod",
    [ZORAVM_INST_POW]     =   "pow",
    [ZORAVM_INST_INC]     =   "inc",
    [ZORAVM_INST_DEC]     =   "dec",

    [ZORAVM_INST_SIN]     =   "sin",
    [ZORAVM_INST_COS]     =   "cos",
    [ZORAVM_INST_TAN]     =   "tan",
    [ZORAVM_INST_FACTORIAL]=  "fact",

    [ZORAVM_INST_EQ]      =   "eq",
    [ZORAVM_INST_GT]      =   "gt",
    [ZORAVM_INST_LT]      =   "lt",
    [ZORAVM_INST_GTE]     =   "gte",
    [ZORAVM_INST_LTE]     =   "lte",
    [ZORAVM_INST_NEQ]     =   "neq",
    [ZORAVM_INST_NGT]     =   "ngt",
    [ZORAVM_INST_NLT]     =   "nlt",
    [ZORAVM_INST_NGTE]    =   "ngte",
    [ZORAVM_INST_NLTE]    =   "nlte",

    [ZORAVM_INST_CALL]    =   "call",
    [ZORAVM_INST_CALLIF]  =   "callif",
    [ZORAVM_INST_CALLIFN] =   "callifn",
    [ZORAVM_INST_JMP]     =   "jmp",
    [ZORAVM_INST_JMPIF]   =   "jmpif",
    [ZORAVM_INST_JMPIFN]   =  "jmpifn",

    [ZORAVM_INST_ENV]      =  "env",

    [ZORAVM_INST_DUMP_STACK]= "dump_stack",
    [ZORAVM_INST_DUMP_MEM] =  "dump_mem",

    [ZORAVM_INST_RET]     =   "ret",
    [ZORAVM_INST_HALT]    =   "halt"
};

char *ZoraVM_DataKind[] = {
    [ZORAVM_DATA_INT]     =   "int",
    [ZORAVM_DATA_STRING]  =   "string",
    [ZORAVM_DATA_FLOAT]   =   "float"
};

#endif
