#ifndef RESERVED_H
#define RESERVED_H

#include <stdbool.h>

typedef enum {
  K_NONE,
  K_STORE,
  K_ADD,
  K_SUB,
  K_MUL,
  K_DIV,
  K_MOD,
  K_POW,
  K_PRINT,
  K_SCAN,
  K_HALT,
};

bool isKeyword(char *str);

#endif
