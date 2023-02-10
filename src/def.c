#ifndef DEF_C
#define DEF_C

#include <stdlib.h>
#include <string.h>

#include "./include/vm.h"

char *DATAKIND_as_str(enum DATA_KIND kind) {
  switch (kind) {
  case DATA_INTEGER:
    return "INTEGER";
  case DATA_STRING:
    return "STRING";
  case DATA_FLOATING:
    return "FLOATING";
  default:
    return "UNKNOWN";
  }
}

int is_num(char ch) { return ch >= '0' && ch <= '9'; }

int is_str_int(char *str) {
  for (int c = 0; c < strlen(str); c++)
    if (!is_num(str[c]))
      return 0;
  return 1;
}

int parseInt(char *str) {
  if (is_str_int(str))
    return atoi(str);
  return 0;
}

#endif
