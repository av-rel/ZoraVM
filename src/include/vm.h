#ifndef VM_H
#define VM_H

#include "./inst.h"

#define STACK_SIZE 1024

typedef struct {
  int state;
  int ip;
  int sp;
  int stack[STACK_SIZE];
} VM;

typedef struct {
  Inst inst;
  int operand;
} Program;

VM *init_vm();
void vm_exec(VM *vm, Program prog);

#endif
