#ifndef VM_H
#define VM_H

#include <stdint.h>
#include "./op.h"

#define ArraySize(ele) (int)sizeof(ele) / sizeof(ele[0])

typedef struct {
  int* globals;
  int ip;
  int len;
} Zvm;

typedef struct {
  OP_Type op;
  int val;
} Program;

#endif
