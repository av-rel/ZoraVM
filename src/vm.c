#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "../include/vm.h"
#include "./trap.c"

Zvm *zvm_new() {
  Zvm *zvm = (Zvm *) malloc(sizeof(Zvm));
  /* zvm->globals = (int*) calloc(1, VM_CAP); */
  zvm->ip = 0;
  zvm->len = 0;
  return zvm;
}

void zvm_exec(Zvm *vm, Program prog) {
  switch (prog.op) {
  case OP_STORE:
    vm->globals[vm->len++] = prog.val;
    handleTrap(vm);
    /* vm->ip++; */
    break;
  case OP_DISPOSE:
    vm->globals[--vm->len] = 0;
    handleTrap(vm);
    /* vm->ip++; */
    break;
  case OP_PRINT:
    printf("%lld\n", vm->globals[--vm->len]);
    handleTrap(vm);
    break;
  case OP_SCAN:
    scanf("%lld", &vm->globals[vm->len++]);
    handleTrap(vm);
    break;
  case OP_ADD:
    vm->globals[vm->len-2] += vm->globals[vm->len-- - 1];
    handleTrap(vm);
    break;
  case OP_SUB:
    vm->globals[vm->len-2] -= vm->globals[vm->len-- - 1];
    handleTrap(vm);
    break;
  case OP_MUL:
    vm->globals[vm->len-2] *= vm->globals[vm->len-- - 1];
    handleTrap(vm);
    break;
  case OP_DIV: {
    long long int divisor = vm->globals[vm->len-- - 1];
    if (divisor == 0) activateTrap(TRAP_DIV_BY_0);
    vm->globals[vm->len-2] /= divisor;
    handleTrap(vm);
    break;
    }
  case OP_MOD:
    vm->globals[vm->len-2] %= vm->globals[vm->len-- - 1];
    handleTrap(vm);
    break;
  case OP_POW:
    vm->globals[vm->len-2] = pow(vm->globals[vm->len-- - 1], vm->globals[vm->len-2]);
    handleTrap(vm);
    break;
  case OP_INC:
    ++vm->globals[vm->len-1];
    break;
  case OP_DEC:
    --vm->globals[vm->len-1];
    break;
  case OP_TIME: {
    time_t currentTime;
    /* struct tm *timeinfo; */
    time(&currentTime);
    /* timeinfo = localtime(&currentTime); */
    vm->globals[vm->len++] = currentTime; 
    /* printf("%d:%d:%d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec); */
    break;
  }
  case OP_DEBUG: {
    printf("[Stack]:\n");
    for (int i = 0; i < vm->len; i++){
      printf("\t%lld\n", vm->globals[i]);
    }
    if (vm->len < 1) printf("\t<Empty>\n");
    break;
  }
  case OP_RET:
    exit(vm->globals[vm->len--]);
  case OP_NONE:
    break;
  case OP_EXIT:
    exit(0);
  default:
    fprintf(stderr, "Unknown Instruction\n");
    exit(0);
  }
 }
