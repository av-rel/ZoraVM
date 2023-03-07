#ifndef _ZORAVM_C
#define _ZORAVM_C

#include <stdio.h>
#include <stdlib.h>

#include "./zoravm.h"
#include "./exec.c"
#include "./inst.c"
#include "./trap.c"

int ZoraVME(ZoraVM_Program *program, unsigned int program_size, unsigned int cap) {
  ZoraVM vm;
  ZORAVM_ERROR vm_err = ZORAVM_ERROR_OK;

  if (program_size < 1) goto dispose;
  vm = ZoraVM_Init(cap);
 
  while (vm.state && vm_err == ZORAVM_ERROR_OK && vm.ip < program_size) {
    vm_err = ZoraVME_Execute(&vm, program[vm.ip]);
  }

  if (vm_err != ZORAVM_ERROR_OK) {
    #if ZORAVM_LOG
    printf("\n%s%s%s\n", "" , "ZORAVM_ERROR: ", ZoraVM_Errors[vm_err]);
    #endif
    goto dispose;
  }

  if (vm.mem[vm.mp - 1].kind != ZORAVM_DATA_INTEGER) {
    #if ZORAVM_LOG
    printf("\n%s%s%s\n", "" ,"ZORAVM_ERROR: ", "Expected integer as return value\n");
    #endif
    vm_err = ZORAVM_ERROR_UNEXPECTED_TYPE;
    goto dispose;
  }

  vm_err = vm.mem[--vm.mp].val.integer;

dispose:
  if (!(program_size < 1)) ZoraVM_Dispose(&vm);
  return vm_err;
}


ZORAVM_ERROR ZoraVME_Execute(ZoraVM *vm, ZoraVM_Program prog) {
  switch (prog.inst) {
  case ZORAVM_INST_PUSH:
    return ZoraVME_Push(vm, prog.entry);
  case ZORAVM_INST_POP:
    return ZoraVME_Pop(vm);
  case ZORAVM_INST_STORE:
    return ZoraVME_Store(vm, prog.entry);
  case ZORAVM_INST_LOAD:
    return ZoraVME_Load(vm, prog.entry);
  case ZORAVM_INST_DUP:
    return ZoraVME_Dup(vm);
  case ZORAVM_INST_SWAP:
    return ZoraVME_Swap(vm);
  case ZORAVM_INST_ADD:
    return ZoraVME_Add(vm);
  case ZORAVM_INST_SUB:
    return ZoraVME_Sub(vm);
  case ZORAVM_INST_MUL:
    return ZoraVME_Mul(vm);
  case ZORAVM_INST_DIV:
    return ZoraVME_Div(vm);
  case ZORAVM_INST_MOD:
    return ZoraVME_Mod(vm);
  case ZORAVM_INST_INC:
    return ZoraVME_Inc(vm);
  case ZORAVM_INST_DEC:
    return ZoraVME_Dec(vm);
  case ZORAVM_INST_POW:
    return ZoraVME_Pow(vm);
  case ZORAVM_INST_AND:
    return ZoraVME_And(vm);
  case ZORAVM_INST_OR:
    return ZoraVME_Or(vm);
  case ZORAVM_INST_XOR:
    return ZoraVME_Xor(vm);
  case ZORAVM_INST_NOT:
    return ZoraVME_Not(vm);
  case ZORAVM_INST_SHL:
    return ZoraVME_Shl(vm);
  case ZORAVM_INST_SHR:
    return ZoraVME_Shr(vm);
  case ZORAVM_INST_CMP_EQ:
    return ZoraVME_CmpEq(vm);
  case ZORAVM_INST_CMP_NEQ:
    return ZoraVME_CmpNotEq(vm);
  case ZORAVM_INST_CMP_GT:
    return ZoraVME_CmpGt(vm);
  case ZORAVM_INST_CMP_NGT:
    return ZoraVME_CmpNotGt(vm);
  case ZORAVM_INST_CMP_LT:
    return ZoraVME_CmpLt(vm);
  case ZORAVM_INST_CMP_NLT:
    return ZoraVME_CmpNotLt(vm);
  case ZORAVM_INST_CMP_GTE:
    return ZoraVME_CmpGte(vm);
  case ZORAVM_INST_CMP_NGTE:
    return ZoraVME_CmpNotGte(vm);
  case ZORAVM_INST_CMP_LTE:
    return ZoraVME_CmpLte(vm);
  case ZORAVM_INST_CMP_NLTE:
    return ZoraVME_CmpNotLte(vm);
  case ZORAVM_INST_JMP:
    return ZoraVME_Jmp(vm, prog);
  case ZORAVM_INST_JMPIF:
    return ZoraVME_JmpIf(vm, prog);
  case ZORAVM_INST_JMPIFN:
    return ZoraVME_JmpIfNot(vm, prog);
  case ZORAVM_INST_PRINT:
    return ZoraVME_Print(vm);
  case ZORAVM_INST_SCAN:
    return ZoraVME_Scan(vm);
  case ZORAVM_INST_SIZEOF:
    return ZoraVME_SizeOf(vm);
  case ZORAVM_INST_RET:
    return ZoraVME_Ret(vm, prog);
  case ZORAVM_INST_HALT:
    return ZoraVME_Halt(vm, prog);
  case ZORAVM_INST_DUMP_STACK:
    return ZoraVME_Dump_Stack(vm);
  case ZORAVM_INST_DUMP_MEM:
    return ZoraVME_Dump_Mem(vm);
  default:
    return ZORAVM_ERROR_UNKNOWN_INST;
  }
  return ZORAVM_ERROR_OK;
}

ZoraVM ZoraVM_Init(unsigned int cap) {
  ZoraVM vm = {0};

  vm.ip = 0;
  vm.mp = 0;
  vm.sp = 0;
  vm.fp = 0;
  vm.size = cap;

  vm.stack = malloc(sizeof(ZoraVM_Data) * (vm.size + 1));
  vm.mem = malloc(sizeof(ZoraVM_Data) * (vm.size + 1));

  vm.state = 1;

  return vm;
}

void ZoraVM_Dispose(ZoraVM *vm) {
  free(vm->mem);
  free(vm->stack);
}

#endif
