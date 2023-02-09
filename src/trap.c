#ifndef TRAP_C
#define TRAP_C

#include <stdio.h>
#include <stdlib.h>

#include "./include/trap.h"

void activateTrap(TRAP trap) {
  switch (trap) {
  case TRAP_OK:
    return;
  case TRAP_DIV_BY_0:
    printf("[Trap]: Division By Zero\n");
    break;
  default:
    printf("[Trap]: Unknown Trap Detected");
  }
  exit(0);
}

#endif
