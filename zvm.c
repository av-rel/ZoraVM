#include "./source/fs.c"
#include "./source/lexer/lexer.h"
#include "./source/vm.c"
#include <stdio.h>
#include <stdlib.h>

int ZVM(Zvm *vm, int argc, char *argv[]) {

  int i;

  for (i = 0; i < argc; i++) {

    char *source = filereader(argv[1]);
    file_t *file = file_obj(source, argv[1]);
    lexer_struct *lexer = (lexer_struct *)init_lexer(file);

    vm_run(lexer);

    free(file);
    free(lexer);
    free(source);
  }

  return 0;
}

int main(int argc, char *argv[]) { return ZVM(zvm_new(), argc, argv); }