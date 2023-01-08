#ifndef ZVM_C
#define ZVM_C

#include "../include/vm.h"
#include "./lexer/lexer.h"
#include "./stack.c"
#include <stdio.h>
#include <stdlib.h>

Zvm *zvm_new() {
  Zvm *_zvm = (Zvm *)calloc(1, sizeof(Zvm));
  _zvm->size = 0;
  _zvm->inst.op = OP_Silent;
  _zvm->inst.val = 0;
  return _zvm;
}

void vm_run(lexer_struct *lexer) {
  while (lexer->cur != '\0') {
    printf("%c", lexer->cur);
  }
}

void zvm_free(Zvm *vm) { free(vm); }

// unused for now
// void vm_exec(Zvm *vm) {
//   switch (vm->inst.op) {
//   case OP_Push:
//     stack_push(vm, vm->inst.val);
//     break;
//   case OP_Pop:
//     stack_pop(vm);
//     break;
//   case OP_Move:
//     stack_move(vm);
//     break;
//   case OP_Add:
//     stack_add(vm);
//     break;
//   case OP_Sub:
//     stack_sub(vm);
//     break;
//   case OP_Mul:
//     stack_mul(vm);
//     break;
//   case OP_Div:
//     stack_div(vm);
//     break;
//   case OP_Mod:
//     stack_mod(vm);
//     break;
//   case OP_Print:
//     stack_print(vm);
//     break;
//   case OP_Silent:
//     break;
//   default:
//     printf("Unknown instruction %d\n", vm->inst.op);
//   }
// }

#endif