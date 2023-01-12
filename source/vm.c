#ifndef ZVM_C
#define ZVM_C

#include "../include/vm.h"
#include "./lexer/lexer.c"
#include "./stack.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Zvm *zvm_new() {
  Zvm *_zvm = (Zvm *)calloc(1, sizeof(Zvm));
  _zvm->size = 0;
  _zvm->ip = 0;
  return _zvm;
}

Inst *inst_new() {
  Inst *inst = (Inst *)calloc(1, sizeof(Inst));
  inst->type = OP_NONE;
  inst->op = 0;
  return inst;
}

void vm_exec(Zvm *vm, Inst *inst) {
  switch (inst->type) {
  case OP_NONE:
    break;
  case OP_PUSH:
    stack_push(vm, inst);
    break;
  case OP_POP:
    stack_pop(vm, inst);
    break;
  case OP_MOVE:
    stack_move(vm, inst);
    break;
  case OP_SWAP:
    stack_swap(vm, inst);
    break;
  case OP_DUP:
    stack_dup(vm, inst);
    break;
  case OP_ADD:
    stack_add(vm, inst);
    break;
  case OP_SUB:
    stack_sub(vm, inst);
    break;
  case OP_MUL:
    stack_mul(vm, inst);
    break;
  case OP_DIV:
    stack_div(vm, inst);
    break;
  case OP_MOD:
    stack_mod(vm, inst);
    break;
  case OP_POW:
    stack_pow(vm, inst);
    break;
  case OP_PRINT:
    stack_print(inst);
    break;
  case OP_LOG:
    stack_log(vm, inst);
    break;
  default:
    printf("Unknown instruction %d\n", inst->op);
    exit(0);
  }
}

#endif