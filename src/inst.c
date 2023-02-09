#ifndef OP_C
#define OP_C

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "./include/inst.h"

const char *keywords[] = {"store", "load",  "print", "scan",  "halt", "ret",
                          "add ",  " sub ", " mul ", " div ", "mod",  "jmp",
                          "cmp",   "ncmp",  "jz",    "jnz",   "je",   "jne",
                          "jg",    "jge",   "jl",    "jle"};

const size_t keyword_size = sizeof(keywords)/sizeof(keywords[0]);

bool isKeyword(char *c) {
  for (int i = 0; i < keyword_size; i++)
    if (strcmp(c, keywords[i]) == 0)
      return true;
  return false;
};

#endif
