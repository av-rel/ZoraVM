#ifndef _VM_H
#define _VM_H

#include "./error.h"
#include "./inst.h"

#define MEM_SIZE 69
#define STACK_SIZE 1024

#define VM_INIT(vm) (vm.state = 1, vm.ip = 0, vm.sp = 0, vm.mp = 0)

typedef enum { DATA_INTEGER, DATA_FLOATING, DATA_STRING } DATA_KIND;

typedef struct {
  // TODO: add more data types (string, float, int, .. , function, array, struct)
  DATA_KIND kind;
  union {
    char *string;
    long long int integer;
    double floating;
  } val;
  void* ptr;
} Data;

typedef struct {
  int state;          //state of vm | HALT or not
  int *pc;            //program counter holding address of current execution data
  int ip;             // instruction pointer
  int sp;             // stack pointer
  int mp;             // mem pointer
  Data mem[MEM_SIZE]; // mem stack
  Data stack[STACK_SIZE]; //stack
} VM;

typedef struct {
  Inst inst;
  Data entry;
} Program;

ERROR VM_Execute(VM *vm, Program prog);

#endif
