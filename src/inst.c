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
    [INST_CMP]      =   "cmp", // V
    [INST_JMP]      =   "jmp", // V
    [INST_JMPIF]    =   "jmpif",
    [INST_JZ]       =   "jz",
    [INST_JE]       =   "je",
    [INST_JG]       =   "jg",
    [INST_JGE]      =   "jge",
    [INST_JL]       =   "jl",
    [INST_JLE]      =   "jle",
    //
    [INST_CMPN]     =   "cmpn", // V
    [INST_JMPIFN]   =   "jmpifn",
    [INST_JNZ]      =   "jnz",
    [INST_JNE]      =   "jne",
    [INST_JNG]      =   "jng",
    [INST_JNGE]     =   "jnge",
    [INST_JNL]      =   "jnl",
    [INST_JNLE]     =   "jnle",
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
    [INST_FAPPEND]  =   "fappend",
    [INST_FSIZE]    =   "fsize",
    // cpu state
    [INST_DUMP_STACK]   =   "dumpstack",
    [INST_DUMP_MEM]     =   "dumpmem",
};

int Is_Inst(char *c) {
  for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++)
    if (strcmp(c, keywords[i]) == 0)
      return 1;
  return 0;
}

#endif
