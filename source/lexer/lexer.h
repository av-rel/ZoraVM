#ifndef LEXER_STRUCT
#define LEXER_STRUCT

#include <stdlib.h>
#include <string.h>

typedef struct {
  char *name;
  char *src;
  unsigned int size;
} file_t;

typedef struct {
  file_t *file;
  char cur;
  unsigned int pos;
  unsigned int col;
  unsigned int line;
} lexer_struct;

#endif