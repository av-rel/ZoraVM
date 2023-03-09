#ifndef ZORASM_KW_C
#define ZORASM_KW_C

#include <stdio.h>
#include <string.h>

#include "./kw.h"
#include "./token.h"
#include "../inc/utils.c"

char *Zorasm_Inst[] = {
    [ZORASM_INST_STORE]   =   "store",
    [ZORASM_INST_LOAD]    =   "load",
    [ZORASM_INST_PUSH]    =   "push",
    [ZORASM_INST_POP]     =   "pop",
    [ZORASM_INST_DUP]     =   "dup",
    [ZORASM_INST_SWAP]    =   "swap",

    [ZORASM_INST_PRINT]   =   "print",
    [ZORASM_INST_SCAN]    =   "scan",
    [ZORASM_INST_SIZEOF]  =   "sizeof",

    [ZORASM_INST_AND]     =   "and",
    [ZORASM_INST_OR]      =   "or",
    [ZORASM_INST_XOR]     =   "xor",
    [ZORASM_INST_NOT]     =   "not",
    [ZORASM_INST_NEG]     =   "neg",
    [ZORASM_INST_SHL]     =   "shl",
    [ZORASM_INST_SHR]     =   "shr",

    [ZORASM_INST_ADD]     =   "add",
    [ZORASM_INST_SUB]     =   "sub",
    [ZORASM_INST_MUL]     =   "mul",
    [ZORASM_INST_DIV]     =   "div",
    [ZORASM_INST_MOD]     =   "mod",
    [ZORASM_INST_POW]     =   "pow",
    [ZORASM_INST_INC]     =   "inc",
    [ZORASM_INST_DEC]     =   "dec",

    [ZORASM_INST_SIN]     =   "sin",
    [ZORASM_INST_COS]     =   "cos",
    [ZORASM_INST_TAN]     =   "tan",
    [ZORASM_INST_FACTORIAL]=  "fact",

    [ZORASM_INST_EQ]      =   "eq",
    [ZORASM_INST_GT]      =   "gt",
    [ZORASM_INST_LT]      =   "lt",
    [ZORASM_INST_GTE]     =   "gte",
    [ZORASM_INST_LTE]     =   "lte",
    [ZORASM_INST_NEQ]     =   "neq",
    [ZORASM_INST_NGT]     =   "ngt",
    [ZORASM_INST_NLT]     =   "nlt",
    [ZORASM_INST_NGTE]    =   "ngte",
    [ZORASM_INST_NLTE]    =   "nlte",

    [ZORASM_INST_CALL]    =   "call",
    [ZORASM_INST_CALLIF]  =   "callif",
    [ZORASM_INST_CALLIFN] =   "callifn",
    [ZORASM_INST_JMP]     =   "jmp",
    [ZORASM_INST_JMPIF]   =   "jmpif",
    [ZORASM_INST_JMPIFN]   =  "jmpifn",

    [ZORASM_INST_ENV]      =  "env",

    [ZORASM_INST_DUMP_STACK]= "dump_stack",
    [ZORASM_INST_DUMP_MEM] =  "dump_mem",

    [ZORASM_INST_RET]     =   "ret",
    [ZORASM_INST_HALT]    =   "halt"
};

char *Zorasm_Datakind[] = {
    [ZORASM_DATA_INT]     =   "int",
    [ZORASM_DATA_STRING]  =   "string",
    [ZORASM_DATA_FLOAT]   =   "float"
};

ZORASM_INST Zorasm_char_to_inst(char *s) {
  for (int i = 0; i < ZORASM_INST_HALT; i++)
    if (strcmp(s, Zorasm_Inst[i]) == 0)
      return i;
  return ZORASM_INST_HALT;
}

Zorasm_TokenKind Zorasm_inst_operand(ZORASM_INST zn) {
  switch (zn) {
    case ZORASM_INST_STORE:
    case ZORASM_INST_LOAD:
      return ZORASM_TK_REGISTER;

    case ZORASM_INST_PUSH:
      return ZORASM_TK_KIND;

    case ZORASM_INST_JMP:
    case ZORASM_INST_JMPIF:
    case ZORASM_INST_JMPIFN:
    case ZORASM_INST_CALL:
    case ZORASM_INST_CALLIF:
    case ZORASM_INST_CALLIFN:
      return ZORASM_TK_LABEL;

    case ZORASM_INST_RET:
    case ZORASM_INST_HALT:
      return ZORASM_TK_INT;

    default: return ZORASM_TK_NONE;
  }
  return ZORASM_TK_NONE;
}

Zorasm_TokenKind Zorasm_inst_op(char* native) {
    unsigned int i, len = sizeof(Zorasm_Inst)/sizeof(Zorasm_Inst[0]) ;
    for (i = 0; i < len ; i++)
        if (strcmp(native, Zorasm_Inst[i]) == 0) 
            return Zorasm_inst_operand(i);
    return ZORASM_TK_NONE;
}

ZORASM_DATAKIND Zorasm_tk_to_dk(Zorasm_TokenKind kind){
  ZORASM_DATAKIND data = {0};
  if (kind == ZORASM_TK_STRING) return ZORASM_DATA_STRING;
  else if  (kind == ZORASM_TK_INT) return ZORASM_DATA_STRING;
  else if (kind == ZORASM_TK_FLOAT) return ZORASM_DATA_STRING;
  else return ((data = -69));
}

int Zorasm_is_inst(char *str) {
  unsigned int i;
  for (i = 0; i < (sizeof(Zorasm_Inst)/sizeof(Zorasm_Inst[0])); i++) 
    if (strcmp(str, Zorasm_Inst[i]) == 0) return 1;
  return 0;
}

int Zorasm_is_register(char *str) {
  unsigned int i;
  for (i = 0; i < strlen(str); i++) {
    if (!Zora_is_digit(str[i])) return 0;
  }
  return 1;
}

int Zorasm_is_datakind(char *str) {
  int data = 0;
  unsigned int i;
  for (i = 0; i < sizeof(Zorasm_Datakind)/sizeof(Zorasm_Datakind[0]); i++) if (strcmp(str, Zorasm_Datakind[i]) == 0) ++data;
  return data;
}

void Zorasm_print_all_insts() {
  unsigned int i, len  = sizeof(Zorasm_Inst)/sizeof(Zorasm_Inst[0]);
  for (i = 0; i < len ; i++) {
    printf("%s", Zorasm_Inst[i]);
    if (i != len - 1) printf(", ");
  }
  printf("\n");
}

void Zorasm_print_all_datakind() {
  unsigned int i, len = sizeof(Zorasm_Datakind)/sizeof(Zorasm_Datakind[0]);
  for (i = 0; i < len; i++) {
    printf("%s", Zorasm_Datakind[i]);
    if (i != len - 1) printf(", ");
  }
  printf("\n");
}

#endif
