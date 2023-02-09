#ifndef VM_C
#define VM_C

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/vm.h"
#include "./inst.c"
#include "./trap.c"

int Zvm(Program program[]) {
  VM *vm = init_vm();

  while (vm->state)
    vm_exec(vm, program[vm->ip]);

  int ret = vm->stack[vm->sp - 1];

  free(vm);
  return ret;
}

int main(int argc, char *argv[]) {
  Program program[] = {{
                           .inst = INST_STORE,
                           .operand = 10,
                       },
                       {
                           .inst = INST_STORE,
                           .operand = 20,
                       },
                       {
                           .inst = INST_ADD,
                       },
                       {
                           .inst = INST_PRINT,
                       },
                       {
                           .inst = INST_DUMP,
                       },
                       {.inst = INST_HALT, 0}};

  return Zvm(program);
}

VM *init_vm() {
  VM *vm = calloc(1, sizeof(VM));
  vm->state = 1;
  vm->ip = 0;
  vm->sp = 0;
  return vm;
}

void vm_exec(VM *vm, Program prog) {
  // TODO: Add trap handler
  switch (prog.inst) {
  case INST_STORE:
    handle_trap(vm);
    vm->stack[vm->sp++] = prog.operand;
    vm->ip++;
    break;
  case INST_LOAD:
    // handle_trap(vm);
    vm->stack[vm->sp++] = vm->stack[prog.operand];
    vm->ip++;
    break;
  case INST_PRINT:
    // handle_trap(vm);
    printf("%d\n", vm->stack[vm->sp - 1]);
    vm->ip++;
    break;
  case INST_SCAN:
    // handle_trap(vm);
    scanf("%d", &vm->stack[vm->sp++]);
    vm->ip++;
    break;
  case INST_ADD:
    vm->stack[vm->sp - 2] += vm->stack[vm->sp - 1];
    vm->sp--;
    vm->ip++;
    // handle_trap(vm);
    break;
  case INST_SUB:
    vm->stack[vm->sp - 2] -= vm->stack[vm->sp - 1];
    vm->sp--;
    vm->ip++;
    // handle_trap(vm);
    break;
  case INST_MUL:
    vm->stack[vm->sp-- - 2] *= vm->stack[vm->sp - 1];
    vm->sp--;
    vm->ip++;
    // handle_trap(vm);
    break;
  case INST_DIV: {
    vm->stack[vm->sp - 2] /= vm->stack[vm->sp - 1];
    vm->sp--;
    vm->ip++;
    // handle_trap(vm);
    break;
  }
  case INST_MOD:
    vm->stack[vm->sp - 2] %= vm->stack[vm->sp - 1];
    vm->sp--;
    vm->ip++;
    // handle_trap(vm);
    break;
  case INST_RET:
    vm->ip = vm->stack[--vm->sp];
    // handle_trap(vm);
    break;
  case INST_HALT:
    vm->stack[vm->sp++] = prog.operand;
    vm->ip++;
    vm->state = 0;
    break;
  case INST_NONE:
    break;
  case INST_DUMP: {
    printf("\n[Stack]:\n");
    if (vm->sp < 1) {
      printf("\t<empty>\n");
      break;
    }
    for (int i = 0; i < vm->sp; i++) {
      printf(" \t %d\n", vm->stack[i]);
    }
    vm->ip++;
    break;
  }
  default:
    fprintf(stderr, "ERROR: Unknown Instruction found\n");
    exit(0);
  }
}

#endif
