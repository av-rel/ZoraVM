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

#define Store(val)                                                             \
  { .inst = INST_STORE, .entry = EntryInt(val) }

#define Load(val)                                                              \
  { .inst = INST_LOAD, .entry = EntryInt(val) }

#define Dup(val)    \
  {.inst = INST_DUP, .entry = EntryInt(val)}

#define Swap(val)    \
  {.inst = INST_SWAP, .entry = EntryInt(val)}

#define AddInt()                                                               \
  { .inst = INST_ADD, EntryInt(0) }
#define AddFloat()                                                             \
  { .inst = INST_ADD, EntryFloat(0) }
#define AddStr()                                                               \
  { .inst = INST_ADD, EntryStr(0) }

#define SubInt()                                                               \
  { .inst = INST_SUB, EntryInt(0) }
#define SubFloat()                                                             \
  { .inst = INST_SUB, EntryFloat(0) }
#define SubStr()                                                               \
  { .inst = INST_SUB, EntryStr(0) }

#define MulInt()                                                               \
  { .inst = INST_MUL, EntryInt(0) }
#define MulFloat()                                                             \
  { .inst = INST_MUL, EntryFloat(0) }
#define MulStr()                                                               \
  { .inst = INST_MUL, EntryStr(0) }

#define DivInt()                                                               \
  { .inst = INST_DIV, EntryInt(0) }
#define DivFloat()                                                             \
  { .inst = INST_DIV, , EntryFloat(0) }
#define DivStr()                                                               \
  { .inst = INST_DIV, , EntryStr(0) }

#define ModInt()                                                               \
  { .inst = INST_MOD, EntryInt(0) }
#define ModFloat()                                                             \
  { .inst = INST_MOD, EntryFloat(0) }
#define ModStr()                                                               \
  { .inst = INST_MOD, EntryStr(0) }

#define IncInt()                                                               \
  { .inst = INST_INC, EntryInt(0) }
#define IncFloat()                                                             \
  { .inst = INST_INC, EntryFloat(0) }
#define IncStr()                                                               \
  { .inst = INST_INC, EntryStr(0) }

#define DecInt()                                                               \
  { .inst = INST_DEC, EntryInt(0) }
#define DecFloat()                                                             \
  { .inst = INST_DEC, EntryFloat(0) }
#define DecStr()                                                               \
  { .inst = INST_DEC, EntryStr(0) }

#define PowInt()                                                               \
  { .inst = INST_POW, EntryInt(0) }
#define PowFloat()                                                             \
  { .inst = INST_POW, EntryFloat(0) }
#define PowStr()                                                               \
  { .inst = INST_POW, EntryString(0) }

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

#define DumpStack()                                                            \
  { .inst = INST_DUMP_STACK, }
#define DumpMem()                                                              \
  { .inst = INST_DUMP_MEM, }
#define Halt(a)                                                                \
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


static int is_num(char ch) { return ch >= '0' && ch <= '9'; }

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
