#ifndef _EXEC_C
#define _EXEC_C

#include <math.h>
#include <stdio.h>

#include "./def.c"
#include "./error.c"
#include "./include/vm.h"
#include "./inst.c"
#include "include/error.h"

// push to the memory stack
ERROR VM_Push(VM *vm, Data data) {
  if (vm->mp >= MEM_SIZE)
    return ERROR_MEMORY_FULL;
  switch (data.kind) {
  case DATA_INTEGER:
    vm->mem[vm->mp] = (Data){DATA_INTEGER, .val.integer = data.val.integer};
    break;
  case DATA_FLOATING:
    vm->mem[vm->mp] = (Data){DATA_FLOATING, .val.floating = data.val.floating};
    break;
  case DATA_STRING:
    vm->mem[vm->mp] = (Data){DATA_STRING, .val.string = data.val.string};
    break;
  default:
    return ERROR_UNKNOWN_TYPE;
  }

  vm->mp++;
  vm->ip++;

  return ERROR_OK;
}

// pop from the memory stack
ERROR VM_Pop(VM *vm) {
  if (vm->mp <= 0)
    return ERROR_MEMORY_EMPTY;

  vm->mem[--vm->mp] = (Data){0};
  vm->ip++;

  return ERROR_OK;
}

ERROR VM_Store(VM *vm, Data data) {
  if (vm->sp >= STACK_SIZE)
    return ERROR_STACK_OVERFLOW;
  if (vm->mp < 1)
    return ERROR_MEMORY_EMPTY;

  vm->stack[data.val.integer] = vm->mem[--vm->mp];
  vm->sp++;
  vm->ip++;

  return ERROR_OK;
}

ERROR VM_Load(VM *vm, Data data) {
  if (vm->sp <= 0)
    return ERROR_STACK_UNDERFLOW;
  if (vm->mp >= MEM_SIZE)
    return ERROR_MEMORY_FULL;

  vm->mem[vm->mp++] = vm->stack[data.val.integer];
  vm->sp--;
  vm->ip++;

  return ERROR_OK;
}

// added the two val from mem stack and push it back to the mem stack
ERROR VM_Add(VM *vm) {
  if (vm->mp <= 1)
    return ERROR_MEMORY_EMPTY;
  if (vm->mem[vm->mp - 1].kind != DATA_INTEGER ||
      vm->mem[vm->mp - 2].kind != DATA_INTEGER)
    return ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer += vm->mem[vm->mp - 1].val.integer;
  vm->mem[vm->mp - 2].kind = DATA_INTEGER;
  vm->mem[--vm->mp] = (Data){0};
  vm->ip++;

  return ERROR_OK;
}

// subtract the two val from mem stack and push it back to the mem stack
ERROR VM_Sub(VM *vm) {
  if (vm->mp <= 1)
    return ERROR_MEMORY_EMPTY;
  if (vm->mem[vm->mp - 1].kind != DATA_INTEGER ||
      vm->mem[vm->mp - 2].kind != DATA_INTEGER)
    return ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer -= vm->mem[vm->mp - 1].val.integer;
  vm->mem[vm->mp - 2].kind = DATA_INTEGER;
  vm->mem[--vm->mp] = (Data){0};
  vm->ip++;

  return ERROR_OK;
}

// multiply the two val from mem stack and push it back to the mem stack
ERROR VM_Mul(VM *vm) {
  if (vm->mp <= 1)
    return ERROR_MEMORY_EMPTY;
  if (vm->mem[vm->mp - 1].kind != DATA_INTEGER ||
      vm->mem[vm->mp - 2].kind != DATA_INTEGER)
    return ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer *= vm->mem[vm->mp - 1].val.integer;
  vm->mem[vm->mp - 2].kind = DATA_INTEGER;
  vm->mem[--vm->mp] = (Data){0};
  vm->ip++;

  return ERROR_OK;
}

// divide the two val from mem stack and push it back to the mem stack
ERROR VM_Div(VM *vm) {
  if (vm->mp <= 1)
    return ERROR_MEMORY_EMPTY;
  if (vm->mem[vm->mp - 1].kind != DATA_INTEGER ||
      vm->mem[vm->mp - 2].kind != DATA_INTEGER)
    return ERROR_UNIMPLEMENTED;

  if (vm->mem[vm->mp - 1].val.integer == 0)
    return ERROR_DIV_BY_0;

  vm->mem[vm->mp - 2].val.integer /= vm->mem[vm->mp - 1].val.integer;
  vm->mem[vm->mp - 2].kind = DATA_INTEGER;
  vm->mem[--vm->mp] = (Data){0};
  vm->ip++;

  return ERROR_OK;
}

// mod the two val from mem stack and push it back to the mem stack
ERROR VM_Mod(VM *vm) {
  if (vm->mp <= 1)
    return ERROR_MEMORY_EMPTY;
  if (vm->mem[vm->mp - 1].kind != DATA_INTEGER ||
      vm->mem[vm->mp - 2].kind != DATA_INTEGER)
    return ERROR_UNIMPLEMENTED;
  if (vm->mem[vm->mp - 1].val.integer == 0)
    return ERROR_DIV_BY_0;

  vm->mem[vm->mp - 2].val.integer %= vm->stack[vm->sp - 1].val.integer;
  vm->mem[vm->mp--] = (Data){0};
  vm->ip++;

  return ERROR_OK;
}

ERROR VM_Inc(VM *vm) {
  if (vm->mp < 1)
    return ERROR_MEMORY_EMPTY;
  if (vm->mem[vm->mp - 1].kind != DATA_INTEGER)
    return ERROR_UNIMPLEMENTED;

  ++vm->mem[vm->mp - 1].val.integer;
  vm->ip++;

  return ERROR_OK;
}

