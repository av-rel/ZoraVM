#include <stdio.h>
#include <stdlib.h>

#include "./source/fs.c"
#include "./source/lexer/lexer.h"
#include "./source/reserved.c"
#include "./source/vm.c"

#define ArraySize(ele) (int)sizeof(ele) / sizeof(ele[0])

Inst program[] = {{OP_PUSH, 10}, {OP_PUSH, 11}, {OP_LOG, 0},
                  {OP_SWAP},     {OP_LOG, 0},   {OP_HALT, 0}};

int ZVM(int argc, char *argv[]) {

  Zvm *zvm = zvm_new();

  // char *source = filereader(argv[i]);
  // file_t *file = file_obj(source, argv[i]);
  // lexer_struct *lexer = (lexer_struct *)init_lexer(file);

  int p = 0;
  while (program[p].type != OP_HALT) {
    vm_exec(zvm, &program[p]);
    p++;
  }

  // free(file);
  // free(lexer);
  // free(source);
  free(zvm);
  return 0;
}

int main(int argc, char *argv[]) { return ZVM(argc, argv); }