#ifndef RESERVED_H
#define RESERVED_H

#include <stdbool.h>

typedef enum {
  K_NONE,
  K_PUSH,
  K_POP,
  K_MOVE,
  K_ADD,
  K_SUB,
  K_MUL,
  K_DIV,
  K_MOD,
  K_PRINT,
  K_SCAN,
  K_HALT,
} K_KEYWORD;

bool isKeyword(char *str);

#endif