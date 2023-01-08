#ifndef LEXER_C
#define LEXER_C

#include "./lexer.h"

lexer_struct init_lexer(file_t file) {
  lexer_struct *lexer = (lexer_struct *)malloc(sizeof(lexer_struct));

  lexer->file = &file;
  lexer->pos = 0;
  lexer->col = lexer->pos;
  lexer->line = 1;
  lexer->cur = lexer->file->src[lexer->pos];

  return *lexer;
}

void lexer_advance(lexer_struct *lexer) {
  if (lexer->cur != '\0') {

    if (lexer->cur == '\n') {
      lexer->line++;
      lexer->col = 0;
    }

    lexer->col++;
    lexer->pos++;
    lexer->cur = lexer->file->src[lexer->pos];
  }
}

char lexer_peek(lexer_struct *lexer, int offset) {
  if (lexer->pos + offset < lexer->file->size)
    return lexer->file->src[lexer->pos + offset];

  return '\0';
}

void n_lexer_advance(lexer_struct *lexer, unsigned int n) {
  unsigned int i;
  for (i = 0; i < n; i++)
    lexer_advance(lexer);
}

void lexer_skip_ws(lexer_struct *lexer) {
  while (lexer->cur == ' ' || lexer->cur == '\n' || lexer->cur == '\r' ||
         lexer->cur == '\t')
    lexer_advance(lexer);
}

void lexer_skip_comment(lexer_struct *lexer) {

  if (lexer->cur == ';') {
    n_lexer_advance(lexer, 2);
    while (lexer->cur != '\0' && lexer->cur != '\n')
      lexer_advance(lexer);
  }
}

#endif