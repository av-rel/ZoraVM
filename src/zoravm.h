#ifndef _ZORAVM_H
#define _ZORAVM_H

#include "./inst.h"
#include "./trap.c"

#define ZORAVM_MEM_SIZE 69
#define ZORAVM_STACK_SIZE 6969

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
  int state;  // state of vm | HALT or not
  int np;     //no. of programs
  int ip;    // instruction pointer
  int sp;    // stack pointer
  int mp;    // mem pointer
  ZoraVM_Data mem[ZORAVM_MEM_SIZE];     // mem stack
  ZoraVM_Data stack[ZORAVM_STACK_SIZE]; // stack
} ZoraVM;

typedef struct {
  ZoraVM_Inst inst;
  ZoraVM_Data entry;
} ZoraVM_Program;

ZoraVM ZoraVM_Init(int np);
ZORAVM_ERROR ZoraVME_Execute(ZoraVM *vm, ZoraVM_Program prog);

#endif
