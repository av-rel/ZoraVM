/* #define RUN_ZORAVM */
#define SHOUT 1

#include <stdio.h>
#include <stdlib.h>

#include "./exec.c"
#include "./include/macro.h"
#include "./include/vm.h"
#include "./inst.c"
#include "./prog.c"
#include "./trap.c"

int ZoraVM(Program *program, int np) {
  VM vm = {0};
  VM_INIT(vm);

  ERROR vm_err = ERROR_OK;

  while (vm.state && vm_err == ERROR_OK && vm.ip < np) {
    vm_err = VM_Execute(&vm, program[vm.ip]);
  }

  if (vm_err != ERROR_OK) {
    #if SHOUT
    printf("%s%s%s\n", "" , "ERROR: ", Errors[vm_err]);
    #endif
    return vm_err;
  }

  if (vm.mem[vm.mp - 1].kind != DATA_INTEGER) {
    #if SHOUT
    printf("%s%s%s\n", "" ,"ERROR: ", "Expected integer as return value\n");
    #endif
    return ERROR_UNEXPECTED_TYPE;
  }

  return vm.mem[--vm.mp].val.integer;
}

#ifdef RUN_ZORAVM
int main(int argc, char *argv[]) {
  //  TODO: Add a way to load programs from files;
  //   char *source = "PUSH 123\nPUSH 456\nDUMP\nADD\nDUMP\n";

  Program program[] = {
    PushStr("Hello, world\n"),
    Print(),
    Halt(0),
  };

  return ZoraVM(program, ArraySize(program));
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
  case INST_DUP:
    return VM_Dup(vm);
  case INST_SWAP:
    return VM_Swap(vm);
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
  case INST_AND:
    return VM_And(vm);
  case INST_OR:
    return VM_Or(vm);
  case INST_XOR:
    return VM_Xor(vm);
  case INST_NOT:
    return VM_Not(vm);
  case INST_SHL:
    return VM_Shl(vm);
  case INST_SHR:
    return VM_Shr(vm);
  case INST_CMP_EQ:
    return VM_CmpEq(vm);
  case INST_CMP_NEQ:
    return VM_CmpNotEq(vm);
  case INST_CMP_GT:
    return VM_CmpGt(vm);
  case INST_CMP_NGT:
    return VM_CmpNotGt(vm);
  case INST_CMP_LT:
    return VM_CmpLt(vm);
  case INST_CMP_NLT:
    return VM_CmpNotLt(vm);
  case INST_CMP_GTE:
    return VM_CmpGte(vm);
  case INST_CMP_NGTE:
    return VM_CmpNotGte(vm);
  case INST_CMP_LTE:
    return VM_CmpLte(vm);
  case INST_CMP_NLTE:
    return VM_CmpNotLte(vm);
  case INST_JMP:
    return VM_Jmp(vm, prog);
  case INST_JMPIF:
    return VM_JmpIf(vm, prog);
  case INST_JMPIFN:
    return VM_JmpIfNot(vm, prog);
  case INST_PRINT:
    return VM_Print(vm);
  case INST_SCAN:
    return VM_Scan(vm, prog);
  case INST_SIZEOF:
    return VM_SizeOf(vm);
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
