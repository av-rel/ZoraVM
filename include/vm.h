#ifndef VM_H
#define VM_H

#include <stdint.h>
#include "./op.h"

#define ArraySize(ele) (int)sizeof(ele) / sizeof(ele[0])

#define VM_CAP 2048

typedef struct {
  long long int globals[VM_CAP];
  int ip;
  int len;
} Zvm;

typedef struct {
  OP_Type op;
  int val;
} Program;

#endif
