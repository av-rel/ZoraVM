#ifndef TRAP_C
#define TRAP_C

#include <stdio.h>
#include <stdlib.h>

#include "../include/trap.h"
#include "../include/vm.h"

void activateTrap(TRAP_TYPE trap) {
  if (trap == TRAP_OK) return;
  switch (trap) {
  case TRAP_STACKOVERFLOW:
    printf("\n[TRAP]: StackOverflow - VM capacity reached\n");
    break;
  case TRAP_STACKUNDERFLOW:
    printf("\n[TRAP]: StackUnderflow - VM has not enough globals\n");
    break;
  case TRAP_DIV_BY_0:
    printf("\n[TRAP]: Division By Zero\n");
    break;
  default:
    printf("\n[Trap]: Unknown Trap Detected");
  }
  exit(0);
}

void handleTrap(Zvm* vm){
  if (vm->len >= VM_CAP){
    activateTrap(TRAP_STACKOVERFLOW);
  }
  else if (vm->len <= 0){
    activateTrap(TRAP_STACKUNDERFLOW);
  }
}

#endif
