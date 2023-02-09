#ifndef OP_H
#define OP_H

typedef enum {
  OP_DEBUG,
  OP_NONE,
  OP_STORE,
  OP_LOAD,
  OP_RET,
  OP_PRINT,
  OP_SCAN,
  OP_HALT,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_MOD,
  OP_JMP,
  OP_CMP,
  OP_NCMP,
  OP_JZ,
  OP_JNZ,
  OP_JE,
  OP_JNE,
  OP_JG,
  OP_JGE,
  OP_JL,
  OP_JLE,
} OP;

#endif
