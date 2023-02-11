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
    return (Program *){0};
}

#endif
