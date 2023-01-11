#ifndef ZVM_C
#define ZVM_C

#include "../include/vm.h"
#include "./lexer/lexer.c"
#include "./stack.c"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Zvm *zvm_new() {
  Zvm *_zvm = (Zvm *)calloc(1, sizeof(Zvm));
  _zvm->size = 0;
  _zvm->ip = _zvm->size;
  return _zvm;
}

Inst *inst_new() {
  Inst *inst = (Inst *)calloc(1, sizeof(Inst));
  inst->operation = OP_HALT;
  inst->operand = 0;
  return inst;
}

// void vm_run(lexer_struct *lexer) {

//   while (lexer->cur != '\0') {
//     lexer_skip_ws(lexer);
//     lexer_skip_comment(lexer);

//     lexer_advance(lexer);
//   }
// }

void vm_exec(Zvm *vm, Inst *program) {
  switch (program->operand) {
  case OP_PUSH:
    stack_push(vm, program);
    break;
  case OP_POP:
    stack_pop(vm, program);
    break;
  case OP_MOVE:
    stack_move(vm, program);
    break;
  case OP_ADD:
    stack_add(vm, program);
    break;
  case OP_SUB:
    stack_sub(vm, program);
    break;
  case OP_MUL:
    stack_mul(vm, program);
    break;
  case OP_DIV:
    stack_div(vm, program);
    break;
  case OP_MOD:
    stack_mod(vm, program);
    break;
  case OP_PRINT:
    stack_print(program);
  case OP_LOG:
    stack_log(vm, program);
    break;
  case OP_NONE:
    break;
  default:
    printf("Unknown instruction %d\n", program->operand);
  }
}

#endif