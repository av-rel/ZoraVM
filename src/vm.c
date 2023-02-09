#ifndef VM_C
#define VM_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/macro.h"
#include "./include/vm.h"
#include "./trap.c"

//debugging purposes only
Program program[] = {};

int Zvm(char *code) {
  VM vm = init_vm();

  for (int i = 0; i < ARRAY_SIZE(program); i++) {
    vm_exec(vm, program[i]);
  }

  return 0;
}

int main(int argc, char *argv[]) {
  char *code = "";
  return Zvm(code);
}

VM init_vm() {
  VM vm;
  vm.ip = 0;
  return vm;
}

void vm_exec(VM vm, Program prog) {
  switch (prog.op) {
  case OP_STORE:
    break;
  case OP_LOAD:
    break;
  case OP_PRINT:
    break;
  case OP_SCAN:
    break;
  case OP_ADD:
    break;
  case OP_SUB:
    break;
  case OP_MUL:
    break;
  case OP_DIV: {
    break;
  }
  case OP_MOD:
    break;
  case OP_DEBUG: {
  }
  case OP_RET:
    break;
  case OP_HALT:
    break;
  case OP_NONE:
    break;
  default:
    fprintf(stderr, "Unknown Instruction found\n");
    exit(0);
  }
}

#endif