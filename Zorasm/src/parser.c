#ifndef ZORASM_PARSER_C
#define ZORASM_PARSER_C

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lexer.h"
#include "./kw.c"
#include "./token.h"

int Zorasm_parser_expect(Zorasm_lexer_t *lexer, Zorasm_token_t token, Zorasm_TokenKind expect, Zorasm_TokenKind got);
int Zorasm_parser_expect_many(Zorasm_lexer_t *lexer, Zorasm_token_t token, Zorasm_TokenKind expect[], int expected_len , Zorasm_TokenKind got);


int Zorasm_parser_expect(Zorasm_lexer_t *lexer, Zorasm_token_t token, Zorasm_TokenKind expect, Zorasm_TokenKind got) {
    if (expect == got) return 0;
    if (expect == ZORASM_TK_KIND && (got == ZORASM_TK_STRING || got == ZORASM_TK_INT || got == ZORASM_TK_FLOAT)) return 0;
#if ZORASM_LOG
    printf("\n%s:%d:%d: Expected `%s` but got `%s`\n\n", lexer->file->argfile, token.pos.start.line, token.pos.start.col, Zorasm_token_as_str(expect), Zorasm_token_as_str(got));
    Zorasm_log_error_line(lexer->file->src, token.pos.start.line);
#endif

    return -1;
}

int Zorasm_parser_expect_many(Zorasm_lexer_t *lexer, Zorasm_token_t token, Zorasm_TokenKind expect[], int expected_len , Zorasm_TokenKind got) {
    int c;
    for (c = 0; c < expected_len; c++){
        if (expect[c] == got) return 0;
        if (expect[c] == ZORASM_TK_KIND && (got == ZORASM_TK_STRING || got == ZORASM_TK_INT || got == ZORASM_TK_FLOAT)) return 0;
    }

#if ZORASM_LOG
    printf("\n%s:%d:%d: Expected ", lexer->file->argfile, token.pos.start.line, token.pos.start.col);
    for (c = 0; c < expected_len; c++) {
      printf("`%s`", Zorasm_token_as_str(expect[c]));
      if (c < expected_len - 1) printf(", ");
    }
    printf(" but got `%s`\n\n", Zorasm_token_as_str(got));
    Zorasm_log_error_line(lexer->file->src, token.pos.start.line);
#endif

  return -3;
}

Zorasm_token_t Zorasm_parser_peek(Zorasm_lexer_t *lexer, unsigned int c) {
  return lexer->tokens[c];
}

Zorasm_token_t Zorasm_parser_next(Zorasm_lexer_t *lexer, Zorasm_token_t *token, unsigned int *c) {
    *token = lexer->tokens[(*c)++];
    return *token;
}

int Zorasm_parser_analyze(Zorasm_lexer_t *lexer) {
  unsigned int c = 0;
  Zorasm_token_t token = lexer->tokens[c];

  for (; token.kind != ZORASM_TK_EOF; ) {
    if (token.kind == ZORASM_TK_NATIVE) {
      if (token.len < 1) {
        #if ZORASM_LOG
        printf("\n%s:%d:%d: Empty native call\n\n", lexer->file->argfile, token.pos.start.line, token.pos.start.col);
        Zorasm_log_error_line(lexer->file->src, token.pos.start.line);
        #endif
        return -3;
      }
      else if (!Zorasm_is_native(token.value)) {
        #if ZORASM_LOG
        printf("\n%s:%d:%d: Unknown native call `%s`\n\n", lexer->file->argfile, token.pos.start.line, token.pos.start.col, token.value);
        Zorasm_log_error_line(lexer->file->src, token.pos.start.line);
        printf("Available Native calls:\n");
        Zorasm_print_all_natives();
        #endif
        return -3;
      }
      Zorasm_TokenKind expected = Zorasm_n_to_op(token.value);
      if (expected != ZORASM_TK_NONE) {
        Zorasm_token_t next = Zorasm_parser_next(lexer, &token, &c);
        if (Zorasm_parser_expect(lexer, token, expected, next.kind) != 0) return -3;
      }
    }
    else if (token.kind == ZORASM_TK_REGISTER) {
      if (token.len < 1) {
        #if ZORASM_LOG
        printf("\n%s:%d:%d: Unnamed register\n\n", lexer->file->argfile, token.pos.start.line, token.pos.start.col);
        Zorasm_log_error_line(lexer->file->src, token.pos.start.line);
        #endif
        return -3;
      }
      else if (!Zorasm_is_register(token.value)) {
        #if ZORASM_LOG
        printf("\n%s:%d:%d: Unknown register `%s`\n\n", lexer->file->argfile, token.pos.start.line, token.pos.start.col, token.value);
        Zorasm_log_error_line(lexer->file->src, token.pos.start.line);
        #endif
        return -3;
      }
    }
    else if (token.kind == ZORASM_TK_LABEL) {
      if (token.len < 1) {
        #if ZORASM_LOG
        printf("\n%s:%d:%d: Unnamed label\n\n", lexer->file->argfile, token.pos.start.line, token.pos.start.col);
        Zorasm_log_error_line(lexer->file->src, token.pos.start.line);
        #endif
        return -3;
      }
    }
    Zorasm_parser_next(lexer, &token, &c);
  }

  return 0;
}

#endif
