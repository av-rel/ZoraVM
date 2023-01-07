// VM for i32bit
#include <stdio.h>
#include <stdlib.h>

#include "./zvm.c"

#define lvm(vm) printf("%p\n", &vm)

int main() {

  Zvm *zvm = zvm_new();
  Inst *inst = inst_new();

  /* inst->op = OP_Push; */

  stack_push(zvm, 190003);

  vm_exec(zvm, inst);

  return 0;
}
