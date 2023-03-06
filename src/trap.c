#ifndef _ZORAVM_TRAP_C
#define _ZORAVM_TRAP_C

typedef enum {
  ZORAVM_ERROR_OK = 0,            //  all ok
  ZORAVM_ERROR_REG_OUT_OF_BOUNDS, // Illegal register access
  ZORAVM_ERROR_STACK_OVERFLOW,    //  stack is full
  ZORAVM_ERROR_STACK_UNDERFLOW,   //  stack op failure due to less value than required
  ZORAVM_ERROR_MEMORY_FULL,       // memory full
  ZORAVM_ERROR_MEMORY_EMPTY,      // memory empty
  ZORAVM_ERROR_DIV_BY_0,          // Div by zero
  ZORAVM_ERROR_NOT_ENOUGH_OPERANDS, // not enough operands on the memory for execution
  ZORAVM_ERROR_UNEXPECTED_TYPE,     // unexpected type
  ZORAVM_ERROR_ILLEGAL_INST,        // illegal instruction
  ZORAVM_ERROR_ILLEGAL_INST_TYPE,        // illegal instruction
  ZORAVM_ERROR_UNKNOWN_TYPE,        // unknown type
  ZORAVM_ERROR_UNKNOWN_INST,        // unknown instruction
  ZORAVM_ERROR_UNIMPLEMENTED,       // unimplemented instruction
  TOTAL_ZORAVM_ERROR
} ZORAVM_ERROR;

char *ZoraVM_Errors[] = {
    [ZORAVM_ERROR_OK] = "OK",
    [ZORAVM_ERROR_REG_OUT_OF_BOUNDS] = "Register got out of bounds",
    [ZORAVM_ERROR_DIV_BY_0] = "Division by Zero",
    [ZORAVM_ERROR_NOT_ENOUGH_OPERANDS] = "Not enough operands on the memory for execution",
    [ZORAVM_ERROR_STACK_OVERFLOW] = "Stack Overflow",
    [ZORAVM_ERROR_STACK_UNDERFLOW] = "Stack Underflow",
    [ZORAVM_ERROR_MEMORY_FULL] = "Memory full for allocation",
    [ZORAVM_ERROR_MEMORY_EMPTY] = "Memory empty for execution",
    [ZORAVM_ERROR_UNEXPECTED_TYPE] = "Unexpected type",
    [ZORAVM_ERROR_ILLEGAL_INST] = "Illegal Instruction",
    [ZORAVM_ERROR_ILLEGAL_INST_TYPE] = "Operation between different type of operands",
    [ZORAVM_ERROR_UNKNOWN_TYPE] = "Unknown type",
    [ZORAVM_ERROR_UNKNOWN_INST] = "Unknown instruction",
    [ZORAVM_ERROR_UNIMPLEMENTED] = "Unimplemented Instruction",
};

#endif
