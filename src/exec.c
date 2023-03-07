#ifndef _ZORAVM_EXEC_C
#define _ZORAVM_EXEC_C

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "./zoravm.h"
#include "./inst.c"
#include "./trap.c"

// push to the memory stack
ZORAVM_ERROR ZoraVME_Push(ZoraVM *vm, ZoraVM_Data data) {
  if (vm->mp >= vm->size)
    return ZORAVM_ERROR_MEMORY_FULL;
  switch (data.kind) {
  case ZORAVM_DATA_INTEGER:
    vm->mem[vm->mp] = (ZoraVM_Data){ZORAVM_DATA_INTEGER, .val.integer = data.val.integer};
    break;
  case ZORAVM_DATA_FLOATING:
    vm->mem[vm->mp] = (ZoraVM_Data){ZORAVM_DATA_FLOATING, .val.floating = data.val.floating};
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
  if (vm->mp < 1)
    return ZORAVM_ERROR_MEMORY_EMPTY;

  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// store to the stack from mem
ZORAVM_ERROR ZoraVME_Store(ZoraVM *vm, ZoraVM_Data data) {
  if (vm->sp >= vm->size)
    return ZORAVM_ERROR_STACK_OVERFLOW;
  if (vm->mp < 1)
    return ZORAVM_ERROR_MEMORY_EMPTY;

  vm->stack[data.val.integer] = vm->mem[--vm->mp];
  vm->sp++;
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// load from stack to the mem
ZORAVM_ERROR ZoraVME_Load(ZoraVM *vm, ZoraVM_Data data) {
  if (vm->sp < 1)
    return ZORAVM_ERROR_STACK_UNDERFLOW;
  if (vm->mp >= vm->size)
    return ZORAVM_ERROR_MEMORY_FULL;

  vm->mem[vm->mp++] = vm->stack[data.val.integer];
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// duplicate memory values
ZORAVM_ERROR ZoraVME_Dup(ZoraVM *vm) {
  if (vm->mp >= vm->size)
    return ZORAVM_ERROR_MEMORY_FULL;
  if (vm->mp < 1)
    return ZORAVM_ERROR_MEMORY_EMPTY;

  vm->mem[vm->mp] = vm->mem[vm->mp - 1];
  vm->mp++;
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// swap memory values
ZORAVM_ERROR ZoraVME_Swap(ZoraVM *vm) {
  if (vm->mp >= vm->size)
    return ZORAVM_ERROR_MEMORY_FULL;
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data tmp = vm->mem[vm->mp - 2];
  vm->mem[vm->mp - 2] = vm->mem[vm->mp - 1];
  vm->mem[vm->mp - 1] = tmp;
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// add the two val from mem stack and push it back to the mem stack
ZORAVM_ERROR ZoraVME_Add(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind != two.kind)
    return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER) {
    vm->mem[vm->mp - 2].val.integer += two.val.integer;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  } else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING) {
    char *tmp = strcat(strcpy(tmp, one.val.string), two.val.string);
    vm->mem[vm->mp - 2].val.string = tmp;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_STRING;
  } else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING) {
    vm->mem[vm->mp - 2].val.floating += two.val.floating;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_FLOATING;
  } else
    return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

// subtract the two val from mem stack and push it back to the mem stack
ZORAVM_ERROR ZoraVME_Sub(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind != two.kind)
    return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER) {
    vm->mem[vm->mp - 2].val.integer -= two.val.integer;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  } else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING) {
    vm->mem[vm->mp - 2].val.floating -= two.val.floating;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_FLOATING;
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
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind != two.kind)
    return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER) {
    vm->mem[vm->mp - 2].val.integer *= two.val.integer;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  } else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING) {
    vm->mem[vm->mp - 2].val.floating *= two.val.floating;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_FLOATING;
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
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind != two.kind)
    return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER) {
    vm->mem[vm->mp - 2].val.integer /= two.val.integer;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  } else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING) {
    vm->mem[vm->mp - 2].val.floating /= two.val.floating;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_FLOATING;
  } else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    return ZORAVM_ERROR_ILLEGAL_INST;
  else
    return ZORAVM_ERROR_UNKNOWN_TYPE;

  return ZORAVM_ERROR_OK;
}

