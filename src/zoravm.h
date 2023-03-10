#ifndef ZORAVM_H
#define ZORAVM_H

#include "./trap.h"
#include "./inst.h"

typedef struct {
  ZORAVM_DATAKIND kind;
  union {
    char *string;
    long long int integer;
    double floating;
  } val;
  void *ptr; //todo
} ZoraVM_Data;

typedef struct {
  ZORAVM_INST inst;
  ZoraVM_Data entry;
} ZoraVM_Program;

typedef struct {
  int state;  // state of vm
  unsigned int size;     //no. of programs
  unsigned int memsize;
  unsigned int stacksize;
  int ip;    // instruction pointer
  int sp;    // stack pointer
  int mp;    // mem pointer
  int fp;   // frame pointer
  ZoraVM_Data *mem;     // mem stack
  ZoraVM_Data *stack; // stack
} ZoraVM;


ZoraVM ZoraVM_Init(unsigned int cap);
void ZoraVM_Dispose(ZoraVM *vm);
ZORAVM_ERROR ZoraVME_Execute(ZoraVM *vm, ZoraVM_Program prog);

#endif
