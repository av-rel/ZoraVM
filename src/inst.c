#ifndef OP_C
#define OP_C

#include <stdbool.h>
#include <stdint.h>
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
    [INST_ADD]      =   "add",
    [INST_SUB]      =   "sub",
    [INST_MUL]      =   "mul",
    [INST_DIV]      =   "div",
    [INST_MOD]      =   "mod",
    //
    [INST_JMP]      =   "jmp",
    [INST_CMP]      =   "cmp",
    [INST_JZ]       =   "jz",
    [INST_JE]       =   "je",
    [INST_JG]       =   "jg",
    [INST_JGE]      =   "jge",
    [INST_JL]       =   "jl",
    [INST_JLE]      =   "jle",
    //
    [INST_NCMP]     =   "ncmp",
    [INST_JNZ]      =   "jnz",
    [INST_JNE]      =   "jne",
    [INST_JNG]      =   "jng",
    [INST_JNGE]     =   "jnge",
    [INST_JNL]      =   "jnl",
    [INST_JNLE]     =   "jnle",
};


_Bool is_inst(char *c) {
  for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++)
    if (strcmp(c, keywords[i]) == 0)
      return true;
  return false;
}

#endif
