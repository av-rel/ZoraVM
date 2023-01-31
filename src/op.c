#ifndef OP_C
#define OP_C

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "../include/op.h"

const char *keywords[] = {"store", "dispose",
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

#endif
