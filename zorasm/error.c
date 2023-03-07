#ifndef ZORASM_ERROR_C
#define ZORASM_ERROR_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lexer.h"

void Zorasm_log_error_line(char *source, int errline) {
#if ZORASM_LOG
  int line = 1, pos = 0, findline = 1, scrapline = 1, i;
  int filelen = strlen(source);
  for (i = 0; (i < filelen && findline); i++) {
    if (source[pos] == '\n') line++;
    if (errline == line) {
      pos++;
      printf("  %d | ", errline);
      while (scrapline) {
        if (source[pos] == '\0') break;
        printf("%c", source[pos++]);
        if (source[pos] == '\n' && filelen > pos) scrapline = 0;
      }
      printf("\n\n");
      findline = 0;
    }
    pos++;
  }
#endif
}

void Zorasm_lexical_error(Zorasm_lexer_t *lexer) {
#if ZORASM_LOG
  printf("\n%s:%d:%d Unrecognized token `%c`\n\n", lexer->file->argfile, lexer->line, lexer->col, lexer->cur);
  Zorasm_log_error_line(lexer->file->src, lexer->line);
#endif
}

#endif
