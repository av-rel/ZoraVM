#ifndef ERROR_H
#define ERROR_H

typedef enum {
  ERROR_OK = 0,            //  all ok
  ERROR_UNKNOWN_INST,      // unknown instruction
  ERROR_STACK_OVERFLOW,    //  stack is full
  ERROR_STACK_UNDERFLOW,   //  stack op failure due to less value than required
  ERROR_REG_OUT_OF_BOUNDS, // Illegal register access
  ERROR_DIV_BY_0,          // Div by zero
  ERROR_MISMATCH_TYPE,     // comparision between different types
} ERROR;

#endif
