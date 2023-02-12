#ifndef TRAP_H
#define TRAP_H

typedef enum {
  ERROR_OK = 0,            //  all ok
  ERROR_REG_OUT_OF_BOUNDS, // Illegal register access
  ERROR_STACK_OVERFLOW,    //  stack is full
  ERROR_STACK_UNDERFLOW,   //  stack op failure due to less value than required
  ERROR_MEMORY_FULL,       // memory full
  ERROR_MEMORY_EMPTY,      // memory empty
  ERROR_DIV_BY_0,          // Div by zero
  ERROR_NOT_ENOUGH_OPERANDS, // not enough operands on the memory for execution
  ERROR_UNEXPECTED_TYPE,     // unexpected type
  ERROR_ILLEGAL_INST,        // illegal instruction
  ERROR_UNKNOWN_TYPE,        // unknown type
  ERROR_UNKNOWN_INST,        // unknown instruction
  ERROR_UNIMPLEMENTED,       // unimplemented instruction
  TOTAL_ERRORNO
} ERROR;

#endif
