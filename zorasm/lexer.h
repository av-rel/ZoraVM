#ifndef ZORASM_LEXER_H
#define ZORASM_LEXER_H

#include "../inc/sys.h"
#include "./token.h"

typedef struct {
  Zora_file_t *file;
  char cur;
  unsigned int pos;
  unsigned int col;
  unsigned int line;
  unsigned int ntok;
  Zorasm_token_t *tokens;
} Zorasm_lexer_t;

Zorasm_lexer_t init_lexer(Zora_file_t *file);
char Zorasm_lexer_advance(Zorasm_lexer_t *lexer);
void Zorasm_lexer_degrade(Zorasm_lexer_t *lexer);
void Zorasm_lexer_n_advance(Zorasm_lexer_t *lexer, unsigned int n);
char Zorasm_lexer_peek(Zorasm_lexer_t *lexer, int offset);
void Zorasm_lexer_skip_line(Zorasm_lexer_t *lexer);
void Zorasm_lexer_skip_ws(Zorasm_lexer_t *lexer);

#endif
