#ifndef TRAP_C
#define TRAP_C

#include <stdio.h>
#include <stdlib.h>

#include "../include/trap.h"

void activateTrap(TRAP_TYPE trap) {
  switch (trap) {
  case TRAP_OK:
    return;
  case TRAP_UNKNOWN:
  default:
    printf("Trap: Unknown Trap Detected");
  }
  exit(0);
}

#endif
