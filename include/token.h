#ifndef TOKEN_H
#define TOKEN_H

typedef enum{
  TK_ID,
  TK_STRING,
  TK_INT,
  TK_FLOAT,
  TK_HEX,
  TK_BOOL,
  TK_NULL,
} TokenType;

typedef struct{
  char* name;
  TokenType type; 
} token_struct;

#endif
