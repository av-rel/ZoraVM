#define RUN_ZORAVM

#include <stdio.h>
#include <stdlib.h>

#include "./def.c"
#include "./error.c"
#include "./exec.c"
#include "./include/vm.h"
#include "./inst.c"
#include "./prog.c"

const char *NAME_SPACE = "ZoraVM:";

int ZVM(char *source) {
  VM vm = {0};
  VM_Init(&vm);
  ERROR vm_err = ERROR_OK;

  //   Program *programs = translate_asm_to_program(source);

  Program *program = (Program[]){
      {INST_PUSH, {DATA_INTEGER, .data.integer = 123}},
      {INST_PUSH, {DATA_INTEGER, .data.integer = 456}},
    //   {INST_DUMP, {DATA_INTEGER}},
      {INST_ADD, {DATA_INTEGER}},
      {INST_PRINT, {DATA_INTEGER}},
    //   {INST_DUMP, {DATA_INTEGER}},
      {INST_HALT, {DATA_INTEGER, .data.integer = 0}},
  };

  while (vm.state && vm_err == ERROR_OK)
    vm_err = VM_Execute(&vm, program[vm.ip]);

  if (vm_err != ERROR_OK) {
    printf("%s %s\n", NAME_SPACE, ERROR_as_str(vm_err));
    return vm_err;
  }

  return vm.stack[vm.sp - 1].data.integer;
}

#ifdef RUN_ZORAVM
int main(int argc, char *argv[]) {
  //  TODO: Add a way to load programs from files;

  char *source = "PUSH 123\nPUSH 456\nDUMP\nADD\nDUMP\n";

  return ZVM(source);
}
#endif

void VM_Init(VM *vm) {
  vm->state = 1;
  vm->ip = 0;
  vm->sp = 0;
}

ERROR VM_Execute(VM *vm, Program prog) {
  switch (prog.inst) {
  case INST_PUSH:
    return VM_Push(vm, prog);
  case INST_POP:
    return VM_Pop(vm);
  case INST_ADD:
    return VM_Add(vm);
  case INST_SUB:
    return VM_Sub(vm);
  case INST_MUL:
    return VM_Mul(vm);
  case INST_DIV:
    return VM_Div(vm);
  case INST_MOD:
    return VM_Mod(vm);
  case INST_HALT:
    return VM_Halt(vm, prog);
  case INST_PRINT:
    return VM_Print(vm, prog);
  case INST_SCAN:
    return VM_Scan(vm, prog);
  case INST_DUMP:
    return VM_Dump(vm);
  default:
    return ERROR_UNKNOWN_INST;
  }
  return ERROR_OK;
}
