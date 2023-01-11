#ifndef STACK_C
#define STACK_C

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/vm.h"
#include "./trap/trap.c"
#include "./trap/trap.h"

void stack_push(Zvm *vm, Inst *inst) {
  if (vm->size >= STACK_SIZE)
    activateTrap(TRAP_STACKOVERFLOW);
  vm->stack[vm->size] = inst->operand;
  vm->size++;
}

void stack_pop(Zvm *vm, Inst *inst) {
  if (vm->size <= 0)
    activateTrap(TRAP_STACKUNDERFLOW);
  vm->size--;
}

void stack_move(Zvm *vm, Inst *inst) {
  if (vm->size <= 1)
    activateTrap(TRAP_STACKUNDERFLOW);
  vm->stack[vm->size - 2] = vm->stack[vm->size - 1];
  vm->size--;
}

void stack_dup(Zvm *vm, Inst *inst) {
  if (vm->size <= 1)
    activateTrap(TRAP_STACKUNDERFLOW);
  if (vm->size >= STACK_SIZE)
    activateTrap(TRAP_STACKOVERFLOW);
  vm->stack[vm->size] = vm->stack[vm->size - 1];
  vm->size++;
}

void stack_swap(Zvm *vm, Inst *inst) {
  if (vm->size <= 1)
    activateTrap(TRAP_STACKUNDERFLOW);
  vm->stack[vm->size - 2] -= vm->stack[vm->size - 1];
  vm->stack[vm->size - 1] += vm->stack[vm->size - 2];
}

void stack_add(Zvm *vm, Inst *inst) {
  if (vm->size <= 1)
    activateTrap(TRAP_STACKUNDERFLOW);
  vm->stack[vm->size - 2] += vm->stack[vm->size - 1];
  vm->size--;
}

void stack_sub(Zvm *vm, Inst *inst) {
  if (vm->size <= 1)
    activateTrap(TRAP_STACKUNDERFLOW);
  vm->stack[vm->size - 2] -= vm->stack[vm->size - 1];
  vm->size--;
}

void stack_mul(Zvm *vm, Inst *inst) {
  if (vm->size <= 1)
    activateTrap(TRAP_STACKUNDERFLOW);
  vm->stack[vm->size - 2] *= vm->stack[vm->size - 1];
  vm->size--;
}

void stack_div(Zvm *vm, Inst *inst) {
  if (vm->size <= 1)
    activateTrap(TRAP_STACKUNDERFLOW);
  vm->stack[vm->size - 2] /= vm->stack[vm->size - 1];
  vm->size--;
}

void stack_mod(Zvm *vm, Inst *inst) {
  if (vm->size <= 1)
    activateTrap(TRAP_STACKUNDERFLOW);
  vm->stack[vm->size - 2] %= vm->stack[vm->size - 1];
  vm->size--;
}

void stack_pow(Zvm *vm, Inst *inst) {
  if (vm->size <= 1)
    activateTrap(TRAP_STACKUNDERFLOW);
  vm->stack[vm->size - 2] = pow(vm->stack[vm->size - 1], 2);
  vm->size--;
}

void stack_print(Inst *inst) { printf("%d", inst->operation); }

void stack_scan(int scanno) { scanf("%d", &scanno); }

void stack_log(Zvm *vm, Inst *inst) {
  int i;
  printf("\n[Stack]:\n");

  if (vm->size <= 1) {
    printf("\t<Empty>\n");
    return;
  }

  for (i = 0; i < vm->size; i++) {
    printf("\t");
    printf("%d", vm->stack[i]);
    if (i == vm->size - 1)
      printf("\t<--");
    printf("\n");
  }
}

#endif
