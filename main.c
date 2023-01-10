#include <stdio.h>
#include <stdlib.h>

#include "./source/fs.c"
#include "./source/lexer/lexer.h"
#include "./source/reserved.c"
#include "./source/vm.c"

Inst insts[] = {
    // {OP_PUSH, 10}
};

void ZVM(Zvm *vm, int argc, char *argv[]) {

  for (int i = 1; i < argc; i++) {

    // char *source = filereader(argv[i]);
    // file_t *file = file_obj(source, argv[i]);
    // lexer_struct *lexer = (lexer_struct *)init_lexer(file);

    vm_run(vm, insts);

    // free(file);
    // free(lexer);
    // free(source);
  }
}

int main(int argc, char *argv[]) {
  Zvm *vm = zvm_new();
  ZVM(vm, argc, argv);
  free(vm);
  return 0;
}