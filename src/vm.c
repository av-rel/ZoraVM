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
  // TODO: Add a REPL for the VM
  //  TODO: Add a way to load programs from files
  Program program[] = {{
                           INST_PUSH,
                           10,
                       },
                       {
                           INST_PUSH,
                           20,
                       },
                       {
                           INST_MUL,
                       },
                       //    {
                       //    INST_PUSH,
                       //    30,
                       //    },
                       {
                           INST_DUMP,
                       },
                       //    {
                       //    INST_DIV,
                       //    },
                       {INST_HALT, 0}};

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
  switch (prog.inst) {
  case INST_PUSH:
    if (vm->sp >= STACK_SIZE)
      activateTrap(TRAP_STACK_OVERFLOW);
    vm->stack[vm->sp++] = prog.operand;
    vm->ip++;
    break;
  case INST_LOAD:
    if (vm->sp >= STACK_SIZE)
      activateTrap(TRAP_STACK_OVERFLOW);
    if (prog.operand >= STACK_SIZE)
      activateTrap(TRAP_STACK_OVERFLOW);
    vm->stack[vm->sp++] = vm->stack[prog.operand];
    vm->ip++;
    break;
  case INST_PRINT:
    if (vm->sp < 1)
      activateTrap(TRAP_STACK_UNDERFLOW);
    printf("%d\n", vm->stack[vm->sp - 1]);
    vm->ip++;
    break;
  case INST_SCAN:
    if (vm->sp >= STACK_SIZE)
      activateTrap(TRAP_STACK_OVERFLOW);
    scanf("%d", &vm->stack[vm->sp++]);
    vm->ip++;
    break;
  case INST_ADD:
    if (vm->sp < 1)
      activateTrap(TRAP_STACK_UNDERFLOW);
    vm->stack[vm->sp - 2] += vm->stack[vm->sp - 1];
    vm->ip++;
    break;
  case INST_SUB:
    if (vm->sp < 1)
      activateTrap(TRAP_STACK_UNDERFLOW);
    vm->stack[vm->sp - 2] -= vm->stack[vm->sp - 1];
    vm->ip++;
    break;
  case INST_MUL:
    if (vm->sp < 1)
      activateTrap(TRAP_STACK_UNDERFLOW);
    vm->stack[vm->sp-- - 2] *= vm->stack[vm->sp - 1];
    vm->ip++;
    break;
  case INST_DIV: {
    if (vm->sp < 1)
      activateTrap(TRAP_STACK_UNDERFLOW);
    if (vm->stack[vm->sp - 1] == 0)
      activateTrap(TRAP_DIV_BY_0);
    vm->stack[vm->sp - 2] /= vm->stack[vm->sp - 1];
    vm->ip++;
    break;
  }
  case INST_MOD:
    if (vm->sp < 1)
      activateTrap(TRAP_STACK_UNDERFLOW);
    if (vm->stack[vm->sp - 1] == 0)
      activateTrap(TRAP_DIV_BY_0);
    vm->stack[vm->sp - 2] %= vm->stack[vm->sp - 1];
    vm->ip++;
    break;
  case INST_RET:
    if (vm->sp < 1)
      activateTrap(TRAP_STACK_UNDERFLOW);
    vm->ip = vm->stack[--vm->sp];
    break;
  case INST_HALT:
    vm->state = 0;
    vm->stack[vm->sp++] = prog.operand;
    vm->ip++;
    break;
  case INST_NONE:
    vm->ip++;
    break;
  case INST_DUMP: {
    vm->ip++;
    printf("\n[Registers]:\n");
    printf("\tIP: %d", vm->ip);
    printf("\tSP: %d", vm->sp);
    printf("\n[Stack]:\n");
    if (vm->sp < 1) {
      printf("\t<empty>\n");
      break;
    }
    for (int i = 0; i < vm->sp; i++) {
      printf(" \t %d\n", vm->stack[i]);
    }
    break;
  }
  default:
    fprintf(stderr, "ERROR: Unknown Instruction found\n");
    exit(0);
  }
}

#endif
