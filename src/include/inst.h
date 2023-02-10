#ifndef INST_H
#define INST_H

typedef enum {
  //sys
  INST_PUSH = 0,
  INST_POP,
  INST_STORE,
  INST_LOAD,
  INST_PRINT,
  INST_SCAN,
  INST_RET,
  INST_HALT,
  //arithmetic
  INST_ADD,
  INST_SUB,
  INST_MUL,
  INST_DIV,
  INST_MOD,
  //conditons
  INST_JMP,
  INST_CMP,
  INST_JZ,
  INST_JE,
  INST_JG,
  INST_JGE,
  INST_JL,
  INST_JLE,
  //
  INST_NCMP,
  INST_JNZ,
  INST_JNE,
  INST_JNL,
  INST_JNLE,
  INST_JNG,
  INST_JNGE,
  //debugging only
  INST_DUMP,
} Inst;

#endif
