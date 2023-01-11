#ifndef RESERVED_C
#define RESERVED_C

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "../include/reserved.h"

const char *keywords[] = {"push", "pop", "add",   "sub", "mul",
                          "div",  "mod", "print", "halt"};
const size_t keyword_size = 9;

bool isKeyword(char *c) {
  for (int i = 0; i < keyword_size; i++) {
    if (strcmp(c, keywords[i]) == 0) {
      return true;
    }
  }
  return false;
};
K_KEYWORD getKeyword(char *c) {
  if (strcmp(c, "push") == 0)
    return K_PUSH;
  else if (strcmp(c, "pop") == 0)
    return K_POP;
  else if (strcmp(c, "add") == 0)
    return K_ADD;
  else if (strcmp(c, "sub") == 0)
    return K_SUB;
  else if (strcmp(c, "mul") == 0)
    return K_MUL;
  else if (strcmp(c, "div") == 0)
    return K_DIV;
  else if (strcmp(c, "mod") == 0)
    return K_MOD;
  else if (strcmp(c, "print") == 0)
    return K_PRINT;
  else if (strcmp(c, "scan") == 0)
    return K_SCAN;
  else if (strcmp(c, "halt") == 0)
    return K_HALT;
  else
    return '\0';
}

#endif