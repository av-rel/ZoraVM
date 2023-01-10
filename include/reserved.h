#ifndef RESERVED_H
#define RESERVED_H

#include <stdbool.h>

typedef enum {
  K_PUSH,
  K_PULL,
  K_MOVE,
  K_ADD,
  K_SUB,
  K_MUL,
  K_DIV,
  K_MOD,
  K_PRINT,
  K_HALT,
} K_KEYWORD;

bool isKeyword(char *str);

#endif