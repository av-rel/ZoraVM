#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./source/vm.c"
#include "./source/fs.c"
#include "./source/lexer.c"
#include "./source/op.c"
#include "./source/token.c"
#include "include/token.h"
#include "include/vm.h"

int ZVM(int argc, char *argv[]) {
  Zvm *zvm = zvm_new();

  char *source = filereader(argv[1]);
  file_t *file = file_obj(source, argv[1]);
  lexer_struct *lexer = (lexer_struct *)init_lexer(file);

  /* token_struct* tokens = tokenize(lexer); */

  free(lexer->tokens);
  free(lexer);
  free(file);
  free(source);
  free(zvm->globals);
  free(zvm);

  return 0;
}


int main(int argc, char *argv[]) { 
  
  if (argc < 2){
    fprintf(stderr, "No files specified");
    return 0;
  }

  return ZVM(argc, argv); 
}
