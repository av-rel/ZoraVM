#ifndef DEF_C
#define DEF_C

#include <stdlib.h>
#include <string.h>

#include "./include/vm.h"

#define EntryInt(v)                                                            \
  { .kind = DATA_INTEGER, .val.integer = v }
#define EntryFloat(v)                                                          \
  { .kind = DATA_FLOATING, .val.floating = v }
#define EntryStr(v)                                                            \
  { .kind = DATA_STRING, .val.string = v }

#define PushInt(val)                                                           \
  { .inst = INST_PUSH, .entry = EntryInt(val) }

#define PushFloat(val)                                                         \
  { .inst = INST_PUSH, .entry = EntryFloat(val) }

#define PushStr(val)                                                           \
  { .inst = INST_PUSH, .entry = EntryStr(val) }

#define Pop()                                                                  \
  { .inst = INST_POP, }

#define AddInt()                                                               \
  { .inst = INST_ADD, }

#define SubInt()                                                               \
  { .inst = INST_SUB, }

#define MulInt()                                                               \
  { .inst = INST_MUL, }

#define DivInt()                                                               \
  { .inst = INST_DIV, }

#define ModInt()                                                               \
  { .inst = INST_MOD, }

#define PrintInt()                                                             \
  { .inst = INST_PRINT, .entry = EntryInt(0) }

#define PrintFloat()                                                           \
  { .inst = INST_PRINT, .entry = EntryFloat(0) }

#define PrintStr()                                                             \
  { .inst = INST_PRINT, .entry = EntryStr(0) }

#define ScanInt()                                                              \
  { .inst = INST_SCAN, .entry = EntryInt(0) }

#define ScanFloat()                                                            \
  { .inst = INST_SCAN, .entry = EntryFloat(0) }

#define ScanStr()                                                              \
  { .inst = INST_SCAN, .entry = EntryStr(0) }

#define Dump()                                                                 \
  { .inst = INST_DUMP, }

#define Halt(a)                                                                 \
  { .inst = INST_HALT, .entry = EntryInt(a) }

char *DATAKIND_as_str(DATA_KIND kind) {
  switch (kind) {
  case DATA_INTEGER:
    return "INTEGER";
  case DATA_STRING:
    return "STRING";
  case DATA_FLOATING:
    return "FLOATING";
  default:
    return "UNKNOWN";
  }
}

int is_num(char ch) { return ch >= '0' && ch <= '9'; }

int is_str_int(char *str) {
  for (int c = 0; c < strlen(str); c++)
    if (!is_num(str[c]))
      return 0;
  return 1;
}

int parseInt(char *str) {
  if (is_str_int(str))
    return atoi(str);
  return 0;
}

#endif
