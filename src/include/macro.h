#ifndef MACRO_H
#define MACRO_H

#include <stdlib.h>

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

#define Add()                                                                  \
  { .inst = INST_ADD, }
#define Sub()                                                                  \
  { .inst = INST_SUB, }
#define Mul()                                                                  \
  { .inst = INST_MUL, }
#define Div()                                                                  \
  { .inst = INST_DIV, }
#define Mod()                                                                  \
  { .inst = INST_MOD, }

#define Inc()                                                                  \
  { .inst = INST_INC, }
#define Dec()                                                                  \
  { .inst = INST_DEC, }
#define Pow()                                                                  \
  { .inst = INST_POW, }

#define Neg()                                                                  \
  { .inst = INST_NEG, }
#define Not()                                                                  \
  { .inst = INST_NOT, }
#define And()                                                                  \
  { .inst = INST_AND, }
#define Or()                                                                   \
  { .inst = INST_OR, }
#define Xor()                                                                  \
  { .inst = INST_XOR, }
#define Shl()                                                                  \
  { .inst = INST_SHL, }
#define Shr()                                                                  \
  { .inst = INST_SHR, }

#define CmpEq()                                                                \
  { .inst = INST_CMP_EQ, }
#define CmpNeq()                                                               \
  { .inst = INST_CMP_NEQ, }
#define CmpGt()                                                                \
  { .inst = INST_CMP_GT, }
#define CmpNotGt()                                                             \
  { .inst = INST_CMP_NGT, }
#define CmpLt()                                                                \
  { .inst = INST_CMP_LT, }
#define CmpNotLt()                                                             \
  { .inst = INST_CMP_NLT, }
#define CmpGte()                                                                \
  { .inst = INST_CMP_GTE, }
#define CmpNotGte()                                                             \
  { .inst = INST_CMP_NGTE, }
#define CmpLte()                                                                \
  { .inst = INST_CMP_LTE, }
#define CmpNotLte()                                                             \
  { .inst = INST_CMP_NLTE, }

#define Jmp(val)                                                               \
  { .inst = INST_JMP, .entry = EntryInt(val) }
#define JmpIf(val)                                                             \
  { .inst = INST_JMPIF, .entry = EntryInt(val) }
#define JmpIfNot(val)                                                          \
  { .inst = INST_JMPIFN, .entry = EntryInt(val) }

#define Print()                                                                \
  { .inst = INST_PRINT, }

#define ScanInt()                                                              \
  { .inst = INST_SCAN, .entry = EntryInt(0) }
#define ScanFloat()                                                            \
  { .inst = INST_SCAN, .entry = EntryFloat(0) }
#define ScanStr()                                                              \
  { .inst = INST_SCAN, .entry = EntryStr(0) }

#define SizeOf()                                                               \
  {.inst = INST_SIZEOF, }

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
