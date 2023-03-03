#ifndef _INST_C
#define _INST_C

#include <string.h>

#include "./include/inst.h"

const char *keywords[] = {
    // V
    [INST_PUSH]     =   "push", // V
    [INST_POP]      =   "pop",  // V
    [INST_STORE]    =   "store", // V
    [INST_LOAD]     =   "load", // V
    [INST_PRINT]    =   "print", // V
    [INST_SCAN]     =   "scan", // V
    [INST_RET]      =   "ret", // v
    [INST_HALT]     =   "halt", //V
    //v
    [INST_DUP]      =   "dup",
    [INST_SWAP]     =   "swap",
    //v
    [INST_ADD]      =   "add",
    [INST_SUB]      =   "sub",
    [INST_MUL]      =   "mul",
    [INST_DIV]      =   "div",
    [INST_MOD]      =   "mod",
    //
    [INST_CMP_EQ]   =   "eq", // V
    [INST_CMP_GT]   =   "gt",
    [INST_CMP_LT]   =   "lt",
    [INST_CMP_GTE]  =   "gte",
    [INST_CMP_LTE]  =   "lte",
    //
    [INST_CMP_NEQ]  =   "neq", // V
    [INST_CMP_NGT]  =   "ngt",
    [INST_CMP_NLT]  =   "nlt",
    [INST_CMP_NGTE] =   "ngte",
    [INST_CMP_NLTE] =   "nlte",
    //
    [INST_JMP]      =   "jmp", // V
    [INST_JMPIF]    =   "jmpif",
    [INST_JMPIFN]   =   "jmpifn",
    //
    [INST_AND]      =   "and",
    [INST_OR]       =   "or",
    [INST_XOR]      =   "xor",
    [INST_NOT]      =   "not",
    [INST_NEG]      =   "neg",
    [INST_SHL]      =   "shl",
    [INST_SHR]      =   "shr",
    //
    [INST_INC]      =   "inc",
    [INST_DEC]      =   "dec",
    [INST_POW]      =   "pow",
    //
    [INST_FOPEN]    =   "fopen",
    [INST_FCLOSE]   =   "fclose",
    [INST_FREAD]    =   "fread",
    [INST_FWRITE]   =   "fwrite",

    [INST_SIZEOF]   =   "sizeof",
    // cpu state
    [INST_DUMP_STACK]   =   "_stack",
    [INST_DUMP_MEM]     =   "_mem",
};

int Is_Inst(char *c) {
  for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++)
    if (strcmp(c, keywords[i]) == 0)
      return 1;
  return 0;
}

#endif
