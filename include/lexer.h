#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "./token.h"

typedef struct {
  char *name;
  char *src;
  unsigned int size;
} file_t;

typedef struct {
  file_t *file;
  token_struct* tokens;
  char cur;
  unsigned int pos;
  unsigned int col;
  unsigned int line;
} lexer_struct;


bool is_whitespace(char ch);
bool is_digit(char ch);
bool is_alpha(char ch);

#endif