// mod the two val from mem stack and push it back to the mem stack
ZORAVM_ERROR ZoraVME_Mod(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind != two.kind)
    return ZORAVM_ERROR_ILLEGAL_INST_TYPE;

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER) {
    vm->mem[vm->mp - 2].val.integer %= two.val.integer;
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  } else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING)
    return ZORAVM_ERROR_ILLEGAL_INST;
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    return ZORAVM_ERROR_ILLEGAL_INST;
  else
    return ZORAVM_ERROR_UNKNOWN_TYPE;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Inc(ZoraVM *vm) {
  if (vm->mp < 1)
    return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_INTEGER)
    ++vm->mem[vm->mp - 1].val.integer;
  else if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_FLOATING)
    ++vm->mem[vm->mp - 1].val.floating;
  else if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_STRING)
    return ZORAVM_ERROR_ILLEGAL_INST;
  else
    return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Dec(ZoraVM *vm) {
  if (vm->mp < 1)
    return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_INTEGER)
    --vm->mem[vm->mp - 1].val.integer;
  else if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_FLOATING)
    --vm->mem[vm->mp - 1].val.floating;
  else if (vm->mem[vm->mp - 1].kind == ZORAVM_DATA_STRING)
    return ZORAVM_ERROR_ILLEGAL_INST;
  else
    return ZORAVM_ERROR_UNKNOWN_TYPE;
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Pow(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (two.kind != ZORAVM_DATA_INTEGER)
    return ZORAVM_ERROR_ILLEGAL_INST;

  if (one.kind == ZORAVM_DATA_INTEGER) {
    vm->mem[vm->mp - 2].val.integer = pow(one.val.integer, two.val.integer);
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  } else if (one.kind == ZORAVM_DATA_FLOATING) {
    vm->mem[vm->mp - 2].val.floating = pow(one.val.floating, two.val.floating);
    vm->mem[vm->mp - 2].kind = ZORAVM_DATA_FLOATING;
  } else if (one.kind == ZORAVM_DATA_STRING)
    return ZORAVM_ERROR_UNIMPLEMENTED;
  else
    return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_And(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;
  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INTEGER ||
      vm->mem[vm->mp - 2].kind != ZORAVM_DATA_INTEGER)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer &= vm->mem[vm->mp - 1].val.integer;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Or(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;
  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INTEGER ||
      vm->mem[vm->mp - 2].kind != ZORAVM_DATA_INTEGER)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer |= vm->mem[vm->mp - 1].val.integer;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Xor(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;
  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INTEGER ||
      vm->mem[vm->mp - 2].kind != ZORAVM_DATA_INTEGER)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer ^= vm->mem[vm->mp - 1].val.integer;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Not(ZoraVM *vm) {
  if (vm->mp < 1)
    return ZORAVM_ERROR_MEMORY_EMPTY;
  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INTEGER)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 1].val.integer = ~vm->mem[vm->mp - 1].val.integer;
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Shl(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;
  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INTEGER ||
      vm->mem[vm->mp - 2].kind != ZORAVM_DATA_INTEGER)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer <<= vm->mem[vm->mp - 1].val.integer;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Shr(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;
  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INTEGER ||
      vm->mem[vm->mp - 2].kind != ZORAVM_DATA_INTEGER)
    return ZORAVM_ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer >>= vm->mem[vm->mp - 1].val.integer;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpEq(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER)
    vm->mem[vm->mp - 2].val.integer = (int)one.val.integer == (int)two.val.integer;
  else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING)
    vm->mem[vm->mp - 2].val.integer = one.val.floating == two.val.floating;
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer =
        strcmp(one.val.string, two.val.string) == 0;
  else
    vm->mem[vm->mp - 2].val.integer = 0;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpNotEq(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER)
    vm->mem[vm->mp - 2].val.integer = (int)!((int)one.val.integer == (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING)
    vm->mem[vm->mp - 2].val.integer = !(one.val.floating == two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer =
        !(strcmp(one.val.string, two.val.string) == 0);
  else
    vm->mem[vm->mp - 2].val.integer = 1;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpGt(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER)
    vm->mem[vm->mp - 2].val.integer = (int)one.val.integer > (int)two.val.integer;
  else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING)
    vm->mem[vm->mp - 2].val.integer = one.val.floating > two.val.floating;
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = (strcmp(one.val.string, two.val.string) == 1);
  else
    vm->mem[vm->mp - 2].val.integer = 0;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpNotGt(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER)
    vm->mem[vm->mp - 2].val.integer = (int)!((int)one.val.integer > (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING)
    vm->mem[vm->mp - 2].val.integer = !(one.val.floating > two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = !(strcmp(one.val.string, two.val.string) == 1);
  else
    vm->mem[vm->mp - 2].val.integer = 1;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;


  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpLt(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER)
    vm->mem[vm->mp - 2].val.integer = (int)one.val.integer < (int)two.val.integer;
  else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING)
    vm->mem[vm->mp - 2].val.integer = one.val.floating < two.val.floating;
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = (strcmp(one.val.string, two.val.string) == -1);
  else
    vm->mem[vm->mp - 2].val.integer = 0;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpNotLt(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER)
    vm->mem[vm->mp - 2].val.integer = (int)!((int)one.val.integer < (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING)
    vm->mem[vm->mp - 2].val.integer = !(one.val.floating < two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = !(strcmp(one.val.string, two.val.string) == -1);
  else
    vm->mem[vm->mp - 2].val.integer = 1;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpGte(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER)
    vm->mem[vm->mp - 2].val.integer = (int)((int)one.val.integer > (int)two.val.integer || (int)one.val.integer == (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING)
    vm->mem[vm->mp - 2].val.integer = (one.val.floating > two.val.floating || one.val.floating == two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = (strcmp(one.val.string, two.val.string) == 1 || strcmp(one.val.string, two.val.string) == 0);
  else
    vm->mem[vm->mp - 2].val.integer = 0;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpNotGte(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER)
    vm->mem[vm->mp - 2].val.integer = (int)!((int)one.val.integer > (int)two.val.integer || (int)one.val.integer == (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING)
    vm->mem[vm->mp - 2].val.integer = !(one.val.floating > two.val.floating || one.val.floating == two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = !(strcmp(one.val.string, two.val.string) == 1 || strcmp(one.val.string, two.val.string) == 0);
  else
    vm->mem[vm->mp - 2].val.integer = 1;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpLte(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER)
    vm->mem[vm->mp - 2].val.integer = (int)one.val.integer < (int)two.val.integer || (int)one.val.integer == (int)two.val.integer;
  else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING)
    vm->mem[vm->mp - 2].val.integer = (one.val.floating < two.val.floating || one.val.floating == two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = (strcmp(one.val.string, two.val.string) == -1 || strcmp(one.val.string, two.val.string) == 0);
  else
    vm->mem[vm->mp - 2].val.integer = 0;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_CmpNotLte(ZoraVM *vm) {
  if (vm->mp < 2)
    return ZORAVM_ERROR_NOT_ENOUGH_OPERANDS;

  ZoraVM_Data one = vm->mem[vm->mp - 2], two = vm->mem[vm->mp - 1];

  if (one.kind == ZORAVM_DATA_INTEGER && two.kind == ZORAVM_DATA_INTEGER)
    vm->mem[vm->mp - 2].val.integer = (int)!((int)one.val.integer < (int)two.val.integer || (int)one.val.integer == (int)two.val.integer);
  else if (one.kind == ZORAVM_DATA_FLOATING && two.kind == ZORAVM_DATA_FLOATING)
    vm->mem[vm->mp - 2].val.integer = !(one.val.floating < two.val.floating || one.val.floating == two.val.floating);
  else if (one.kind == ZORAVM_DATA_STRING && two.kind == ZORAVM_DATA_STRING)
    vm->mem[vm->mp - 2].val.integer = !(strcmp(one.val.string, two.val.string) == -1 || strcmp(one.val.string, two.val.string) == 0);
  else
    vm->mem[vm->mp - 2].val.integer = 1;

  vm->mem[vm->mp - 2].kind = ZORAVM_DATA_INTEGER;
  vm->mem[--vm->mp] = (ZoraVM_Data){0};
  vm->ip++;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Jmp(ZoraVM *vm, ZoraVM_Program prog) {
  /* vm->ip = prog.entry.val.integer; */
  return ZORAVM_ERROR_UNIMPLEMENTED;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_JmpIf(ZoraVM *vm, ZoraVM_Program prog) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INTEGER) return ZORAVM_ERROR_ILLEGAL_INST;

  if (vm->mem[vm->mp - 1].val.integer == 0) vm->ip++;
  else vm->ip = prog.entry.val.integer;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_JmpIfNot(ZoraVM *vm, ZoraVM_Program prog) {
  if (vm->mp < 1)
    return ZORAVM_ERROR_MEMORY_EMPTY;

  if (vm->mem[vm->mp - 1].kind != ZORAVM_DATA_INTEGER)
    return ZORAVM_ERROR_ILLEGAL_INST;

  if (vm->mem[vm->mp - 1].val.integer != 0) vm->ip++;
  else vm->ip = prog.entry.val.integer;

  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Ret(ZoraVM *vm, ZoraVM_Program prog) {
  vm->mem[vm->mp].kind = ZORAVM_DATA_INTEGER;
  vm->mem[vm->mp].val.integer = prog.entry.val.integer;
  vm->mp++;
  vm->ip++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_Print(ZoraVM *vm) {
  if (vm->mp < 1)
    return ZORAVM_ERROR_MEMORY_EMPTY;

  switch (vm->mem[vm->mp - 1].kind) {
  case ZORAVM_DATA_INTEGER:
    printf("%lld", vm->mem[--vm->mp].val.integer);
    break;
  case ZORAVM_DATA_FLOATING:
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
  if (vm->mp >= vm->size) return ZORAVM_ERROR_MEMORY_FULL;

  scanf("%s", vm->mem[vm->mp].val.string);
  /* vm->mem[vm->mp].kind = ZORAVM_DATA_STRING; */

  vm->ip++;
  vm->mp++;
  return ZORAVM_ERROR_OK;
}

ZORAVM_ERROR ZoraVME_SizeOf(ZoraVM *vm) {
  if (vm->mp < 1) return ZORAVM_ERROR_MEMORY_EMPTY;

  ZoraVM_Data data = vm->mem[vm->mp - 1];
  long long int size;

  if (data.kind == ZORAVM_DATA_INTEGER)
    size = sizeof(data.val.integer);
  else if (data.kind == ZORAVM_DATA_FLOATING)
    size = sizeof(data.val.floating);
  else if (data.kind == ZORAVM_DATA_STRING)
    size = sizeof(data.val.string);
  else return ZORAVM_ERROR_UNKNOWN_TYPE;

  vm->mem[vm->mp - 1] = (ZoraVM_Data){
    .kind = ZORAVM_DATA_INTEGER,
    .val.integer = size,
  };

  vm->ip++;
  return ZORAVM_ERROR_OK;
}

// halt the vm
ZORAVM_ERROR ZoraVME_Halt(ZoraVM *vm, ZoraVM_Program prog) {
  vm->state = 0;
  vm->mem[vm->mp].kind = ZORAVM_DATA_INTEGER;
  vm->mem[vm->mp].val.integer = prog.entry.val.integer;
  vm->mp++;
  vm->ip++;
  return ZORAVM_ERROR_OK;
}

// dump current cpu stack state
ZORAVM_ERROR ZoraVME_Dump_Stack(ZoraVM *vm) {
  vm->ip++;
  #if ZORAVM_LOG
  printf("\n[CPU]\n");
  printf("\tIP: %d", vm->ip);
  printf("\tSP: %d", vm->sp);
  printf("\n[Stack]\n");
  if (vm->sp < 1) {
    printf("\t<empty>\n");
    return ZORAVM_ERROR_OK;
  }
  for (int i = 0; i < vm->sp; i++) {
    ZoraVM_Data entry = vm->stack[i];
    switch (entry.kind) {
    case ZORAVM_DATA_INTEGER:
      printf("\t %d: \t %lld \t [%s]\n", i, entry.val.integer,
             ZoraVM_KindAsStr(entry.kind));
      break;
    case ZORAVM_DATA_FLOATING:
      printf("\t %d: \t %lf \t [%s]\n", i, entry.val.floating,
             ZoraVM_KindAsStr(entry.kind));
      break;
    case ZORAVM_DATA_STRING:
      printf("\t %d: \t %s \t [%s]\n", i, entry.val.string,
             ZoraVM_KindAsStr(entry.kind));
      break;
    default:
      return ZORAVM_ERROR_UNKNOWN_TYPE;
    }
  }
  #endif
  return ZORAVM_ERROR_OK;
}

// dump current cpu mem state
ZORAVM_ERROR ZoraVME_Dump_Mem(ZoraVM *vm) {
  vm->ip++;
  #if ZORAVM_LOG
  printf("\n[CPU]\n");
  printf("\tIP: %d", vm->ip);
  printf("\tMP: %d", vm->mp);
  printf("\n[Memory]\n");
  if (vm->mp < 1) {
    printf("\t<empty>\n");
    return ZORAVM_ERROR_OK;
  }
  for (int i = 0; i < vm->mp; i++) {
    ZoraVM_Data entry = vm->mem[i];
    switch (entry.kind) {
    case ZORAVM_DATA_INTEGER:
      printf("\t %d: \t %lld \t [%s]\n", i, entry.val.integer,
             ZoraVM_KindAsStr(entry.kind));
      break;
    case ZORAVM_DATA_FLOATING:
      printf("\t %d: \t %lf \t [%s]\n", i, entry.val.floating,
             ZoraVM_KindAsStr(entry.kind));
      break;
    case ZORAVM_DATA_STRING:
      printf("\t %d: \t %s \t [%s]\n", i, entry.val.string,
             ZoraVM_KindAsStr(entry.kind));
      break;
    default:
      return ZORAVM_ERROR_UNKNOWN_TYPE;
    }
  }
  #endif
  return ZORAVM_ERROR_OK;
}

#endif
