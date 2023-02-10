#ifndef VM_C
#define VM_C

#include <stdio.h>
#include <stdlib.h>

#include "./def.c"
#include "./error.c"
#include "./include/vm.h"
#include "./inst.c"

int ZVM(Program program[]) {
  VM vm = {0};
  VM_Init(&vm);

  ERROR vm_err = ERROR_OK;
  while (vm.state && vm_err == ERROR_OK)
    vm_err = VM_Execute(&vm, program[vm.ip]);

  if (vm_err != ERROR_OK)
    printf("VM: %s\n", ERROR_as_str(vm_err));

  return vm_err;
}

int main(int argc, char *argv[]) {
  // TODO: Add a REPL for the VM
  //  TODO: Add a way to load programs from files
  Program program[] = {{INST_PUSH, -1},
                       {
                           INST_DUMP,
                       },
                       {INST_HALT, 0}};

  // TODO: pass bytecode to the VM
  return ZVM(program);
}

void VM_Init(VM *vm) {
  vm->state = 1;
  vm->ip = 0;
  vm->sp = 0;
}

ERROR VM_Dump(VM *vm) {
  vm->ip++;
  printf("\n[CPU]\n");
  printf("\tIP: %d", vm->ip);
  printf("\tSP: %d", vm->sp);
  printf("\n[Stack]\n");
  if (vm->sp < 1) {
    printf("\t<empty>\n");
    return ERROR_OK;
  }
  for (int i = 0; i < vm->sp; i++) {
    printf("\t%d\n", vm->stack[i]);
  }
  return ERROR_OK;
}

ERROR VM_Execute(VM *vm, Program prog) {
  switch (prog.inst) {
  case INST_PUSH:
    vm->stack[vm->sp++] = prog.operand;
    vm->ip++;
    break;
  case INST_HALT:
    vm->state = 0;
    vm->stack[vm->sp++] = prog.operand;
    vm->ip++;
    break;
  case INST_DUMP:
    return VM_Dump(vm);
  default:
    return ERROR_UNKNOWN_INST;
  }
  return ERROR_OK;
}

#endif
