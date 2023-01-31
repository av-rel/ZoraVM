#ifndef VM_H
#define VM_H

#include <stdint.h>
#include "../source/op.c"

#define ArraySize(ele) (int)sizeof(ele) / sizeof(ele[0])

typedef struct {
  int* globals;
  int ip;
} Zvm;

typedef struct {
  OP_Type type;
} Inst;

typedef struct {
  OP_Type inst;
  int val;
} Program;

#endif
