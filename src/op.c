#ifndef OP_C
#define OP_C

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "./include/macro.h"
#include "./include/op.h"

const char *keywords[] = {"store", "load", "print", "scan", "halt", "ret",
                          "call",  "goto", "add",   "sub",  "mul",  "div",
                          "mod",   "jmp",  "cmp",   "ncmp", "jz",   "jnz",
                          "je",    "jne",  "jg",    "jge",  "jl",   "jle"};

const size_t keyword_size = ARRAY_SIZE(keywords);

bool isKeyword(char *c) {
  for (int i = 0; i < keyword_size; i++)
    if (strcmp(c, keywords[i]) == 0)
      return true;
  return false;
};

#endif
