#ifndef LEXER_C
#define LEXER_C

#include "../include/lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

lexer_struct *init_lexer(file_t *file) {
  lexer_struct *lexer = (lexer_struct *)malloc(sizeof(lexer_struct));

  lexer->tokens = (token_struct*) malloc(sizeof(token_struct));
  lexer->file = file;
  lexer->pos = 0;
  lexer->col = lexer->pos+1;
  lexer->line = 1;
  lexer->cur = file->src[lexer->pos];

  return lexer;
}

void lexer_advance(lexer_struct *lexer) {
  if (!lexer->cur) return;

  if (lexer->cur == '\n') {
    lexer->line++;
    lexer->col = 1;
  }

  lexer->pos++;
  lexer->col++;
  lexer->cur = lexer->file->src[lexer->pos];
}

char lexer_peek(lexer_struct *lexer, int offset) {
  if (lexer->pos + offset < lexer->file->size) return lexer->file->src[lexer->pos + offset];
  return '\0';
}

void lexer_n_advance(lexer_struct *lexer, unsigned int n) {
  for (unsigned int i = 0; i < n; i++) lexer_advance(lexer);
}

void lexer_skip_ws(lexer_struct *lexer) {
  while (is_whitespace(lexer->cur)) lexer_advance(lexer);
}

void lexer_skip_comment(lexer_struct *lexer) {
  if (lexer->cur == ';') {
    lexer_advance(lexer);
    while (lexer->cur != '\0' && lexer->cur != '\n') lexer_advance(lexer);
  }
}

bool is_identifier(char ch){
  return is_alpha(ch) || ch == '_';
}

bool is_whitespace(char ch){
  return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}

bool is_alpha(char ch){
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool is_digit(char ch){
  return ch >= '0' && ch <= '9';
}

bool is_hex(char ch){
  return (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F') || is_digit(ch);
}

bool is_bin(char ch){
  return (ch == '0' || ch == '1');
}

bool is_escape(char ch){
  return (ch == '\r' || ch == '\t' || ch == '\n' || ch == '\\' || ch == '\"' || ch == '\'');
}

#endif
