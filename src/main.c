#define ZORAVM_LOG 1
#define ZORASM_LOG 1

#include "./zoravm.c"
#include "./prog.c"

int Usage(char** argv) {
  printf("Usage: %s <file>\n", argv[0]);
  return -1;
}

int main(int argc, char** argv) {

  if (argc < 2) {
    return Usage(argv);
  }

  int rtn;
  ZoraVM_Program *prog = {0};
  Zorasm_file_t file = file_obj(argv[1]);

  int ntok = 0, err = 0, progc = 0;
  Zorasm_token_t* tokens = Zorasm(&file, &ntok , &err);
  if (err != 0) goto end;

  prog = malloc(sizeof(ZoraVM_Program) * (ntok + 1));
  if (!prog) {
    err = -1;
    #if ZORAVM_LOG
    printf("Error: Could not allocate memory for program.\n");
    #endif
  }
  progc = ZoraVM_Program_from_tokens(tokens, ntok, prog);
  rtn = ZoraVME(prog, progc, ntok);

end:
  Zorasm_free_tokens(tokens);
  if (prog) free(prog);
  return err != 0 ? err : rtn;
}
