#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/vm.h"

#define HEAP_SIZE 2048

Zvm *zvm_new() {
  Zvm *_zvm = (Zvm *) malloc(sizeof(Zvm));
  _zvm->globals = (int*) calloc(1, HEAP_SIZE);
  _zvm->ip = 0;
  return _zvm;
}

Inst *inst_new() {
  Inst *inst = (Inst *)calloc(1, sizeof(Inst));
  inst->type = OP_NONE;
  return inst;
}

void vm_exec(Zvm *vm, Inst *inst) {
  switch (inst->type) {
  case OP_NONE:
    break;
  default:
    break;
  }
 }
