#define ZORA_LOG 1
#define ZORAVM_LOG 1
#define ZORASM_LOG 1

#include "./zoravm.c"
#include "../zorasm/zorasm.c"
#include "./prog.c"
#include "../inc/sys.c"
#include "../inc/utils.c"

#include <stdio.h>
#include <string.h>

#define ZORAVM_DESC "ZoraVM is a virtual machine for the running Zorasm program."

void help();
void version();
int run(char* path);
int com(char* path);

typedef struct {
  char* name;
  char* flag;
  char* desc;
} Command_t;

Command_t command[] = {
  [0] = {
    .name = "help",
    .flag = "h",
    .desc = "Prints this help message."
  },
  [1] = {
    .name = "version",
    .flag = "v",
    .desc = "Prints the version"
  },
  [2] = {
    .name = "run",
    .flag = "r",
    .desc = "Run a Zorasm program"
  },
  [3] = {
    .name = "com",
    .flag = "c",
    .desc = "Compile a Zorasm program to bytecode"
  }
};

int main(int argc, char** argv) {
    int rtn = 0;

    if (argc <= 1) {
        rtn = -1;
        help();
        goto end;
    }

    if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0) {
        help();
        return 0;
    } else if (strcmp(argv[1], "version") == 0 || strcmp(argv[1], "v") == 0) {
        version();
        return 0;
    } else if (strcmp(argv[1], "run") == 0 || strcmp(argv[1], "r") == 0) {
        if (argc < 3) {
            printf("Error: No file specified to run\n");
            rtn = 1;
            goto end;
        }
        rtn = run(argv[2]);
    } else if (strcmp(argv[1], "com") == 0 || strcmp(argv[1], "c") == 0) {
        if (argc < 3) {
            printf("Error: No file specified to compile\n");
            rtn = 1;
            goto end;
        }
        rtn = com(argv[2]);
    } else {
        help();
        printf("\nError: Unknown command '%s'.\n", argv[1]);
        rtn = -1;
        goto end;
    }

end:
    return rtn;
}

void help() {
    int c;
    int spacing = 14, flagspacing = 6;
    printf("%s\n\n", ZORAVM_DESC);
    for (c = 0; c < sizeof(command) / sizeof(Command_t); c++) {
        printf("%s", command[c].name);
        int i;
        for (i = 0; i < spacing - strlen(command[c].name); i++) printf(" ");
        printf("%s\n", command[c].desc);
    }
}

void version() {
    printf("Version: %s\n", ZORAVM_VERSION);
}

int run(char* path) {
  int rtn;
  ZoraVM_Program *prog = {0};
  Zora_file_t file = Zora_file_obj(path);

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

int com(char* path) {
  int rtn = 0;
  printf("TODO: Compile '%s'\n", path);

  return rtn;
}

