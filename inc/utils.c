#ifndef _ZORA_UTILS_C
#define _ZORA_UTILS_C

#include "./utils.h"

int Zora_is_valid_identifier(char ch) {
  return Zora_is_alpha(ch) || ch == '_' || Zora_is_digit(ch);
}

int Zora_is_ws(char ch) {
  return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}

int Zora_is_alpha(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int Zora_is_digit(char ch) { return ch >= '0' && ch <= '9'; }

#endif
