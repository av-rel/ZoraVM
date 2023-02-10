#ifndef _EXEC_C
#define _EXEC_C

#include <stdio.h>

#include "./error.c"
#include "./include/vm.h"
#include "./inst.c"

ERROR VM_Push(VM *vm, Program prog) {
  if (vm->sp >= STACK_SIZE)
    return ERROR_STACK_OVERFLOW;

  //   if (vm->stack[vm->sp - 1].kind == DATA_INTEGER)
  vm->stack[vm->sp++].data.integer = prog.entry.data.integer;
  //   else if (vm->stack[vm->sp - 1].kind == DATA_FLOATING)
  // vm->stack[vm->sp++].data.floating = prog.entry.data.floating;
  //   else if (vm->stack[vm->sp - 1].kind == DATA_STRING)
  // vm->stack[vm->sp++].data.string = prog.entry.data.string;

  vm->ip++;

  return ERROR_OK;
}

ERROR VM_Pop(VM *vm) {
  if (vm->sp <= 0)
    return ERROR_STACK_UNDERFLOW;
  vm->stack[vm->sp--] = (Data){0};
  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Add(VM *vm) {
  if (vm->sp <= 1)
    return ERROR_STACK_UNDERFLOW;
  vm->stack[vm->sp - 2].data.integer += vm->stack[vm->sp - 1].data.integer;
  vm->stack[vm->sp--] = (Data){0};
  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Sub(VM *vm) {
  if (vm->sp <= 1)
    return ERROR_STACK_UNDERFLOW;
  vm->stack[vm->sp - 2].data.integer -= vm->stack[vm->sp - 1].data.integer;
  vm->stack[vm->sp--] = (Data){0};
  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Mul(VM *vm) {
  if (vm->sp <= 1)
    return ERROR_STACK_UNDERFLOW;
  vm->stack[vm->sp - 2].data.integer *= vm->stack[vm->sp - 1].data.integer;
  vm->stack[vm->sp--] = (Data){0};
  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Div(VM *vm) {
  if (vm->sp <= 1)
    return ERROR_STACK_UNDERFLOW;
  if (vm->stack[vm->sp - 1].data.integer == 0)
    return ERROR_DIV_BY_0;
  vm->stack[vm->sp - 2].data.integer /= vm->stack[vm->sp - 1].data.integer;
  vm->stack[vm->sp--] = (Data){0};
  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Mod(VM *vm) {
  if (vm->sp <= 1)
    return ERROR_STACK_UNDERFLOW;
  if (vm->stack[vm->sp - 1].data.integer == 0)
    return ERROR_DIV_BY_0;
  vm->stack[vm->sp - 2].data.integer %= vm->stack[vm->sp - 1].data.integer;
  vm->stack[vm->sp--] = (Data){0};
  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Halt(VM *vm, Program prog) {
  vm->state = 0;
  vm->stack[vm->sp].kind = DATA_INTEGER;
  vm->stack[vm->sp].data.integer = prog.entry.data.integer;
  vm->sp++;
  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Print(VM *vm, Program prog) {
  if (vm->sp <= 0)
    return ERROR_STACK_UNDERFLOW;
  if (vm->stack[vm->sp - 1].kind == DATA_INTEGER)
    printf("%d", vm->stack[vm->sp - 1].data.integer);
  else if (vm->stack[vm->sp - 1].kind == DATA_FLOATING)
    printf("%f", vm->stack[vm->sp - 1].data.floating);
  else if (vm->stack[vm->sp - 1].kind == DATA_STRING)
    printf("%s", vm->stack[vm->sp - 1].data.string);

  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Scan(VM *vm, Program prog) {
  if (vm->sp <= 0)
    return ERROR_STACK_UNDERFLOW;
  if (vm->stack[vm->sp - 1].kind == DATA_INTEGER)
    scanf("%d", &vm->stack[vm->sp - 1].data.integer);
  else if (vm->stack[vm->sp - 1].kind == DATA_FLOATING)
    scanf("%f", &vm->stack[vm->sp - 1].data.floating);
  else if (vm->stack[vm->sp - 1].kind == DATA_STRING)
    scanf("%s", vm->stack[vm->sp - 1].data.string);
  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Call(VM *vm, Program prog) {
  if (vm->sp >= STACK_SIZE)
    return ERROR_STACK_OVERFLOW;
  vm->stack[vm->sp++].data.integer = vm->ip + 1;
  vm->ip = prog.entry.data.integer;
  return ERROR_OK;
}

ERROR VM_Jmpz(VM *vm, Program prog) {
  if (vm->stack[vm->sp - 1].data.integer == 0)
    vm->ip = prog.entry.data.integer;
  else
    vm->ip++;
  return ERROR_OK;
}

ERROR VM_Jmpnz(VM *vm, Program prog) {
  if (vm->stack[vm->sp - 1].data.integer != 0)
    vm->ip = prog.entry.data.integer;
  else
    vm->ip++;
  return ERROR_OK;
}

ERROR VM_Jmp(VM *vm, Program prog) {
  vm->ip = prog.entry.data.integer;
  return ERROR_OK;
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
    if (vm->stack[i].kind == DATA_INTEGER)
      printf("\t%d: %d\n", i, vm->stack[i].data.integer);
    else if (vm->stack[i].kind == DATA_FLOATING)
      printf("\t%d: %f\n", i, vm->stack[i].data.floating);
    else if (vm->stack[i].kind == DATA_STRING)
      printf("\t%d: %s\n", i, vm->stack[i].data.string);
  }
  return ERROR_OK;
}

#endif