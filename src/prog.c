#ifndef _PROG_C
#define _PROG_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/vm.h"
#include "./inst.c"

#define ENST_STR_LEN 69

Program asm_inst_to_program(char *asm_inst) { return (Program){0}; }

Program *translate_asm_to_program(char *source) {
  unsigned int filelen = strlen(source);
  Program *programs = {0};
  char *insts[] = {0};
  unsigned int inst_c = 0;

  int p = 0;
  char enst[ENST_STR_LEN] = {0};

  for (int c = 0; c < filelen; c++) {
    printf("%c", source[c]);
  }

  for (int k = 0; k < inst_c; k++) {
    programs[k] = asm_inst_to_program(insts[k]);
  }

  return programs;
}

#endif
