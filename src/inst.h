#ifndef _ZORAVM_INST_H
#define _ZORAVM_INST_H

typedef enum {
  ZORAVM_INST_PUSH = 0,
  ZORAVM_INST_POP,
  ZORAVM_INST_STORE,
  ZORAVM_INST_LOAD,
  ZORAVM_INST_PRINT,
  ZORAVM_INST_SCAN,
  ZORAVM_INST_RET,
  ZORAVM_INST_HALT,
  //
  ZORAVM_INST_DUP,
  ZORAVM_INST_SWAP,
  //
  ZORAVM_INST_ADD,
  ZORAVM_INST_SUB,
  ZORAVM_INST_MUL,
  ZORAVM_INST_DIV,
  ZORAVM_INST_MOD,
  //
  ZORAVM_INST_CMP_EQ,
  ZORAVM_INST_CMP_GT,
  ZORAVM_INST_CMP_LT,
  ZORAVM_INST_CMP_GTE,
  ZORAVM_INST_CMP_LTE,
  //
  ZORAVM_INST_CMP_NEQ,
  ZORAVM_INST_CMP_NGT,
  ZORAVM_INST_CMP_NLT,
  ZORAVM_INST_CMP_NGTE,
  ZORAVM_INST_CMP_NLTE,
  //
  ZORAVM_INST_JMP,
  ZORAVM_INST_JMPIF,
  ZORAVM_INST_JMPIFN,
  //
  ZORAVM_INST_AND,
  ZORAVM_INST_OR,
  ZORAVM_INST_XOR,
  ZORAVM_INST_NOT,
  ZORAVM_INST_NEG,
  ZORAVM_INST_SHL,
  ZORAVM_INST_SHR,
  //
  ZORAVM_INST_INC,
  ZORAVM_INST_DEC,
  ZORAVM_INST_POW,
  //
  ZORAVM_INST_SIZEOF,
  //
  ZORAVM_INST_FOPEN,
  ZORAVM_INST_FCLOSE,
  ZORAVM_INST_FREAD,
  ZORAVM_INST_FWRITE,
  //
  ZORAVM_INST_DUMP_STACK,
  ZORAVM_INST_DUMP_MEM,
  //
  ZORAVM_TOTAL_INST
} ZoraVM_Inst;


#define ZoraVM_EntryInt(v)                                                            \
  { .kind = ZORAVM_DATA_INTEGER, .val.integer = v }
#define ZoraVM_EntryFloat(v)                                                          \
  { .kind = ZORAVM_DATA_FLOATING, .val.floating = v }
#define ZoraVM_EntryStr(v)                                                            \
  { .kind = ZORAVM_DATA_STRING, .val.string = v }

#define ZoraVM_PushInt(val)                                                           \
  { .inst = ZORAVM_INST_PUSH, .entry = ZoraVM_EntryInt(val) }
#define ZoraVM_PushFloat(val)                                                         \
  { .inst = ZORAVM_INST_PUSH, .entry = ZoraVM_EntryFloat(val) }
#define ZoraVM_PushStr(val)                                                           \
  { .inst = ZORAVM_INST_PUSH, .entry = ZoraVM_EntryStr(val) }

#define ZoraVM_Pop()                                                                  \
  { .inst = ZORAVM_INST_POP, }
#define ZoraVM_Store(val)                                                             \
  { .inst = ZORAVM_INST_STORE, .entry = ZoraVM_EntryInt(val) }
#define ZoraVM_Load(val)                                                              \
  { .inst = ZORAVM_INST_LOAD, .entry = ZoraVM_EntryInt(val) }

#define ZoraVM_Dup()                                                                  \
  { .inst = ZORAVM_INST_DUP, }
#define ZoraVM_Swap()                                                                 \
  { .inst = ZORAVM_INST_SWAP, }

#define ZoraVM_Add()                                                                  \
  { .inst = ZORAVM_INST_ADD, }
#define ZoraVM_Sub()                                                                  \
  { .inst = ZORAVM_INST_SUB, }
#define ZoraVM_Mul()                                                                  \
  { .inst = ZORAVM_INST_MUL, }
