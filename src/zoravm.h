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
  char state;  // state of vm
  int argc;
  char** argv;

  unsigned long int size;     //no. of programs
  unsigned long int memsize;
  unsigned long int stacksize;

  long int ip;    // instruction pointer
  long int sp;    // stack pointer
  long int mp;    // mem pointer
  long int fp;   // frame pointer

  ZoraVM_Data *mem;     // mem stack
  ZoraVM_Data *stack; // stack
} ZoraVM;


ZoraVM ZoraVM_Init(unsigned int cap, int argc, char** argv);
void ZoraVM_Dispose(ZoraVM *vm);
ZORAVM_ERROR ZoraVME_Execute(ZoraVM *vm, ZoraVM_Program prog);

#endif
