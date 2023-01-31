#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/vm.h"

#define MAX_HEAP 2048

Zvm *zvm_new() {
  Zvm *zvm = (Zvm *) malloc(sizeof(Zvm));
  zvm->globals = (int*) calloc(1, MAX_HEAP);
  zvm->ip = 0;
  zvm->len = 0;
  return zvm;
}

void zvm_exec(Zvm *vm, Program prog) {
  switch (prog.op) {
  case OP_STORE:
    vm->globals[vm->len++] = prog.val;
    vm->ip++;
    break;
  case OP_DISPOSE:
    vm->globals[vm->ip] = 0;
    vm->ip++;
    break;
  case OP_PRINT:
    printf("%d\n", vm->globals[vm->ip]);
    break;
  case OP_SCAN:
    scanf("%d", &vm->globals[vm->len++]);
    break;
  case OP_MOVEIP:
    vm->ip = prog.val+1;
    break;
  case OP_NONE:
    break;
  case OP_EXIT:
    exit(0);
  default:
    fprintf(stderr, "Unknown Instruction\n");
    exit(0);
    break;
  }
 }
