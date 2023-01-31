#include <stdio.h>
#include <stdlib.h>

#include "./src/vm.c"
#include "./src/fs.c"
#include "./src/lexer.c"
#include "./src/op.c"
#include "./src/token.c"
#include "./src/op.c"

Program program[] = {
  {OP_STORE, 10},
  {OP_STORE, 20},
  {OP_STORE, 10011},
  {OP_MOVEIP, 2},
  {OP_PRINT}
  /* {OP_PRINT}, */
  /* {OP_EXIT} */
};

int ZVM(int argc, char *argv[]) {
  Zvm *zvm = zvm_new();

  /* char *source = filereader(argv[1]); */
  /* file_t *file = file_obj(source, argv[1]); */
  /* lexer_struct *lexer = (lexer_struct *)init_lexer(file); */

  /* token_struct* tokens = tokenize(lexer); */

  for (int i = 0; i < ArraySize(program); i++){
    zvm_exec(zvm, program[i]);
  }

  /* free(lexer->tokens); */
  /* free(lexer); */
  /* free(file); */
  /* free(source); */
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

