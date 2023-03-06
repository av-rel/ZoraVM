#ifndef _ZORAVM_INST_C
#define _ZORAVM_INST_C

#include <string.h>
#include "./inst.h"

const char *ZoraVM_keywords[] = {
    [ZORAVM_INST_PUSH]     =   "push", // V
    [ZORAVM_INST_POP]      =   "pop",  // V
    [ZORAVM_INST_STORE]    =   "store", // V
    [ZORAVM_INST_LOAD]     =   "load", // V
    [ZORAVM_INST_PRINT]    =   "print", // V
    [ZORAVM_INST_SCAN]     =   "scan", // V
    [ZORAVM_INST_RET]      =   "ret", // v
    [ZORAVM_INST_HALT]     =   "halt", //V
    //v
    [ZORAVM_INST_DUP]      =   "dup",
    [ZORAVM_INST_SWAP]     =   "swap",
    //v
    [ZORAVM_INST_ADD]      =   "add",
    [ZORAVM_INST_SUB]      =   "sub",
    [ZORAVM_INST_MUL]      =   "mul",
    [ZORAVM_INST_DIV]      =   "div",
    [ZORAVM_INST_MOD]      =   "mod",
    //
    [ZORAVM_INST_CMP_EQ]   =   "eq", // V
    [ZORAVM_INST_CMP_GT]   =   "gt",
    [ZORAVM_INST_CMP_LT]   =   "lt",
    [ZORAVM_INST_CMP_GTE]  =   "gte",
    [ZORAVM_INST_CMP_LTE]  =   "lte",
    //
    [ZORAVM_INST_CMP_NEQ]  =   "neq", // V
    [ZORAVM_INST_CMP_NGT]  =   "ngt",
    [ZORAVM_INST_CMP_NLT]  =   "nlt",
    [ZORAVM_INST_CMP_NGTE] =   "ngte",
    [ZORAVM_INST_CMP_NLTE] =   "nlte",
    //
    [ZORAVM_INST_JMP]      =   "jmp", // V
    [ZORAVM_INST_JMPIF]    =   "jmpif",
    [ZORAVM_INST_JMPIFN]   =   "jmpifn",
    //
    [ZORAVM_INST_AND]      =   "and",
    [ZORAVM_INST_OR]       =   "or",
    [ZORAVM_INST_XOR]      =   "xor",
    [ZORAVM_INST_NOT]      =   "not",
    [ZORAVM_INST_NEG]      =   "neg",
    [ZORAVM_INST_SHL]      =   "shl",
    [ZORAVM_INST_SHR]      =   "shr",
    //
    [ZORAVM_INST_INC]      =   "inc",
    [ZORAVM_INST_DEC]      =   "dec",
    [ZORAVM_INST_POW]      =   "pow",
    //
    [ZORAVM_INST_FOPEN]    =   "fopen",
    [ZORAVM_INST_FCLOSE]   =   "fclose",
    [ZORAVM_INST_FREAD]    =   "fread",
    [ZORAVM_INST_FWRITE]   =   "fwrite",

    [ZORAVM_INST_SIZEOF]   =   "sizeof",
    // cpu state
    [ZORAVM_INST_DUMP_STACK]   =   "_stack",
    [ZORAVM_INST_DUMP_MEM]     =   "_mem",
};

int ZoraVM_Is_Inst(char *c) {
  for (int i = 0; i < sizeof(ZoraVM_keywords)/sizeof(ZoraVM_keywords[0]); i++)
    if (strcmp(c, ZoraVM_keywords[i]) == 0)
      return 1;
  return 0;
}

#endif
