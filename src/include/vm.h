#ifndef VM_H
#define VM_H

#include "./error.h"
#include "./inst.h"

#define STACK_SIZE 1024

enum DATA_KIND { STRING = 0, INT, FLOAT };

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

void VM_Init(VM *vm);
ERROR VM_Execute(VM *vm, Program prog);

#endif
