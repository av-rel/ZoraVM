#ifndef TRAP_C
#define TRAP_C

#include <stdio.h>
#include <stdlib.h>

#include "./include/trap.h"
#include "./include/vm.h"

void activateTrap(TRAP trap) {
  switch (trap) {
  case TRAP_OK:
    return;
  case TRAP_DIV_BY_0:
    printf("[Trap]: Division By Zero\n");
    break;
  case TRAP_STACK_OVERFLOW:
    printf("[Trap]: Stack Overflow\n");
    break;
  case TRAP_STACK_UNDERFLOW:
    printf("[Trap]: Stack Underflow\n");
    break;
  default:
    printf("[Trap]: Unknown Trap Detected");
  }
  exit(0);
}

#endif
