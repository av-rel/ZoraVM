#ifndef ERROR_H
#define ERROR_H

typedef enum {
  ERROR_OK = 0,            //  all ok
  ERROR_REG_OUT_OF_BOUNDS, // Illegal register access
  ERROR_STACK_OVERFLOW,    //  stack is full
  ERROR_STACK_UNDERFLOW,   //  stack op failure due to less value than required
  ERROR_DIV_BY_0,          // Div by zero
  ERROR_MISMATCH_TYPE,     // comparision between different types
  ERROR_UNKNOWN_TYPE,      // unknown type
  ERROR_UNKNOWN_INST,      // unknown instruction
  TOTAL_ERROR
} ERROR;

#endif
