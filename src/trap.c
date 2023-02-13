#ifndef TRAP_C
#define TRAP_C

#include <stdio.h>
#include <stdlib.h>

#include "./include/trap.h"

char *Errors[] = {
    [ERROR_OK] = "OK",
    [ERROR_REG_OUT_OF_BOUNDS] = "Register got out of bounds",
    [ERROR_DIV_BY_0] = "Division by Zero",
    [ERROR_NOT_ENOUGH_OPERANDS] = "Not enough operands on the memory for execution",
    [ERROR_STACK_OVERFLOW] = "Stack Overflow",
    [ERROR_STACK_UNDERFLOW] = "Stack Underflow",
    [ERROR_MEMORY_FULL] = "Memory full for allocation",
    [ERROR_MEMORY_EMPTY] = "Memory empty for execution",
    [ERROR_UNEXPECTED_TYPE] = "Unexpected type",
    [ERROR_ILLEGAL_INST] = "Illegal Instruction",
    [ERROR_ILLEGAL_INST_TYPE] = "Operation between different type of operands",
    [ERROR_UNKNOWN_TYPE] = "Unknown type",
    [ERROR_UNKNOWN_INST] = "Unknown instruction",
    [ERROR_UNIMPLEMENTED] = "Unimplemented Instruction",
};

#endif
