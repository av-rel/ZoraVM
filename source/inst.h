#ifndef _ZORAVM_INST_H
#define _ZORAVM_INST_H

#include "../zorasm/kw.h"

#define ZoraVM_EntryInt(v)                                                            \
  { .kind = ZORASM_DATA_INT, .val.integer = v }
#define ZoraVM_EntryFloat(v)                                                          \
  { .kind = ZORASM_DATA_FLOAT, .val.floating = v }
#define ZoraVM_EntryStr(v)                                                            \
  { .kind = ZORASM_DATA_STRING, .val.string = v }

#define ZoraVM_PushInt(val)                                                           \
  { .inst = ZORASM_INST_PUSH, .entry = ZoraVM_EntryInt(val) }
#define ZoraVM_PushFloat(val)                                                         \
  { .inst = ZORASM_INST_PUSH, .entry = ZoraVM_EntryFloat(val) }
#define ZoraVM_PushStr(val)                                                           \
  { .inst = ZORASM_INST_PUSH, .entry = ZoraVM_EntryStr(val) }

#define ZoraVM_Pop()                                                                  \
  { .inst = ZORASM_INST_POP, }
#define ZoraVM_Store(val)                                                             \
  { .inst = ZORASM_INST_STORE, .entry = ZoraVM_EntryInt(val) }
#define ZoraVM_Load(val)                                                              \
  { .inst = ZORASM_INST_LOAD, .entry = ZoraVM_EntryInt(val) }

#define ZoraVM_Dup()                                                                  \
  { .inst = ZORASM_INST_DUP, }
#define ZoraVM_Swap()                                                                 \
  { .inst = ZORASM_INST_SWAP, }

#define ZoraVM_Add()                                                                  \
  { .inst = ZORASM_INST_ADD, }
#define ZoraVM_Sub()                                                                  \
  { .inst = ZORASM_INST_SUB, }
#define ZoraVM_Mul()                                                                  \
  { .inst = ZORASM_INST_MUL, }
#define ZoraVM_Div()                                                                  \
  { .inst = ZORASM_INST_DIV, }
#define ZoraVM_Mod()                                                                  \
  { .inst = ZORASM_INST_MOD, }

#define ZoraVM_Inc()                                                                  \
  { .inst = ZORASM_INST_INC, }
#define ZoraVM_Dec()                                                                  \
  { .inst = ZORASM_INST_DEC, }
#define ZoraVM_Pow()                                                                  \
  { .inst = ZORASM_INST_POW, }

#define ZoraVM_Neg()                                                                  \
  { .inst = ZORASM_INST_NEG, }
#define ZoraVM_Not()                                                                  \
  { .inst = ZORASM_INST_NOT, }
#define ZoraVM_And()                                                                  \
  { .inst = ZORASM_INST_AND, }
#define ZoraVM_Or()                                                                   \
  { .inst = ZORASM_INST_OR, }
#define ZoraVM_Xor()                                                                  \
  { .inst = ZORASM_INST_XOR, }
#define ZoraVM_Shl()                                                                  \
  { .inst = ZORASM_INST_SHL, }
#define ZoraVM_Shr()                                                                  \
  { .inst = ZORASM_INST_SHR, }

#define ZoraVM_CmpEq()                                                                \
  { .inst = ZORASM_INST_EQ, }
#define ZoraVM_CmpNeq()                                                               \
  { .inst = ZORASM_INST_NEQ, }
#define ZoraVM_CmpGt()                                                                \
  { .inst = ZORASM_INST_GT, }
#define ZoraVM_CmpNotGt()                                                             \
  { .inst = ZORASM_INST_NGT, }
#define ZoraVM_CmpLt()                                                                \
  { .inst = ZORASM_INST_LT, }
#define ZoraVM_CmpNotLt()                                                             \
  { .inst = ZORASM_INST_NLT, }
#define ZoraVM_CmpGte()                                                                \
  { .inst = ZORASM_INST_GTE, }
#define ZoraVM_CmpNotGte()                                                             \
  { .inst = ZORASM_INST_NGTE, }
#define ZoraVM_CmpLte()                                                                \
  { .inst = ZORASM_INST_LTE, }
#define ZoraVM_CmpNotLte()                                                             \
  { .inst = ZORASM_INST_NLTE, }

#define ZoraVM_Jmp(val)                                                               \
  { .inst = ZORASM_INST_JMP, .entry = ZoraVM_EntryInt(val) }
#define ZoraVM_JmpIf(val)                                                             \
  { .inst = ZORASM_INST_JMPIF, .entry = ZoraVM_EntryInt(val) }
#define ZoraVM_JmpIfNot(val)                                                          \
  { .inst = ZORASM_INST_JMPIFN, .entry = ZoraVM_EntryInt(val) }
#define ZoraVM_Call(val)                                                               \
  { .inst = ZORASM_INST_CALL, .entry = ZoraVM_EntryInt(val) }
#define ZoraVM_CallIf(val)                                                             \
  { .inst = ZORASM_INST_CALLIF, .entry = ZoraVM_EntryInt(val) }
#define ZoraVM_CallIfNot(val)                                                          \
  { .inst = ZORASM_INST_CALLIFN, .entry = ZoraVM_EntryInt(val) }

#define ZoraVM_Print()                                                                \
  { .inst = ZORASM_INST_PRINT, }
#define ZoraVM_Scan()                                                              \
  { .inst = ZORASM_INST_SCAN, }
#define ZoraVM_SizeOf()                                                               \
  {.inst = ZORASM_INST_SIZEOF, }

#define ZoraVM_Env()                                                                  \
  { .inst = ZORASM_INST_ENV, }

#define ZoraVM_DumpStack()                                                            \
  { .inst = ZORASM_INST_DUMP_STACK, }
#define ZoraVM_DumpMem()                                                              \
  { .inst = ZORASM_INST_DUMP_MEM, }

#define ZoraVM_Ret(a)                                                                  \
  { .inst = ZORASM_INST_RET, .entry = ZoraVM_EntryInt(a)}
#define ZoraVM_Halt(a)                                                                \
  { .inst = ZORASM_INST_HALT, .entry = ZoraVM_EntryInt(a) }

#endif
