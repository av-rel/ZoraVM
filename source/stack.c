// stack functions for i32bit
#ifndef STACK_C
#define STACK_C

#include "../include/vm.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void overflow(bool overflow) {
  if (overflow)
    printf("Stack overflow\n");
  else
    printf("Stack underflow\n");
  exit(0);
}

void stack_push(Zvm *vm, int val) {
  if (vm->size >= STACK_SIZE)
    overflow(true);
  vm->inst.val = val;
  vm->stack[vm->size++] = vm->inst.val;
}

void stack_pop(Zvm *vm) {
  if (vm->size <= 0)
    overflow(false);
  vm->size--;
}

void stack_move(Zvm *vm) {
  if (vm->size <= 1)
    overflow(false);
  vm->stack[vm->size - 2] = vm->stack[vm->size - 1];
  vm->size--;
}

void stack_dup(Zvm *vm) {
  if (vm->size <= 0)
    overflow(false);
  if (vm->size >= STACK_SIZE)
    overflow(true);
  vm->stack[vm->size] = vm->stack[vm->size - 1];
  vm->size++;
}

void stack_swap(Zvm *vm) {
  if (vm->size <= 1)
    overflow(false);
  int temp = vm->stack[vm->size - 1];
  vm->stack[vm->size - 1] = vm->stack[vm->size - 2];
  vm->stack[vm->size - 2] = temp;
}

void stack_add(Zvm *vm) {
  if (vm->size <= 1)
    overflow(false);
  vm->stack[vm->size - 2] += vm->stack[vm->size - 1];
  vm->size++;
}

void stack_sub(Zvm *vm) {
  if (vm->size <= 1)
    overflow(false);
  vm->stack[vm->size - 2] -= vm->stack[vm->size - 1];
  vm->size--;
}

void stack_mul(Zvm *vm) {
  if (vm->size <= 1)
    overflow(false);
  vm->stack[vm->size - 2] *= vm->stack[vm->size - 1];
  vm->size--;
}

void stack_div(Zvm *vm) {
  if (vm->size <= 1)
    overflow(false);
  vm->stack[vm->size - 2] /= vm->stack[vm->size - 1];
  vm->size--;
}

void stack_mod(Zvm *vm) {
  if (vm->size <= 1)
    overflow(false);
  vm->stack[vm->size - 2] %= vm->stack[vm->size - 1];
  vm->size--;
}

// printing the stack
void stack_print(Zvm *vm) {
  int i;

  printf("\n[Stack]:\n");

  if (vm->size <= 0) {
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