#ifndef _ZORAVM_C
#define _ZORAVM_C

#define ZORAVM_VERSION "0.1.0"

#include <stdio.h>
#include <stdlib.h>

#include "./zoravm.h"
#include "../zorasm/kw.c"
#include "./exec.c"
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

  if (vm.mem[vm.mp - 1].kind != ZORASM_DATA_INT) {
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
  case ZORASM_INST_PUSH:
    return ZoraVME_Push(vm, prog.entry);
  case ZORASM_INST_POP:
    return ZoraVME_Pop(vm);
  case ZORASM_INST_STORE:
    return ZoraVME_Store(vm, prog.entry);
  case ZORASM_INST_LOAD:
    return ZoraVME_Load(vm, prog.entry);
  case ZORASM_INST_DUP:
    return ZoraVME_Dup(vm);
  case ZORASM_INST_SWAP:
    return ZoraVME_Swap(vm);
  case ZORASM_INST_ADD:
    return ZoraVME_Add(vm);
  case ZORASM_INST_SUB:
    return ZoraVME_Sub(vm);
  case ZORASM_INST_MUL:
    return ZoraVME_Mul(vm);
  case ZORASM_INST_DIV:
    return ZoraVME_Div(vm);
  case ZORASM_INST_MOD:
    return ZoraVME_Mod(vm);
  case ZORASM_INST_INC:
    return ZoraVME_Inc(vm);
  case ZORASM_INST_DEC:
    return ZoraVME_Dec(vm);
  case ZORASM_INST_POW:
    return ZoraVME_Pow(vm);
  case ZORASM_INST_AND:
    return ZoraVME_And(vm);
  case ZORASM_INST_OR:
    return ZoraVME_Or(vm);
  case ZORASM_INST_XOR:
    return ZoraVME_Xor(vm);
  case ZORASM_INST_NOT:
    return ZoraVME_Not(vm);
  case ZORASM_INST_NEG:
    return ZoraVME_Neg(vm);
  case ZORASM_INST_SHL:
    return ZoraVME_Shl(vm);
  case ZORASM_INST_SHR:
    return ZoraVME_Shr(vm);
  case ZORASM_INST_EQ:
    return ZoraVME_CmpEq(vm);
  case ZORASM_INST_NEQ:
    return ZoraVME_CmpNotEq(vm);
  case ZORASM_INST_GT:
    return ZoraVME_CmpGt(vm);
  case ZORASM_INST_NGT:
    return ZoraVME_CmpNotGt(vm);
  case ZORASM_INST_LT:
    return ZoraVME_CmpLt(vm);
  case ZORASM_INST_NLT:
    return ZoraVME_CmpNotLt(vm);
  case ZORASM_INST_GTE:
    return ZoraVME_CmpGte(vm);
  case ZORASM_INST_NGTE:
    return ZoraVME_CmpNotGte(vm);
  case ZORASM_INST_LTE:
    return ZoraVME_CmpLte(vm);
  case ZORASM_INST_NLTE:
    return ZoraVME_CmpNotLte(vm);
  case ZORASM_INST_JMP:
    return ZoraVME_Jmp(vm, prog);
  case ZORASM_INST_JMPIF:
    return ZoraVME_JmpIf(vm, prog);
  case ZORASM_INST_JMPIFN:
    return ZoraVME_JmpIfNot(vm, prog);
  case ZORASM_INST_PRINT:
    return ZoraVME_Print(vm);
  case ZORASM_INST_SCAN:
    return ZoraVME_Scan(vm);
  case ZORASM_INST_SIZEOF:
    return ZoraVME_SizeOf(vm);
  case ZORASM_INST_RET:
    return ZoraVME_Ret(vm, prog);
  case ZORASM_INST_HALT:
    return ZoraVME_Halt(vm, prog);
  case ZORASM_INST_DUMP_STACK:
    return ZoraVME_Dump_Stack(vm);
  case ZORASM_INST_DUMP_MEM:
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
