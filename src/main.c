#include "include/inst.h"
#define RUN_ZORAVM

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "./def.c"
#include "./error.c"
#include "./exec.c"
#include "./include/vm.h"
#include "./inst.c"
#include "./prog.c"

// TODO: 2 ** 62 > NaN :: Throw Error => No. out of range

const char *NAME_SPACE = "";

int ZVM(char *source) {
  VM vm = {0};
  VM_INIT(vm);

  ERROR vm_err = ERROR_OK;
  Program program[] = {
      PushStr("Hello World!\n"),
      PrintStr(),
      Halt(0),
  };

  // main loop for executing instructions
  while (vm.state && vm_err == ERROR_OK)
    vm_err = VM_Execute(&vm, program[vm.ip]);
  //

  //   if (vm.ip < 1) {
  //     vm_err = ERROR_PROGRAM_NOT_FOUND;
  //     printf("%s %s %s\n", NAME_SPACE, "[ERROR]:", ERROR_as_str(vm_err));
  //     return vm_err;
  //   }

  if (vm_err != ERROR_OK) {
    printf("%s%s%s\n", NAME_SPACE, "[ERROR]: ", ERROR_as_str(vm_err));
    return vm_err;
  }

  if (vm.mem[vm.mp - 1].kind != DATA_INTEGER) {
    printf("%s%s%s\n", NAME_SPACE,
           "[ERROR]: ", "Expected integer as return value\n");
    return ERROR_UNEXPECTED_TYPE;
  }

  return vm.mem[--vm.mp].val.integer;
}

#ifdef RUN_ZORAVM
int main(int argc, char *argv[]) {
  //  TODO: Add a way to load programs from files;
  //   char *source = "PUSH 123\nPUSH 456\nDUMP\nADD\nDUMP\n";

  return ZVM("");
}
#endif

ERROR VM_Execute(VM *vm, Program prog) {
  switch (prog.inst) {
  case INST_PUSH:
    return VM_Push(vm, prog.entry);
  case INST_POP:
    return VM_Pop(vm);
  case INST_STORE:
    return VM_Store(vm, prog.entry);
  case INST_LOAD:
    return VM_Load(vm, prog.entry);
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
  case INST_INC:
    return VM_Inc(vm);
  case INST_DEC:
    return VM_Dec(vm);
  case INST_POW:
    return VM_Pow(vm);
  case INST_PRINT:
    return VM_Print(vm, prog);
  case INST_SCAN:
    return VM_Scan(vm, prog);
  case INST_RET:
    return VM_Ret(vm, prog);
  case INST_HALT:
    return VM_Halt(vm, prog);
  case INST_DUMP_STACK:
    return VM_Dump_Stack(vm);
  case INST_DUMP_MEM:
    return VM_Dump_Mem(vm);
  default:
    return ERROR_UNKNOWN_INST;
  }
  return ERROR_OK;
}
