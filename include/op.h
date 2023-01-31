#ifndef OP_H
#define OP_H

typedef enum {
  OP_MOVEIP,
  OP_STORE,
  OP_DISPOSE,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_MOD,
  OP_POW,
  OP_INC,
  OP_DEC,
  OP_ADDEQ,
  OP_SUBEQ,
  OP_MULEQ,
  OP_DIVEQ,
  OP_MODEQ,
  OP_POWEQ,
  OP_JMP,
  OP_CMP,
  OP_CMPN,
  OP_JZ,
  OP_JZN,
  OP_JE,
  OP_JEN,
  OP_JG,
  OP_JGE,
  OP_JL,
  OP_JLE,
  OP_RET,
  OP_PRINT,
  OP_SCAN,
  OP_SHELL,
  OP_TIME,
  OP_EXIT,
  OP_FOPEN,
  OP_FCLOSE,
  OP_FREAD,
  OP_FWRITE,
  OP_FAPPEND,
  OP_FRENAME,
  OP_FREMOVE,
  OP_FLIST,
  OP_FDIRNAME,
  OP_FCWD,
  OP_FMKDIR,
  OP_FRMDIR,
  OP_FMOVEDIR,
  OP_FCOPYDIR,
  OP_NONE,
} OP_Type;

#endif
