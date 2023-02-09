#ifndef TRAP_H
#define TRAP_H

typedef enum {
  TRAP_OK,
  TRAP_STACK_OVERFLOW,
  TRAP_STACK_UNDERFLOW,
  TRAP_DIV_BY_0,
} TRAP;

#endif