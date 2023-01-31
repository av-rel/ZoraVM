#ifndef TOKENIZER_C
#define TOKENIZER_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/token.h"
#include "./lexer.c"
#include "./op.c"

static token_struct* tokenize(lexer_struct *lexer){

  unsigned int ntok = 0;

  while (lexer->cur) {

    switch (lexer->cur) {
      case ';':
        lexer_skip_comment(lexer);
        break;
      case '@':
        lexer_advance(lexer);

        while(is_identifier(lexer->cur)) {
          lexer_skip_comment(lexer);
          lexer_advance(lexer);
        }
      break;
    }

    lexer_advance(lexer);
  }

  return lexer->tokens;

}

#endif