ERROR VM_Dec(VM *vm) {
  if (vm->mp < 1)
    return ERROR_MEMORY_EMPTY;
  if (vm->mem[vm->mp - 1].kind != DATA_INTEGER)
    return ERROR_UNIMPLEMENTED;

  --vm->mem[vm->mp - 1].val.integer;
  vm->ip++;

  return ERROR_OK;
}

ERROR VM_Pow(VM *vm) {
  if (vm->mp <= 1)
    return ERROR_MEMORY_EMPTY;
  if (vm->mem[vm->mp - 1].kind != DATA_INTEGER || vm->mem[vm->mp - 2].kind != DATA_INTEGER)
    return ERROR_UNIMPLEMENTED;

  vm->mem[vm->mp - 2].val.integer =
      pow(vm->mem[vm->mp - 2].val.integer, vm->mem[vm->mp - 1].val.integer);
  vm->mem[--vm->mp] = (Data){0};
  vm->ip++;

  return ERROR_OK;
}

ERROR VM_Print(VM *vm, Program prog) {
  if (vm->mp < 1)
    return ERROR_MEMORY_EMPTY;

  Data entry = prog.entry;
  switch (entry.kind) {
  case DATA_INTEGER:
    printf("%lld", vm->mem[--vm->mp].val.integer);
    break;
  case DATA_FLOATING:
    printf("%lf", vm->mem[--vm->mp].val.floating);
    break;
  case DATA_STRING:
    printf("%s", vm->mem[--vm->mp].val.string);
    break;
  default:
    return ERROR_UNKNOWN_TYPE;
  }
  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Scan(VM *vm, Program prog) {
  if (vm->mp >= MEM_SIZE)
    return ERROR_MEMORY_FULL;

  Data entry = prog.entry;
  switch (entry.kind) {
  case DATA_INTEGER:
    scanf("%lld", &vm->mem[vm->mp++].val.integer);
    break;
  case DATA_FLOATING:
    scanf("%lf", &vm->mem[vm->mp++].val.floating);
    break;
  case DATA_STRING:
    scanf("%s", vm->mem[vm->mp++].val.string);
    break;
  default:
    return ERROR_UNKNOWN_TYPE;
  }
  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Jmpz(VM *vm, Program prog) {
  return ERROR_UNIMPLEMENTED;
  //   return ERROR_OK;
}

ERROR VM_Jmpnz(VM *vm, Program prog) {
  return ERROR_UNIMPLEMENTED;
  //   return ERROR_OK;
}

ERROR VM_Jmp(VM *vm, Program prog) {
  return ERROR_UNIMPLEMENTED;
  //   return ERROR_OK;
}

ERROR VM_Ret(VM *vm, Program prog) {
  vm->mem[vm->mp].kind = DATA_INTEGER;
  vm->mem[vm->mp].val.integer = prog.entry.val.integer;
  vm->mp++;
  vm->ip++;
  return ERROR_OK;
}

// halt the vm
ERROR VM_Halt(VM *vm, Program prog) {
  vm->state = 0;
  vm->mem[vm->mp].kind = DATA_INTEGER;
  vm->mem[vm->mp].val.integer = prog.entry.val.integer;
  vm->mp++;
  vm->ip++;
  return ERROR_OK;
}

ERROR VM_Dump_Stack(VM *vm) {
  vm->ip++;
  printf("\n[CPU]\n");
  printf("\tIP: %d", vm->ip);
  printf("\tSP: %d", vm->sp);
  printf("\n[Stack]\n");
  if (vm->sp < 1) {
    printf("\t<empty>\n");
    return ERROR_OK;
  }
  for (int i = 0; i < vm->sp; i++) {
    Data entry = vm->stack[i];
    switch (entry.kind) {
    case DATA_INTEGER:
      printf("\t %d: \t %lld \t [%s]\n", i, entry.val.integer,
             DATAKIND_as_str(entry.kind));
      break;
    case DATA_FLOATING:
      printf("\t %d: \t %lf \t [%s]\n", i, entry.val.floating,
             DATAKIND_as_str(entry.kind));
      break;
    case DATA_STRING:
      printf("\t %d: \t %s \t [%s]\n", i, entry.val.string,
             DATAKIND_as_str(entry.kind));
      break;
    default:
      return ERROR_UNKNOWN_TYPE;
    }
  }
  return ERROR_OK;
}

ERROR VM_Dump_Mem(VM *vm) {
  vm->ip++;
  printf("\n[CPU]\n");
  printf("\tIP: %d", vm->ip);
  printf("\tMP: %d", vm->mp);
  printf("\n[Memory]\n");
  if (vm->mp < 1) {
    printf("\t<empty>\n");
    return ERROR_OK;
  }
  for (int i = 0; i < vm->mp; i++) {
    Data entry = vm->mem[i];
    switch (entry.kind) {
    case DATA_INTEGER:
      printf("\t %d: \t %lld \t [%s]\n", i, entry.val.integer,
             DATAKIND_as_str(entry.kind));
      break;
    case DATA_FLOATING:
      printf("\t %d: \t %lf \t [%s]\n", i, entry.val.floating,
             DATAKIND_as_str(entry.kind));
      break;
    case DATA_STRING:
      printf("\t %d: \t %s \t [%s]\n", i, entry.val.string,
             DATAKIND_as_str(entry.kind));
      break;
    default:
      return ERROR_UNKNOWN_TYPE;
    }
  }
  return ERROR_OK;
}

#endif
