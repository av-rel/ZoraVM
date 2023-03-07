#ifndef ZORASM_TOKEN_H
#define ZORASM_TOKEN_H

typedef enum {
  ZORASM_TK_EOF = 0,         // EOF
  ZORASM_TK_REGISTER,    // register - @1, @818
  ZORASM_TK_NATIVE,      // !call
  ZORASM_TK_LABEL,       // #main
  ZORASM_TK_KIND,
  ZORASM_TK_INT,         // 118191
  ZORASM_TK_FLOAT,       // 1.1
  ZORASM_TK_STRING,      // "Hello"
  ZORASM_TK_NONE
} Zorasm_TokenKind;

typedef struct {
  int line;
  int col;
} Zorasm_position_t;

typedef struct {
  Zorasm_position_t start;
  Zorasm_position_t end;
} Zorasm_node_position;

typedef struct {
  char *value;
  Zorasm_TokenKind kind;
  unsigned int len;
  Zorasm_node_position pos;
} Zorasm_token_t;

Zorasm_token_t Zorasm_init_token(char *value, Zorasm_TokenKind kind, int len, Zorasm_node_position pos);
char *Zorasm_token_as_str(Zorasm_TokenKind kind);
void Zorasm_free_tokens(Zorasm_token_t* tokens);

#endif
