#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// mem
/* typedef struct { */
/*     uint8_t *memory; */
/*     uint16_t pc; */
/*     uint16_t sp; */
/*     uint16_t bp; */
/*     uint16_t registers[8]; */
/*     uint8_t flags; */
/* } zvm_t; */

#define STACK_SIZE 1024
#define st size_t
#define i8 int8_t
#define u8 uint8_t
#define i16 int16_t
#define u16 uint16_t
#define i32 int32_t
#define u32 uint32_t
#define i64 int64_t
#define u64 uint64_t

typedef struct {
    i32 stack[STACK_SIZE];
    st stack_size;
} Zvm;

typedef enum{
    OP_Push,
    OP_Pop,
    OP_Move,
    OP_Add,
    OP_Sub,
    OP_Mul,
    OP_Div,
    OP_Mod,
    OP_Log
} OP_Type;

typedef struct {
    OP_Type op;
    st val;
} Inst;

void stack_push(Zvm *vm, st val){
    if(vm->stack_size >= STACK_SIZE){
        printf("Stack overflow\n");
        exit(0);
    }
    vm->stack[vm->stack_size++] = val;
}

void stack_pop(Zvm *vm){
    if (vm->stack_size <= 0){
        printf("Stack underflow\n");
        exit(0);
    }
    vm->stack_size--;
}
