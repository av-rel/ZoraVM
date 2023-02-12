#ifndef MACRO_H
#define MACRO_H

#include <stdlib.h>
#include <string.h>

#define ArraySize(arr) sizeof(arr) / sizeof(arr[0])

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

#define Dup()                                                                  \
  { .inst = INST_DUP, }
#define Swap()                                                                 \
  { .inst = INST_SWAP, }

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
  { .inst = INST_DIV, EntryFloat(0) }
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

#define NegInt()                                                               \
  { .inst = INST_NEG, EntryInt(0) }
#define NegFloat()                                                             \
  { .inst = INST_NEG, EntryFloat(0) }
#define NegStr()                                                               \
  { .inst = INST_NEG, EntryStr(0) }

#define NotInt()                                                               \
  { .inst = INST_NOT, EntryInt(0) }
#define NotFloat()                                                             \
  { .inst = INST_NOT, EntryFloat(0) }
#define NotStr()                                                               \
  { .inst = INST_NOT, EntryStr(0) }

#define AndInt()                                                               \
  { .inst = INST_AND, EntryInt(0) }
#define AndFloat()                                                             \
  { .inst = INST_AND, EntryFloat(0) }
#define AndStr()                                                               \
  { .inst = INST_AND, EntryStr(0) }

#define OrInt()                                                                \
  { .inst = INST_OR, EntryInt(0) }
#define OrFloat()                                                              \
  { .inst = INST_OR, EntryFloat(0) }
#define OrStr()                                                                \
  { .inst = INST_OR, EntryStr(0) }

#define XorInt()                                                               \
  { .inst = INST_XOR, EntryInt(0) }
#define XorFloat()                                                             \
  { .inst = INST_XOR, EntryFloat(0) }
#define XorStr()                                                               \
  { .inst = INST_XOR, EntryStr(0) }

#define ShlInt()                                                               \
  { .inst = INST_SHL, EntryInt(0) }
#define ShlFloat()                                                             \
  { .inst = INST_SHL, EntryFloat(0) }
#define ShlStr()                                                               \
  { .inst = INST_SHL, EntryStr(0) }

#define ShrInt()                                                               \
  { .inst = INST_SHR, EntryInt(0) }
#define ShrFloat()                                                             \
  { .inst = INST_SHR, EntryFloat(0) }
#define ShrStr()                                                               \
  { .inst = INST_SHR, EntryStr(0) }

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

// Macro for the parser
#define is_num(ch) (ch >= '0' && ch <= '9')

#define is_str_int(str)                                                        \
  for (int c = 0; c < strlen(str); c++)                                        \
    if (!is_num(str[c]))                                                       \
      return 0;                                                                \
  return 1;

#define parseInt(str)                                                          \
  if (is_str_int(str))                                                         \
    return atoi(str);                                                          \
  return 0;

#endif
