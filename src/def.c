#ifndef DEF_C
#define DEF_C

#include <stdlib.h>
#include <string.h>

#include "./include/vm.h"

int is_num(char ch) { return ch >= '0' && ch <= '9'; }

int is_str_int(char *str) {
  for (int c = 0; c < strlen(str); c++)
    if (!is_num(str[c]))
      return 0;
  return 1;
}

int is_str_float(char *str) {
  int neg = 0, dot = 0, c = 0;

  if (str[0] == '-') {
    c = ++neg;
    if (strlen(str) <= 1)
      return 0;
  };

  for (; c < strlen(str); c++) {
    if (str[c] == '.') {
      if (dot == 0)
        dot++;
      else
        return 0;
    } else if (!is_num(str[c]))
      return 0;
  }

  return 1;
}

int parseInt(char *str) {
  if (is_str_int(str))
    return atoi(str);
  return 0;
}

float parseFloat(char *str) {
  if (is_str_float(str))
    return atof(str);
  return 0;
}

#endif