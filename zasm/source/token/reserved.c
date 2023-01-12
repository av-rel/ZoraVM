#ifndef RESERVED_C
#define RESERVED_C

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "./token.h"

bool isNumber(char c) {
  return (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' ||
          c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
             ? true
             : false;
}

const char *keywords[] = {"push", "pop", "move", "swap",  "add",  "sub", "mul",
                          "div",  "mod", "pow",  "print", "scan", "halt"};
const size_t keyword_size = sizeof(keywords) / sizeof(char *);

bool isKeyword(char *c) {
  int i;
  for (i = 0; i < keyword_size; i++) {
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
  else if (strcmp(c, "move"))
    return K_MOVE;
  else if (strcmp(c, "swap"))
    return K_SWAP;
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
  else if (strcmp(c, "pow") == 0)
    return K_POW;
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