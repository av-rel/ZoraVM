#ifndef ZORASM_KEYWORDS_C
#define ZORASM_KEYWORDS_C

#include <stdio.h>
#include <string.h>

#include "./lexer.c"
#include "./token.h"

#define ZORASM_ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

typedef enum {
  ZORASM_N_STORE = 0,
  ZORASM_N_LOAD,
  ZORASM_N_PUSH,
  ZORASM_N_POP,
  ZORASM_N_DUP,
  ZORASM_N_SWAP,
  ZORASM_N_PRINT,
  ZORASM_N_SCAN,
  ZORASM_N_SIZEOF,
  ZORASM_N_AND,
  ZORASM_N_OR,
  ZORASM_N_XOR,
  ZORASM_N_NOT,
  ZORASM_N_NEG,
  ZORASM_N_SHL,
  ZORASM_N_SHR,
  ZORASM_N_ADD,
  ZORASM_N_SUB,
  ZORASM_N_MUL,
  ZORASM_N_DIV,
  ZORASM_N_MOD,
  ZORASM_N_POW,
  ZORASM_N_INC,
  ZORASM_N_DEC,
  ZORASM_N_EQ,
  ZORASM_N_GT,
  ZORASM_N_LT,
  ZORASM_N_GTE,
  ZORASM_N_LTE,
  ZORASM_N_NEQ,
  ZORASM_N_NGT,
  ZORASM_N_NLT,
  ZORASM_N_NGTE,
  ZORASM_N_NLTE,
  ZORASM_N_JMP,
  ZORASM_N_JMPIF,
  ZORASM_N_JMPIFN,
  ZORASM_N_CALL,
  ZORASM_N_CALLIF,
  ZORASM_N_CALLIFN,
  ZORASM_N_RET,
  ZORASM_N_HALT,
} ZORASM_NATIVES;

enum ZORASM_DATAKIND {
  ZORASM_D_INT,
  ZORASM_D_STRING,
  ZORASM_D_FLOAT
};

char *Zorasm_Native[] = {
    [ZORASM_N_STORE]   =   "store",
    [ZORASM_N_LOAD]    =   "load",
    [ZORASM_N_PUSH]    =   "push",
    [ZORASM_N_POP]     =   "pop",
    [ZORASM_N_DUP]     =   "dup",
    [ZORASM_N_SWAP]    =   "swap",
    [ZORASM_N_PRINT]   =   "print",
    [ZORASM_N_SCAN]    =   "scan",
    [ZORASM_N_SIZEOF]  =   "sizeof",
    [ZORASM_N_AND]     =   "and",
    [ZORASM_N_OR]      =   "or",
    [ZORASM_N_XOR]     =   "xor",
    [ZORASM_N_NOT]     =   "not",
    [ZORASM_N_NEG]     =   "neg",
    [ZORASM_N_SHL]     =   "shl",
    [ZORASM_N_SHR]     =   "shr",
    [ZORASM_N_ADD]     =   "add",
    [ZORASM_N_SUB]     =   "sub",
    [ZORASM_N_MUL]     =   "mul",
    [ZORASM_N_DIV]     =   "div",
    [ZORASM_N_MOD]     =   "mod",
    [ZORASM_N_POW]     =   "pow",
    [ZORASM_N_INC]     =   "inc",
    [ZORASM_N_DEC]     =   "dec",
    [ZORASM_N_EQ]      =   "eq",
    [ZORASM_N_GT]      =   "gt",
    [ZORASM_N_LT]      =   "lt",
    [ZORASM_N_GTE]     =   "gte",
    [ZORASM_N_LTE]     =   "lte",
    [ZORASM_N_NEQ]     =   "neq",
    [ZORASM_N_NGT]     =   "ngt",
    [ZORASM_N_NLT]     =   "nlt",
    [ZORASM_N_NGTE]    =   "ngte",
    [ZORASM_N_NLTE]    =   "nlte",
    [ZORASM_N_CALL]    =   "call",
    [ZORASM_N_CALLIF]  =   "callif",
    [ZORASM_N_CALLIFN] =   "callifn",
    [ZORASM_N_JMP]     =   "jmp",
    [ZORASM_N_JMPIF]   =   "jmpif",
    [ZORASM_N_JMPIFN]   =  "jmpifn",
    [ZORASM_N_RET]     =   "ret",
    [ZORASM_N_HALT]    =   "halt"
};

