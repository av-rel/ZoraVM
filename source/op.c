#ifndef OP_C
#define OP_C

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

const char *keywords[] = {"store",
                          "add",  "sub", "mul", "div",  "mod", "pow", "inc", "dec", "addeq", "subeq", "muleq", "diveq", "modeq", "poweq",
                          "jump", "cmp", "ncmp" , "jz", "jnz", "je", "jne", "jg", "jge", "jl", "jle",
                          "ret", "print", "scan", "shell", "time", "exit",
                          "fopen", "fclose" ,"fread", "fwrite", "fappend", "frename", "fremove", "flist", "fdirname", "fcwd", "fmkdir", "frmdir", "fmovedir", "fcopydir"
};

const size_t keyword_size = sizeof(keywords) / sizeof(char*);

bool isKeyword(char *c) {
  for (int i = 0; i < keyword_size; i++) if (strcmp(c, keywords[i]) == 0) return true;
  return false;
};

typedef enum {
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
  OP_JUMP,
  OP_CMP,
  OP_CMPN,
  OP_JZ,
  OP_JNZ,
  OP_JE,
  OP_JNE,
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
