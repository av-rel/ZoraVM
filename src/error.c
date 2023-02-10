#ifndef ERROR_C
#define ERROR_C

#include <stdio.h>
#include <stdlib.h>

#include "./include/error.h"

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
  case ERROR_MISMATCH_TYPE:
    return "Comparision of Mismatched Types";
  case ERROR_UNKNOWN_INST:
    return "Unknown Instruction";
  default:
    return "Unknown ERROR Detected";
  }
}

#endif
