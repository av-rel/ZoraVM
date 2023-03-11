#ifndef ZORAVM_EXEC_C
#define ZORAVM_EXEC_C

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./zoravm.h"
#include "./inst.c"
#include "./trap.c"
#include "../inc/math.c"
#include "inst.h"
#include "trap.h"


// store to the stack from mem
ZORAVM_ERROR ZoraVME_Store(ZoraVM *vm, ZoraVM_Data data) {
  if (vm->sp >= vm->stacksize) return ZORAVM_ERROR_STACK_OVERFLOW;
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  vm->stack[data.val.integer] = vm->mem[--vm->mp];
  vm->sp++;
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// load from stack to the mem
ZORAVM_ERROR ZoraVME_Load(ZoraVM *vm, ZoraVM_Data data) {
  if (vm->sp < 1) return ZORAVM_ERROR_STACK_UNDERFLOW;
  if (vm->mp >= vm->memsize) return ZORAVM_ERROR_MEMORY_FULL;

  vm->mem[vm->mp++] = vm->stack[data.val.integer];
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// push to the memory stack
ZORAVM_ERROR ZoraVME_Push(ZoraVM *vm, ZoraVM_Data data) {
  if (vm->mp >= vm->memsize) return ZORAVM_ERROR_MEMORY_FULL;

  switch (data.kind) {
  case ZORAVM_DATA_INT:
    vm->mem[vm->mp] = (ZoraVM_Data){ZORAVM_DATA_INT, .val.integer = data.val.integer};
    break;
  case ZORAVM_DATA_FLOAT:
    vm->mem[vm->mp] = (ZoraVM_Data){ZORAVM_DATA_FLOAT, .val.floating = data.val.floating};
    break;
  case ZORAVM_DATA_STRING:
    vm->mem[vm->mp] = (ZoraVM_Data){ZORAVM_DATA_STRING, .val.string = data.val.string};
    break;
  default:
    return ZORAVM_ERROR_UNKNOWN_TYPE;
  }

  vm->mp++;
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// pop from the memory stack
ZORAVM_ERROR ZoraVME_Pop(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// duplicate memory values
ZORAVM_ERROR ZoraVME_Dup(ZoraVM *vm) {
  if (vm->mp >= vm->memsize) return ZORAVM_ERROR_MEMORY_FULL;
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  vm->mem[vm->mp] = vm->mem[vm->mp - 1];
  vm->mp++;
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// swap memory values
ZORAVM_ERROR ZoraVME_Swap(ZoraVM *vm) {
  if (vm->mp >= vm->memsize) return ZORAVM_ERROR_MEMORY_FULL;
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data tmp = vm->mem[vm->mp - 2];
  vm->mem[vm->mp - 2] = vm->mem[vm->mp - 1];
  vm->mem[vm->mp - 1] = tmp;
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// add the two val from mem stack and push it back to the mem stack
ZORAVM_ERROR ZoraVME_Add(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind != two.kind) return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT) {
    vm->mem[vm->mp - 2].val.integer += two.val.integer;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  } else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING) {
    vm->mem[vm->mp - 2].val.string = strcat(vm->mem[vm->mp - 2].val.string, two.val.string);
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_STRING;
  } else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT) {
    vm->mem[vm->mp - 2].val.floating += two.val.floating;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_FLOAT;
  } else
    return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// subtract the two val from mem stack and push it back to the mem stack
ZORAVM_ERROR ZoraVME_Sub(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind != two.kind) return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT) {
    vm->mem[vm->mp - 2].val.integer -= two.val.integer;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  } else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT) {
    vm->mem[vm->mp - 2].val.floating -= two.val.floating;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_FLOAT;
  } else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    return ZORAVM_ERROR_ILLEGAL_INST;
  else
    return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// multiply the two val from mem stack and push it back to the mem stack
ZORAVM_ERROR ZoraVME_Mul(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind != two.kind) return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT) {
    vm->mem[vm->mp - 2].val.integer *= two.val.integer;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  } else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT) {
    vm->mem[vm->mp - 2].val.floating *= two.val.floating;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_FLOAT;
  } else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    return ZORAVM_ERROR_ILLEGAL_INST;
  else
    return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// divide the two val from mem stack and push it back to the mem stack