#define ZoraVM_Div()                                                                  \
  { .inst = ZORAVM_INST_DIV, }
#define ZoraVM_Mod()                                                                  \
  { .inst = ZORAVM_INST_MOD, }

#define ZoraVM_Inc()                                                                  \
  { .inst = ZORAVM_INST_INC, }
#define ZoraVM_Dec()                                                                  \
  { .inst = ZORAVM_INST_DEC, }
#define ZoraVM_Pow()                                                                  \
  { .inst = ZORAVM_INST_POW, }

#define ZoraVM_Neg()                                                                  \
  { .inst = ZORAVM_INST_NEG, }
#define ZoraVM_Not()                                                                  \
  { .inst = ZORAVM_INST_NOT, }
#define ZoraVM_And()                                                                  \
  { .inst = ZORAVM_INST_AND, }
#define ZoraVM_Or()                                                                   \
  { .inst = ZORAVM_INST_OR, }
#define ZoraVM_Xor()                                                                  \
  { .inst = ZORAVM_INST_XOR, }
#define ZoraVM_Shl()                                                                  \
  { .inst = ZORAVM_INST_SHL, }
#define ZoraVM_Shr()                                                                  \
  { .inst = ZORAVM_INST_SHR, }

#define ZoraVM_CmpEq()                                                                \
  { .inst = ZORAVM_INST_CMP_EQ, }
#define ZoraVM_CmpNeq()                                                               \
  { .inst = ZORAVM_INST_CMP_NEQ, }
#define ZoraVM_CmpGt()                                                                \
  { .inst = ZORAVM_INST_CMP_GT, }
#define ZoraVM_CmpNotGt()                                                             \
  { .inst = ZORAVM_INST_CMP_NGT, }
#define ZoraVM_CmpLt()                                                                \
  { .inst = ZORAVM_INST_CMP_LT, }
#define ZoraVM_CmpNotLt()                                                             \
  { .inst = ZORAVM_INST_CMP_NLT, }
#define ZoraVM_CmpGte()                                                                \
  { .inst = ZORAVM_INST_CMP_GTE, }
#define ZoraVM_CmpNotGte()                                                             \
  { .inst = ZORAVM_INST_CMP_NGTE, }
#define ZoraVM_CmpLte()                                                                \
  { .inst = ZORAVM_INST_CMP_LTE, }
#define ZoraVM_CmpNotLte()                                                             \
  { .inst = ZORAVM_INST_CMP_NLTE, }

#define ZoraVM_Jmp(val)                                                               \
  { .inst = ZORAVM_INST_JMP, .entry = ZoraVM_EntryInt(val) }
#define ZoraVM_JmpIf(val)                                                             \
  { .inst = ZORAVM_INST_JMPIF, .entry = ZoraVM_EntryInt(val) }
#define ZoraVM_JmpIfNot(val)                                                          \
  { .inst = ZORAVM_INST_JMPIFN, .entry = ZoraVM_EntryInt(val) }

#define ZoraVM_Print()                                                                \
  { .inst = ZORAVM_INST_PRINT, }

#define ZoraVM_ScanInt()                                                              \
  { .inst = ZORAVM_INST_SCAN, .entry = ZoraVM_EntryInt(0) }
#define ZoraVM_ScanFloat()                                                            \
  { .inst = ZORAVM_INST_SCAN, .entry = ZoraVM_EntryFloat(0) }
#define ZoraVM_ScanStr()                                                              \
  { .inst = ZORAVM_INST_SCAN, .entry = ZoraVM_EntryStr(0) }

#define ZoraVM_SizeOf()                                                               \
  {.inst = ZORAVM_INST_SIZEOF, }

#define ZoraVM_DumpStack()                                                            \
  { .inst = ZORAVM_INST_DUMP_STACK, }
#define ZoraVM_DumpMem()                                                              \
  { .inst = ZORAVM_INST_DUMP_MEM, }

#define ZoraVM_Halt(a)                                                                \
  { .inst = ZORAVM_INST_HALT, .entry = ZoraVM_EntryInt(a) }

#endif