char *Zorasm_Datakind[] = {
    [ZORASM_D_INT]     =   "int",
    [ZORASM_D_STRING]  =   "string",
    [ZORASM_D_FLOAT]   =   "float"
};

ZORASM_NATIVES Zorasm_char_to_native(char *s) {
  for (int i = 0; i < ZORASM_N_HALT; i++) {
    if (strcmp(s, Zorasm_Native[i]) == 0) {
      return i;
    }
  }
  return ZORASM_N_HALT;
}

Zorasm_TokenKind Zorasm_native_operand(ZORASM_NATIVES zn) {
  switch (zn) {
    case ZORASM_N_STORE:
    case ZORASM_N_LOAD:
      return ZORASM_TK_REGISTER;
    case ZORASM_N_PUSH:
      return ZORASM_TK_KIND;
    case ZORASM_N_JMP:
    case ZORASM_N_JMPIF:
    case ZORASM_N_JMPIFN:
    case ZORASM_N_CALL:
    case ZORASM_N_CALLIF:
    case ZORASM_N_CALLIFN:
      return ZORASM_TK_LABEL;
    case ZORASM_N_RET:
    case ZORASM_N_HALT:
      return ZORASM_TK_INT;
    default: return ZORASM_TK_NONE;
  }
  return ZORASM_TK_NONE;
}

Zorasm_TokenKind Zorasm_n_to_op(char* native) {
    unsigned int i;
    for (i = 0; i < ZORASM_ARR_SIZE(Zorasm_Native); i++)
        if (strcmp(native, Zorasm_Native[i]) == 0) 
            return Zorasm_native_operand(i);
    return ZORASM_TK_NONE;
}

enum ZORASM_DATAKIND Zorasm_tk_to_dk(Zorasm_TokenKind kind){
  enum ZORASM_DATAKIND data = {0};
  if (kind == ZORASM_TK_STRING) return ZORASM_D_STRING;
  else if  (kind == ZORASM_TK_INT) return ZORASM_D_STRING;
  else if (kind == ZORASM_TK_FLOAT) return ZORASM_D_STRING;
  else return ((data = -69));
}

int Zorasm_is_native(char *str) {
  unsigned int i;
  for (i = 0; i < (ZORASM_ARR_SIZE(Zorasm_Native)); i++) 
    if (strcmp(str, Zorasm_Native[i]) == 0) return 1;
  return 0;
}

int Zorasm_is_register(char *str) {
  unsigned int i;
  for (i = 0; i < strlen(str); i++) {
    if (!Zorasm_is_digit(str[i])) return 0;
  }
  return 1;
}

int Zorasm_is_datakind(char *str) {
  int data = 0;
  unsigned int i;
  for (i = 0; i < ZORASM_ARR_SIZE(Zorasm_Datakind); i++) if (strcmp(str, Zorasm_Datakind[i]) == 0) ++data;
  return data;
}

void Zorasm_print_all_natives() {
  unsigned int i;
  for (i = 0; i < ZORASM_ARR_SIZE(Zorasm_Native); i++) {
    printf("%s", Zorasm_Native[i]);
    if (i != ZORASM_ARR_SIZE(Zorasm_Native) - 1) printf(", ");
  }
  printf("\n");
}

void Zorasm_print_all_datakind() {
  unsigned int i;
  for (i = 0; i < ZORASM_ARR_SIZE(Zorasm_Datakind); i++) {
    printf("%s", Zorasm_Datakind[i]);
    if (i != ZORASM_ARR_SIZE(Zorasm_Datakind) - 1) printf(", ");
  }
  printf("\n");
}

#endif
