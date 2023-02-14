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
    [INST_CMP_EQ]   =   "cmp_eq", // V
    [INST_CMP_GT]   =   "cmp_gt",
    [INST_CMP_LT]   =   "cmp_lt",
    [INST_CMP_GTE]  =   "cmp_gte",
    [INST_CMP_LTE]  =   "cmp_lte",
    //
    [INST_CMP_NEQ]  =   "cmp_neq", // V
    [INST_CMP_NGT]  =   "cmp_ngt",
    [INST_CMP_NLT]  =   "cmp_nlt",
    [INST_CMP_NGTE] =   "cmp_ngte",
    [INST_CMP_NLTE] =   "cmp_nlte",
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
    [INST_FSIZE]    =   "fsize",
    // cpu state
    [INST_DUMP_STACK]   =   "dump_stack",
    [INST_DUMP_MEM]     =   "dump_mem",
};

int Is_Inst(char *c) {
  for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++)
    if (strcmp(c, keywords[i]) == 0)
      return 1;
  return 0;
}

#endif
