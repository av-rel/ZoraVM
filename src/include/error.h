#ifndef ERROR_H
#define ERROR_H

typedef enum {
  ERROR_OK = 0,            //  all ok
  ERROR_REG_OUT_OF_BOUNDS, // Illegal register access
  ERROR_STACK_OVERFLOW,    //  stack is full
  ERROR_STACK_UNDERFLOW,   //  stack op failure due to less value than required
  ERROR_MEMORY_FULL,       // memory full
  ERROR_MEMORY_EMPTY,      // memory empty
  ERROR_DIV_BY_0,          // Div by zero
  ERROR_MISMATCH_TYPE,     // comparision between different types
  ERROR_UNEXPECTED_TYPE,   // unexpected type
  ERROR_ILLEGAL_INST,      // illegal instruction
  ERROR_UNKNOWN_TYPE,      // unknown type
  ERROR_UNKNOWN_INST,      // unknown instruction
  ERROR_UNIMPLEMENTED,     // unimplemented instruction
  ERROR_PROGRAM_NOT_FOUND, // program not found
  ERROR_NUMBER_OUT_OF_RANGE,
  TOTAL_ERRORNO
} ERROR;

#endif
