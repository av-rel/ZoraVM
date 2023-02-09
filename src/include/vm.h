#ifndef VM_H
#define VM_H

#include "./op.h"

typedef struct {
  int ip;
} VM;

typedef struct {
  OP op;
  int val;
} Program;

void vm_exec(VM vm, Program prog);
VM init_vm();

#endif
