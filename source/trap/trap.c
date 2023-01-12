#ifndef TRAP_C
#define TRAP_C

#include <stdio.h>
#include <stdlib.h>

#include "./trap.h"

void activateTrap(TRAP_TYPE trap) {
  switch (trap) {
  case TRAP_OK:
    return;
  case TRAP_STACKOVERFLOW: {
    printf("[Trap Activated] StackOverflow\n");
    break;
  }
  case TRAP_STACKUNDERFLOW: {
    printf("[Trap Activated] StackUnderflow\n");
    break;
  }
  case TRAP_UNKNOWN:
  default:
    printf("[Trap Activated] Unknown Trap Detected");
  }
  exit(0);
}

#endif