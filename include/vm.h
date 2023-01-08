// vm instance
#ifndef ZVM_H
#define ZVM_H

#include <stdint.h>

#define STACK_SIZE 1024

#define i16 int16_t
#define i32 int32_t
#define i64 int64_t

#define PUSH(vm, val) stack_push(vm, val);
#define POP(vm) stack_pop(vm);
#define MOVE(vm) stack_move(vm);
#define DUP(vm) stack_dup(vm);
#define SWAP(vm) stack_swap(vm);
#define ADD(vm) stack_add(vm);
#define SUB(vm) stack_sub(vm);
#define MUL(vm) stack_mul(vm);
#define DIV(vm) stack_div(vm);
#define MOD(vm) stack_mod(vm);
#define LOG(vm) stack_print(vm);

typedef enum {
  OP_Push,
  OP_Pop,
  OP_Move,
  OP_Add,
  OP_Sub,
  OP_Mul,
  OP_Div,
  OP_Mod,
  OP_Print,
  OP_Silent,
} OP_Type;

typedef struct {
  OP_Type op;
  i32 val;
} Inst;

typedef struct {
  i32 stack[STACK_SIZE];
  i32 size;
  Inst inst;
} Zvm;

#endif