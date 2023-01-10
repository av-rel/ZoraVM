#ifndef ZVM_H
#define ZVM_H

#include <stdint.h>

#define STACK_SIZE 1024

#define i16 int16_t
#define i32 int32_t
#define i64 int64_t
typedef enum {
  OP_PUSH,
  OP_POP,
  OP_MOVE,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_MOD,
  OP_PRINT,
  OP_HALT,
  OP_NONE,
} OP_Type;

typedef struct {
  i32 stack[STACK_SIZE];
  i32 size;
  i32 ip;
} Zvm;

typedef struct {
  OP_Type op;
  i32 val;
} Inst;

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

#endif