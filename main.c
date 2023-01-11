#include <stdio.h>
#include <stdlib.h>

#include "./source/fs.c"
#include "./source/lexer/lexer.h"
#include "./source/reserved.c"
#include "./source/vm.c"

#define nA(ele) (int)sizeof(ele) / sizeof(ele[0])
#define prog(op, val)                                                          \
  { .operation = op, .operand = val }

Inst program[] = {prog(OP_LOG, 10)};

int ZVM(int argc, char *argv[]) {

  // for (int i = 0; i < argc; i++) {
  Zvm *zvm = zvm_new();

  // char *source = filereader(argv[i]);
  // file_t *file = file_obj(source, argv[i]);
  // lexer_struct *lexer = (lexer_struct *)init_lexer(file);

  // free(file);
  // free(lexer);
  // free(source);
  free(zvm);
  // }
  return 0;
}

int main(int argc, char *argv[]) { return ZVM(argc, argv); }