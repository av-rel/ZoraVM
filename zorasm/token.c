#ifndef ZORASM_TOKEN_C
#define ZORASM_TOKEN_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lexer.c"
#include "./error.c"
#include "./token.h"
#include "../inc/utils.h"
#include "lexer.h"

int Zorasm_tokenizer(Zorasm_lexer_t *lexer) {
  int lexing = 1;
  while (lexing) {
    Zorasm_lexer_skip_ws(lexer);

    switch (lexer->cur) {
    case '\0': {
      lexing = 0;
      lexer->tokens[lexer->ntok++] = Zorasm_init_token("\0", ZORASM_TK_EOF, 0, 
          (Zorasm_node_position){.start = {.line = lexer->line, .col = lexer->col},
                          .end = {.line = lexer->line, .col = lexer->col}});
      break;
    }
    case ';': {
      Zorasm_lexer_advance(lexer);
      Zorasm_lexer_skip_line(lexer);
      break;
    }
    case '-': {
      Zorasm_position_t beforepos = (Zorasm_position_t){lexer->line, lexer->col};
      if (Zora_is_digit(Zorasm_lexer_peek(lexer, 1))) {
        int i = 0, dot = 0;
        char *num = calloc(1, sizeof(char) * (lexer->file->len + 1));
        num[i++] = lexer->cur;
        num[i++] = Zorasm_lexer_advance(lexer);

        while (Zora_is_digit(lexer->cur)) {
          num[i++] = Zorasm_lexer_advance(lexer);
          if (lexer->cur == '.') {
            if (dot > 0) break;
            num[i++] = Zorasm_lexer_advance(lexer);
            dot++;
          }
        }

        Zorasm_position_t afterpos = (Zorasm_position_t){lexer->line, lexer->col};
        lexer->tokens[lexer->ntok++] =
            Zorasm_init_token((char *)strdup(num), dot > 0 ? ZORASM_TK_FLOAT : ZORASM_TK_INT, i,
                       (Zorasm_node_position){beforepos, afterpos});
        free(num);
      } else {
        printf("\n%s:%d:%d: Unrecognizable number format\n\n", lexer->file->argfile, beforepos.line, beforepos.col);
        Zorasm_log_error_line(lexer->file->src, beforepos.line);
        return -69;
      }
      break;
    }
    case '!': {
      Zorasm_position_t beforepos = (Zorasm_position_t){lexer->line, lexer->col};
      int i = 0;
      char *inst = calloc(1, (lexer->file->len + 1) * sizeof(char));

      while (Zora_is_valid_identifier(Zorasm_lexer_advance(lexer))) inst[i++] = lexer->cur;

      Zorasm_position_t afterpos = (Zorasm_position_t){lexer->line, lexer->col};
      lexer->tokens[lexer->ntok++] = Zorasm_init_token((char *)strdup(inst), ZORASM_TK_INST, i,
                     (Zorasm_node_position){beforepos, afterpos});
      free(inst);
      break;
    }
    case '@': {
      Zorasm_position_t beforepos = (Zorasm_position_t){lexer->line, lexer->col};
      int i = 0;
      char *reg = calloc(1, sizeof(char) * (lexer->file->len + 1));

      while (Zora_is_digit(Zorasm_lexer_advance(lexer))) reg[i++] = lexer->cur;

      Zorasm_position_t afterpos = (Zorasm_position_t){lexer->line, lexer->col};
      lexer->tokens[lexer->ntok++] =
          Zorasm_init_token((char *)strdup(reg), ZORASM_TK_REGISTER, i,
                     (Zorasm_node_position){beforepos, afterpos});
      free(reg);
      break;
    }
    case '#': {
      Zorasm_position_t beforepos = (Zorasm_position_t){lexer->line, lexer->col};
      int i = 0;
      char *label = calloc(1, (lexer->file->len + 1) * sizeof(char));

      while (Zora_is_valid_identifier(Zorasm_lexer_advance(lexer))) label[i++] = lexer->cur;

      Zorasm_position_t afterpos = (Zorasm_position_t){lexer->line, lexer->col};
      lexer->tokens[lexer->ntok++] = 
        Zorasm_init_token((char *)strdup(label), ZORASM_TK_LABEL, i, 
          (Zorasm_node_position){beforepos, afterpos});
      free(label);
      break;
    }
    case '\"' : {
      Zorasm_position_t beforepos = (Zorasm_position_t){lexer->line, lexer->col};
      int s = 0, len = 0;
      char *str = calloc(1, (lexer->file->len + 1) * sizeof(char));
      while (Zorasm_lexer_advance(lexer) != '\"') {
        if (lexer->cur == '\0') {
          #if ZORASM_LOG
          printf("\n%s:%d:%d: Unterminated string literal\n\n", lexer->file->argfile, beforepos.line, beforepos.col);
          Zorasm_log_error_line(lexer->file->src, beforepos.line);
          #endif
          free(str);
          return -69;
        } else if (lexer->cur == '\\') {
            len++;
          switch (Zorasm_lexer_advance(lexer)) {
            case 'n': str[s++] = '\n'; break;
            case 't': str[s++] = '\t'; break;
            case 'r': str[s++] = '\r'; break;
            case 'a': str[s++] = '\a'; break;
            case 'b': str[s++] = '\b'; break;
            case 'f': str[s++] = '\f'; break;
            case 'v': str[s++] = '\v'; break;
            case '0': str[s++] = '\0'; break;
            case '?': str[s++] = '\?'; break;
            case '\\': str[s++] = '\\'; break;
            case '\"': str[s++] = '\"'; break;
            case '\'': str[s++] = '\''; break;
            default: {
                str[s++] = '\\';
                str[s++] = lexer->cur;
                len++;
            };
          }
        } else {
            str[s++] = lexer->cur;
            len++;
        }
      }

      Zorasm_lexer_advance(lexer);
      Zorasm_position_t afterpos = (Zorasm_position_t){lexer->line, lexer->col};
      lexer->tokens[lexer->ntok++] = Zorasm_init_token((char *)strdup(str), ZORASM_TK_STRING, len, 
          (Zorasm_node_position){beforepos, afterpos});
      free(str);
      break;
    }
    default: {
      Zorasm_position_t beforepos = (Zorasm_position_t){lexer->line, lexer->col};
      if (Zora_is_digit(lexer->cur)) {
        int i = 0, dot = 0;
        char *num = calloc(1, sizeof(char) * (lexer->file->len + 1));
        while (Zora_is_digit(lexer->cur)) {
          num[i++] = lexer->cur;
          Zorasm_lexer_advance(lexer);
          if (lexer->cur == '.') {
            if (dot > 0) break;
            num[i++] = Zorasm_lexer_advance(lexer);
            dot++;
          }
        }
        Zorasm_position_t afterpos = (Zorasm_position_t){lexer->line, lexer->col};
        lexer->tokens[lexer->ntok++] = Zorasm_init_token((char *)strdup(num), dot > 0 ? ZORASM_TK_FLOAT : ZORASM_TK_INT, i, (Zorasm_node_position){beforepos, afterpos});
        free(num);
        break;
      } 
      else {
        lexing = 1;
        Zorasm_lexical_error(lexer);
        return -3;
      }
    }
    }
  }
  return 0;
}

Zorasm_token_t Zorasm_init_token(char *value, Zorasm_TokenKind kind, int len, Zorasm_node_position pos) {
  return (Zorasm_token_t) {.value = value, .kind = kind, .len = len, .pos = pos};
}

char *Zorasm_token_as_str(Zorasm_TokenKind kind) {
  switch (kind) {
  case ZORASM_TK_INT:
    return "int";
  case ZORASM_TK_STRING:
    return "string";
  case ZORASM_TK_FLOAT:
    return "float";
  case ZORASM_TK_LABEL:
    return "label";
  case ZORASM_TK_REGISTER:
    return "register";
  case ZORASM_TK_INST:
    return "inst";
  case ZORASM_TK_KIND:
    return "data";
  case ZORASM_TK_EOF:
    return "EOF";
  case ZORASM_TK_NONE:
    return "none"; 
  default:
    return "unknown";
  }
}

void Zorasm_free_tokens(Zorasm_token_t* tokens) {
  free(tokens);
}

#endif
