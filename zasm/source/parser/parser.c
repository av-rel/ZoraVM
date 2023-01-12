#ifndef PARSER_C
#define PARSER_C

#include <ctype.h>

#include "./parser.h"
#include "../lexer/lexer.c"
#include "../token/token.c"

void Parser(lexer_struct *lexer) {
  while (lexer->cur != '\0') {

    // lexer_skip_ws(lexer);
    lexer_skip_comment(lexer);

    lexer_advance(lexer);
  }
}

#endif