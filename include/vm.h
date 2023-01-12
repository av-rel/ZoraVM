#ifndef ZVM_H
#define ZVM_H

#include <stdint.h>

#define STACK_SIZE 1024

typedef enum {
  OP_PUSH,
  OP_POP,
  OP_MOVE,
  OP_DUP,
  OP_SWAP,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_MOD,
  OP_POW,
  OP_PRINT,
  OP_SCAN,
  OP_NONE,
  OP_HALT,
  OP_LOG
} OP_Type;

typedef struct {
  int stack[STACK_SIZE];
  int size;
  int ip;
} Zvm;

typedef struct {
  OP_Type type;
  int op;
} Inst;

#endif