#ifndef ERROR_C
#define ERROR_C

#include <stdio.h>
#include <stdlib.h>

#include "./include/error.h"

char *Errors[] = {
    [ERROR_OK] = "OK",
    [ERROR_DIV_BY_0] = "Division By Zero",
    [ERROR_STACK_OVERFLOW] = "Stack Overflow",
    [ERROR_STACK_UNDERFLOW] = "Stack Underflow",
    [ERROR_MEMORY_FULL] = "Memory Full",
    [ERROR_MEMORY_EMPTY] = "Memory Empty",
    [ERROR_MISMATCH_TYPE] = "Mismatched Types",
    [ERROR_UNEXPECTED_TYPE] = "Unexpected Type",
    [ERROR_ILLEGAL_INST] = "Illegal Instruction",
    [ERROR_UNKNOWN_TYPE] = "Unknown Type",
    [ERROR_UNKNOWN_INST] = "Unknown Instruction",
    [ERROR_UNIMPLEMENTED] = "Unimplemented Instruction",
    [ERROR_PROGRAM_NOT_FOUND] = "No Program ",
};

char *ERROR_as_str(ERROR error) {
  switch (error) {
  case ERROR_OK:
    return "OK";
  case ERROR_DIV_BY_0:
    return "Division By Zero";
  case ERROR_STACK_OVERFLOW:
    return "Pushed To Full Stack";
  case ERROR_STACK_UNDERFLOW:
    return "Popped from Empty Stack";
  case ERROR_MEMORY_FULL:
    return "Memory Full";
  case ERROR_MEMORY_EMPTY:
    return "Memory Empty";
  case ERROR_MISMATCH_TYPE:
    return "Comparision of Mismatched Types";
  case ERROR_UNEXPECTED_TYPE:
    return "Unexpected Type";
  case ERROR_ILLEGAL_INST:
    return "Illegal Instruction";
  case ERROR_UNKNOWN_TYPE:
    return "Unknown Type";
  case ERROR_UNKNOWN_INST:
    return "Unknown Instruction";
  case ERROR_UNIMPLEMENTED:
    return "Unimplemented Instruction";
  case ERROR_PROGRAM_NOT_FOUND:
    return "No Program Found";
  default:
    return "Unknown ERROR Detected";
  }
}

#endif
