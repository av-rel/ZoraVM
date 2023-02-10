#ifndef _VM_H
#define _VM_H

#include "./error.h"
#include "./inst.h"

#define MEM_SIZE 32
#define STACK_SIZE 1024

enum DATA_KIND { DATA_INTEGER = 0, DATA_FLOATING, DATA_STRING };

typedef struct {
  // TODO: add more data types (string, float, int, function, array, struct)
  enum DATA_KIND kind;
  union {
    char *string;
    int integer;
    float floating;
  } data;
} Data;

typedef struct {
  int state;
  int ip; // instruction pointer
  int sp; // stack pointer
          //   int mp;
          //   Data mem[MEM_SIZE];
  Data stack[STACK_SIZE];
} VM;

typedef struct {
  Inst inst;
  Data entry;
} Program;

void VM_Init(VM *vm);
ERROR VM_Execute(VM *vm, Program prog);

#endif
