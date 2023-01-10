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
}

#endif