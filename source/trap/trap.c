#ifndef TRAP_C
#define TRAP_C

#include <stdio.h>
#include <stdlib.h>

#include "./trap.h"

void activateTrap(TRAP_TYPE trap) {
  switch (trap) {
  case TRAP_OK: {
  }
  case TRAP_STACKOVERFLOW: {
    printf("[Trap] StackOverflow\n");
    break;
  }
  case TRAP_STACKUNDERFLOW: {
    printf("[Trap] StackUnderflow\n");
    break;
  }
  case TRAP_UNKNOWN:
  default:
    printf("[Trap] Unknown Trap Activated");
  }
  exit(0);
}

#endif