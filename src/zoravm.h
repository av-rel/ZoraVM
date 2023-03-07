#ifndef _ZORAVM_H
#define _ZORAVM_H

#include "./inst.h"
#include "./trap.c"

typedef enum {
  ZORAVM_DATA_STRING,
  ZORAVM_DATA_INTEGER,
  ZORAVM_DATA_FLOATING,
} ZORAVM_DATA_KIND;

#define ZoraVM_KindAsStr(kind) (kind == ZORAVM_DATA_STRING ? "string" : (kind == ZORAVM_DATA_INTEGER ? "integer" : (kind == ZORAVM_DATA_FLOATING ? "float" : "unknown" )))

typedef struct {
  ZORAVM_DATA_KIND kind;
  union {
    char *string;
    long long int integer;
    double floating;
  } val;
  void *ptr;
} ZoraVM_Data;

typedef struct {
  ZoraVM_Inst inst;
  ZoraVM_Data entry;
} ZoraVM_Program;

typedef struct {
  int state;  // state of vm
  int size;     //no. of programs
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