ZORAVM_ERROR ZoraVME_Div(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind != two.kind) return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT) {
    vm->mem[vm->mp - 2].val.integer /= two.val.integer;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  } else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT) {
    vm->mem[vm->mp - 2].val.floating /= two.val.floating;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_FLOAT;
  } else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    return ZORAVM_ERROR_ILLEGAL_INST;
  else return ZORAVM_ERROR_UNKNOWN_TYPE;

  return ZORAVM_ERROR_OK;
}

// mod the two val from mem stack and push it back to the mem stack
ZORAVM_ERROR ZoraVME_Mod(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind != two.kind) return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT) {
    vm->mem[vm->mp - 2].val.integer %= two.val.integer;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  } else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT)
    return ZORAVM_ERROR_ILLEGAL_INST;
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    return ZORAVM_ERROR_ILLEGAL_INST;
  else
    return ZORAVM_ERROR_UNKNOWN_TYPE;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Inc(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_INT)
    ++vm->mem[vm->mp - 1].val.integer;
  else if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_FLOAT)
    ++vm->mem[vm->mp - 1].val.floating;
  else if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_STRING)
    ++vm->mem[vm->mp - 1].val.string;
  else return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Dec(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_INT)
    --vm->mem[vm->mp - 1].val.integer;
  else if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_FLOAT)
    --vm->mem[vm->mp - 1].val.floating;
  else if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_STRING)
    return --vm->mem[vm->mp - 1].val.floating;
  else return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Pow(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (two.kind != ZORAVM_DATA_INT) return ZORAVM_ERROR_ILLEGAL_INST;

  if (one.kind == ZORAVM_DATA_INT) {
    vm->mem[vm->mp - 2].val.integer = ZORA_M_pow(one.val.integer, two.val.integer);
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  } else if (one.kind == ZORAVM_DATA_FLOAT) {
    vm->mem[vm->mp - 2].val.floating = ZORA_M_pow(one.val.floating, two.val.integer);
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_FLOAT;
  } else if (one.kind == ZORAVM_DATA_STRING)
    return ZORAVM_ERROR_UNIMPLEMENTED;
  else return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Sin(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  ZoraVM_Data exp = vm->mem[vm->mp - 1];

  if (exp.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 1].val.floating = ZORA_M_sin(exp.val.integer);
  else if (exp.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 1].val.floating = ZORA_M_sin(exp.val.floating);
  else return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  vm->mem[vm->mp - 1].kind = ZORAVM_DATA_FLOAT;

  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Cos(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  ZoraVM_Data exp = vm->mem[vm->mp - 1];

  if (exp.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 1].val.floating = ZORA_M_sin(exp.val.integer);
  else if (exp.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 1].val.floating = ZORA_M_sin(exp.val.floating);
  else return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  vm->mem[vm->mp - 1].kind = ZORAVM_DATA_FLOAT;

  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Tan(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  ZoraVM_Data exp = vm->mem[vm->mp - 1];

  if (exp.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 1].val.floating = ZORA_M_sin(exp.val.integer);
  else if (exp.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 1].val.floating = ZORA_M_sin(exp.val.floating);
  else return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  vm->mem[vm->mp - 1].kind = ZORAVM_DATA_FLOAT;

  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Factorial(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  ZoraVM_Data data = vm->mem[vm->mp - 1];

  if (data.kind != ZORAVM_DATA_INT)
    return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  vm->mem[vm->mp - 1].val.integer = ZORA_M_factorial(data.val.integer);
  vm->mem[vm->mp - 1].kind = ZORAVM_DATA_INT;

  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Pi(ZoraVM *vm) {
  if (vm->mp >= vm->memsize) return ZORAVM_ERROR_MEMORY_FULL;

  vm->mem[vm->mp].val.floating = ZORA_M_PI;
  vm->mem[vm->mp].kind = ZORAVM_DATA_FLOAT;

  vm->mp++;
  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Abs(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  ZoraVM_Data data = vm->mem[vm->mp - 1];

  if (data.kind == ZORAVM_DATA_INT) {
    data.val.integer = ZORA_M_abs(data.val.integer);
    data.kind = ZORAVM_DATA_INT;
  }
  else if (data.kind == ZORAVM_DATA_FLOAT) {
    data.val.floating = ZORA_M_abs(data.val.floating);
    data.kind = ZORAVM_DATA_FLOAT;
  }
  else return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->mem[vm->mp - 1] = data;

  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Sqrt(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  ZoraVM_Data data = vm->mem[vm->mp - 1];

  if (data.kind == ZORAVM_DATA_INT) data.val.floating = ZORA_M_sqrt(data.val.integer);
  else if (data.kind == ZORAVM_DATA_FLOAT) data.val.floating = ZORA_M_abs(data.val.floating);
  else return ZORAVM_ERROR_UNIMPLEMENTED;

  data.kind = ZORAVM_DATA_FLOAT;
  vm->mem[vm->mp - 1] = data;
  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Max(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_STRING || two.kind == ZORAVM_DATA_STRING) return ZORAVM_ERROR_ILLEGAL_INST_TYPE;
  if (one.kind != two.kind) return ZORAVM_ERROR_ILLEGAL_INST;

  ZoraVM_Data data = (ZoraVM_Data) { .kind = one.kind };

  if (data.kind == ZORAVM_DATA_INT) {
    data.val.integer = ZORA_M_max(one.val.integer, two.val.integer);
    data.kind = ZORAVM_DATA_INT;
  }
  else if (data.kind == ZORAVM_DATA_FLOAT) {
    data.val.floating = ZORA_M_max(one.val.floating, two.val.floating);
    data.kind = ZORAVM_DATA_FLOAT;
  }
  else return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 1] = data;
  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Min(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_STRING || two.kind == ZORAVM_DATA_STRING) return ZORAVM_ERROR_ILLEGAL_INST_TYPE;
  if (one.kind != two.kind) return ZORAVM_ERROR_ILLEGAL_INST;

  ZoraVM_Data data = (ZoraVM_Data) { .kind = one.kind };

  if (data.kind == ZORAVM_DATA_INT) {
    data.val.integer = ZORA_M_min(one.val.integer, two.val.integer);
    data.kind = ZORAVM_DATA_INT;
  }
  else if (data.kind == ZORAVM_DATA_FLOAT) {
    data.val.floating = ZORA_M_min(one.val.floating, two.val.floating);
    data.kind = ZORAVM_DATA_FLOAT;
  }
  else return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 1] = data;
  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_And(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INT ||
      vm->mem[vm->mp - 2].kind != ZORAVM_DATA_INT)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer &= vm->mem[vm->mp - 1].val.integer;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Or(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;
  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INT ||
      vm->mem[vm->mp - 2].kind != ZORAVM_DATA_INT)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer |= vm->mem[vm->mp - 1].val.integer;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Xor(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INT ||
      vm->mem[vm->mp - 2].kind != ZORAVM_DATA_INT)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer ^= vm->mem[vm->mp - 1].val.integer;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Not(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INT)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 1].val.integer = ~vm->mem[vm->mp - 1].val.integer;
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Neg(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_STRING)
    return ZORAVM_ERROR_UNEXPECTED_TYPE;

  if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 1].val.floating = -vm->mem[vm->mp - 1].val.floating;
  else if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 1].val.integer = -vm->mem[vm->mp - 1].val.integer;
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Shl(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INT ||
      vm->mem[vm->mp - 2].kind != ZORAVM_DATA_INT)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer <<= vm->mem[vm->mp - 1].val.integer;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Shr(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INT ||
      vm->mem[vm->mp - 2].kind != ZORAVM_DATA_INT)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer >>= vm->mem[vm->mp - 1].val.integer;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpEq(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 2].val.integer = (int)one.val.integer == (int)two.val.integer;
  else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 2].val.integer = one.val.floating == two.val.floating;
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer =
        strcmp(one.val.string, two.val.string) == 0;
  else
    vm->mem[vm->mp - 2].val.integer = 0;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpNotEq(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 2].val.integer = (int)!((int)one.val.integer == (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 2].val.integer = !(one.val.floating == two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer =
        !(strcmp(one.val.string, two.val.string) == 0);
  else
    vm->mem[vm->mp - 2].val.integer = 1;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpGt(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 2].val.integer = (int)one.val.integer > (int)two.val.integer;
  else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 2].val.integer = one.val.floating > two.val.floating;
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = (strcmp(one.val.string, two.val.string) == 1);
  else
    vm->mem[vm->mp - 2].val.integer = 0;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpNotGt(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 2].val.integer = (int)!((int)one.val.integer > (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 2].val.integer = !(one.val.floating > two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = !(strcmp(one.val.string, two.val.string) == 1);
  else
    vm->mem[vm->mp - 2].val.integer = 1;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;


  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpLt(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 2].val.integer = (int)one.val.integer < (int)two.val.integer;
  else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 2].val.integer = one.val.floating < two.val.floating;
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = (strcmp(one.val.string, two.val.string) == -1);
  else
    vm->mem[vm->mp - 2].val.integer = 0;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpNotLt(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 2].val.integer = (int)!((int)one.val.integer < (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 2].val.integer = !(one.val.floating < two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = !(strcmp(one.val.string, two.val.string) == -1);
  else
    vm->mem[vm->mp - 2].val.integer = 1;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpGte(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 2].val.integer = (int)((int)one.val.integer > (int)two.val.integer || (int)one.val.integer == (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 2].val.integer = (one.val.floating > two.val.floating || one.val.floating == two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = (strcmp(one.val.string, two.val.string) == 1 || strcmp(one.val.string, two.val.string) == 0);
  else
    vm->mem[vm->mp - 2].val.integer = 0;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpNotGte(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 2].val.integer = (int)!((int)one.val.integer > (int)two.val.integer || (int)one.val.integer == (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 2].val.integer = !(one.val.floating > two.val.floating || one.val.floating == two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = !(strcmp(one.val.string, two.val.string) == 1 || strcmp(one.val.string, two.val.string) == 0);
  else
    vm->mem[vm->mp - 2].val.integer = 1;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpLte(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 2].val.integer = (int)one.val.integer < (int)two.val.integer || (int)one.val.integer == (int)two.val.integer;
  else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 2].val.integer = (one.val.floating < two.val.floating || one.val.floating == two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = (strcmp(one.val.string, two.val.string) == -1 || strcmp(one.val.string, two.val.string) == 0);
  else
    vm->mem[vm->mp - 2].val.integer = 0;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpNotLte(ZoraVM *vm) {
  if (vm->mp < 2) return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INT && two.kind == ZORAVM_DATA_INT)
    vm->mem[vm->mp - 2].val.integer = (int)!((int)one.val.integer < (int)two.val.integer || (int)one.val.integer == (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOAT && two.kind == ZORAVM_DATA_FLOAT)
    vm->mem[vm->mp - 2].val.integer = !(one.val.floating < two.val.floating || one.val.floating == two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = !(strcmp(one.val.string, two.val.string) == -1 || strcmp(one.val.string, two.val.string) == 0);
  else
    vm->mem[vm->mp - 2].val.integer = 1;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INT;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Jmp(ZoraVM *vm, ZoraVM_Program prog) {
  vm->ip = prog.entry.val.integer;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_JmpIf(ZoraVM *vm, ZoraVM_Program prog) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INT) return ZORAVM_ERROR_ILLEGAL_INST;

  if (vm->mem[vm->mp - 1].val.integer == 0) vm->ip++;
  else vm->ip = prog.entry.val.integer;

  vm->mp--;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_JmpIfNot(ZoraVM *vm, ZoraVM_Program prog) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INT) return ZORAVM_ERROR_ILLEGAL_INST;

  if (vm->mem[vm->mp - 1].val.integer != 0) vm->ip++;
  else vm->ip = prog.entry.val.integer;


  vm->mp--;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Call(ZoraVM *vm, ZoraVM_Program prog) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;
  
  unsigned long int rtnum = vm->mem[--vm->mp].val.integer;
  vm->mem[vm->mp++] = (ZoraVM_Data){.kind = ZORAVM_DATA_INT, .val.integer = vm->fp};
  vm->mem[vm->mp++] = (ZoraVM_Data){.kind = ZORAVM_DATA_INT, .val.integer = vm->ip};
  vm->fp = vm->sp;
  vm->ip = prog.entry.val.integer;
  vm->mem[vm->mp++]= (ZoraVM_Data){.kind = ZORAVM_DATA_INT, .val.integer = rtnum};

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CallIf(ZoraVM *vm, ZoraVM_Program prog) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[--vm->mp].val.integer == 0) return ZORAVM_ERROR_OK;

  unsigned long int rtnum = vm->mem[--vm->mp].val.integer;
  vm->mem[vm->mp++] = (ZoraVM_Data){.kind = ZORAVM_DATA_INT, .val.integer = vm->fp};
  vm->mem[vm->mp++] = (ZoraVM_Data){.kind = ZORAVM_DATA_INT, .val.integer = vm->ip};
  vm->fp = vm->sp;
  vm->ip = prog.entry.val.integer;
  vm->mem[vm->mp++]= (ZoraVM_Data){.kind = ZORAVM_DATA_INT, .val.integer = rtnum};

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CallIfNot(ZoraVM *vm, ZoraVM_Program prog) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[--vm->mp].val.integer != 0) return ZORAVM_ERROR_OK;
  
  unsigned long int rtnum = vm->mem[--vm->mp].val.integer;
  vm->mem[vm->mp++] = (ZoraVM_Data){.kind = ZORAVM_DATA_INT, .val.integer = vm->fp};
  vm->mem[vm->mp++] = (ZoraVM_Data){.kind = ZORAVM_DATA_INT, .val.integer = vm->ip};
  vm->fp = vm->sp;
  vm->ip = prog.entry.val.integer; 
  vm->mem[vm->mp++]= (ZoraVM_Data){.kind = ZORAVM_DATA_INT, .val.integer = rtnum};

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Print(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  switch (vm->mem[vm->mp - 1].kind) {
  case ZORAVM_DATA_INT:
    printf("%lld", vm->mem[--vm->mp].val.integer);
    break;
  case ZORAVM_DATA_FLOAT:
    printf("%lf", vm->mem[--vm->mp].val.floating);
    break;
  case ZORAVM_DATA_STRING:
    printf("%s", vm->mem[--vm->mp].val.string);
    break;
  default:
    return ZORAVM_ERROR_UNKNOWN_TYPE;
  }

  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Scan(ZoraVM *vm) {
  if (vm->mp >= vm->memsize) return ZORAVM_ERROR_MEMORY_FULL;

  unsigned int buffsize = (sizeof(char*) * 256 * (vm->size + 1));

  ZoraVM_Data data = {.kind = ZORAVM_DATA_STRING, };
  char *str = malloc(buffsize);
  scanf("%s", str);

  data.val.string = strdup(str);

  vm->mem[vm->mp++] = data;
  vm->ip++;
  free(str);
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_SizeOf(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  ZoraVM_Data data = vm->mem[vm->mp - 1];
  long long int size;

  if (data.kind == ZORAVM_DATA_INT)
    size = sizeof(data.val.integer);
  else if (data.kind == ZORAVM_DATA_FLOAT)
    size = sizeof(data.val.floating);
  else if (data.kind == ZORAVM_DATA_STRING)
    size = sizeof(data.val.string);
  else return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->mem[vm->mp - 1] = (ZoraVM_Data){
    .kind = ZORAVM_DATA_INT,
    .val.integer = size,
  };

  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Env(ZoraVM* vm) {
  if (vm->mp > vm->memsize) return ZORAVM_ERROR_MEMORY_FULL;

  ZoraVM_Data data = vm->mem[vm->mp - 1];

  if (data.kind != ZORAVM_DATA_STRING) return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->mem[vm->mp - 1] = (ZoraVM_Data) {
    .kind = ZORAVM_DATA_STRING,
    .val.string = getenv(data.val.string),
  };

  vm->ip++;
  return ZORAVM_ERROR_OK;
}

// return value from func
ZORAVM_ERROR ZoraVME_Ret(ZoraVM *vm, ZoraVM_Program prog) {

  vm->sp = vm->fp;
  vm->ip = vm->stack[--vm->sp].val.integer;
  vm->fp = vm->stack[--vm->sp].val.integer;
  
  long long int argc = vm->stack[--vm->sp].val.integer;
  vm->sp -= argc;

  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// halt the vm
ZORAVM_ERROR ZoraVME_Halt(ZoraVM *vm, ZoraVM_Program prog) {
  vm->state = 0;
  vm->mem[vm->mp].kind = ZORAVM_DATA_INT;
  vm->mem[vm->mp].val.integer = prog.entry.val.integer;
  vm->mp++;
  vm->ip++;
  return ZORAVM_ERROR_OK;
}

// dump current cpu stack state
ZORAVM_ERROR ZoraVME_Dump_Stack(ZoraVM *vm) {
  vm->ip++;
  printf("\n[CPU]\n");
  printf("\tIP: %ld", vm->ip);
  printf("\tSP: %ld", vm->sp);
  printf("\n[Stack] [%ld]\n", vm->stacksize);
  if (vm->sp < 1) {
    printf("\t<empty>\n");
    return ZORAVM_ERROR_OK;
  }

  int i;
  for (i = 0; i < vm->sp; i++) {
    ZoraVM_Data entry = vm->stack[i];
    switch (entry.kind) {
    case ZORAVM_DATA_INT:
      printf("\t %d: \t %lld \t [%s]\n", i, entry.val.integer, ZoraVM_DataKind[entry.kind]);
      break;
    case ZORAVM_DATA_FLOAT:
      printf("\t %d: \t %lf \t [%s]\n", i, entry.val.floating, ZoraVM_DataKind[entry.kind]);
      break;
    case ZORAVM_DATA_STRING:
      printf("\t %d: \t %s \t [%s]\n", i, entry.val.string, ZoraVM_DataKind[entry.kind]);
      break;
    default:
      return ZORAVM_ERROR_UNKNOWN_TYPE;
    }
  }
  return ZORAVM_ERROR_OK;
}

// dump current cpu mem state
ZORAVM_ERROR ZoraVME_Dump_Mem(ZoraVM *vm) {
  vm->ip++;
  printf("\n[CPU]\n");
  printf("\tIP: %ld", vm->ip);
  printf("\tMP: %ld", vm->mp);
  printf("\n[Memory] [%ld]\n", vm->memsize);
  if (vm->mp < 1) {
    printf("\t<empty>\n");
    return ZORAVM_ERROR_OK;
  }

  int i;
  for (i = 0; i < vm->mp; i++) {
    ZoraVM_Data entry = vm->mem[i];
    switch (entry.kind) {
    case ZORAVM_DATA_INT:
      printf("\t %d: \t %lld \t [%s]\n", i, entry.val.integer, ZoraVM_DataKind[entry.kind]);
      break;
    case ZORAVM_DATA_FLOAT:
      printf("\t %d: \t %lf \t [%s]\n", i, entry.val.floating, ZoraVM_DataKind[entry.kind]);
      break;
    case ZORAVM_DATA_STRING:
      printf("\t %d: \t %s \t [%s]\n", i, entry.val.string, ZoraVM_DataKind[entry.kind]);
      break;
    default:
      return ZORAVM_ERROR_UNKNOWN_TYPE;
    }
  }
  return ZORAVM_ERROR_OK;
}

#endif
