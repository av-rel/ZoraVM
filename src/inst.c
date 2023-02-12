#ifndef _INST_C
#define _INST_C

#include <string.h>

#include "./include/inst.h"

const char *keywords[] = {
    [INST_PUSH]     =   "push",
    [INST_POP]      =   "pop", 
    [INST_STORE]    =   "store",
    [INST_LOAD]     =   "load",
    [INST_PRINT]    =   "print",
    [INST_SCAN]     =   "scan",
    [INST_RET]      =   "ret",
    [INST_HALT]     =   "halt",
    //
    [INST_DUP]      =   "dup",
    [INST_SWAP]     =   "swap",
    //
    [INST_ADD]      =   "add",
    [INST_SUB]      =   "sub",
    [INST_MUL]      =   "mul",
    [INST_DIV]      =   "div",
    [INST_MOD]      =   "mod",
    //
    [INST_CMP]      =   "cmp",
    [INST_JMP]      =   "jmp",
    [INST_JMPIF]    =   "jmpif",
    [INST_JZ]       =   "jz",
    [INST_JE]       =   "je",
    [INST_JG]       =   "jg",
    [INST_JGE]      =   "jge",
    [INST_JL]       =   "jl",
    [INST_JLE]      =   "jle",
    //
    [INST_NCMP]     =   "ncmp",
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
