#define ZORA_LOG 1
#define ZORAVM_LOG 1
#define ZORASM_LOG 1

#include "./zoravm.c"
#include "../zorasm/zorasm.c"
#include "./prog.c"
#include "../inc/sys.c"
#include "../inc/utils.c"
#include "../inc/lev.c"

#include <stdio.h>
#include <string.h>

void help(char* arg0);
void version();
int run(char* path);
int sim(char* path);
int com(char* path);

typedef struct {
  char* name;
  char* flag;
  char* desc;
} Command_t;

char* Command_name[] = { "help", "version", "run", "com" };

Command_t command[] = {
  [0] = { .name = "help", .flag = "h", .desc = "Prints this help message" },
  [1] = { .name = "version", .flag = "v", .desc = "Prints the current version" },
  [2] = { .name = "run", .flag = "r", .desc = "Run program" },
  [3] = { .name = "com", .flag = "c", .desc = "Compile program to bytecode" }
};


int main(int argc, char** argv) {
    int rtn = 0;
    char * const APP = argv[0];

    if (argc <= 1) {
        rtn = -1;
        help(APP);
        goto end;
    }
    char* cmd = argv[1];

    if (strcmp(cmd, "help") == 0 || strcmp(cmd, "h") == 0) {
        help(APP);
        goto end;
    } else if (strcmp(cmd, "version") == 0 || strcmp(cmd, "v") == 0) {
        version();
        goto end;
    } else if (strcmp(cmd, "run") == 0 || strcmp(cmd, "r") == 0) {
        if (argc < 3) {
            printf("Error: No file specified to run\n");
            rtn = 1;
            goto end;
        }
        rtn = run(argv[2]);
    } else if (strcmp(cmd, "com") == 0 || strcmp(cmd, "c") == 0) {
        if (argc < 3) {
            printf("Error: No file specified to compile\n");
            rtn = 1;
            goto end;
        }
        rtn = com(argv[2]);
    } else {
        help(APP);
        printf("%s:\n\n", APP);
        printf("\t  '%s' is not registered as a command | Try `%s help`\n", cmd, APP);
        printf("\t  Most similar command  '%s'\n", Command_name[Zora_find_similar_string(cmd, Command_name, sizeof(Command_name)/sizeof(Command_name[0]))]);
        rtn = -1;
        goto end;
    }

end:
    return rtn;
}

void help(char* arg0) {
    int c;
    int spacing = 14, flagspacing = 6;
    printf("Usage:\n\t  %s {command} [arguments]\n\n", arg0);
    printf("{commands}\n\n");
    for (c = 0; c < sizeof(command) / sizeof(Command_t); c++) {
        printf("\t  %s", command[c].name);
        int i;
        for (i = 0; i < spacing - strlen(command[c].name); i++) printf(" ");
        printf("%s\n", command[c].desc);
    }
    printf("\n");
}

void version() {
    printf("Version: %s\n", ZORAVM_VERSION);
}

int run(char* path) {
    int rtn = 0;
    int ntok = 0, err = 0, progc = 0;

    ZoraVM_Program *prog = {0};
    Zorasm_token_t* tokens = {0};

    Zora_file_t file = Zora_file_obj(path);
    if (file.len == -1) {
        printf("Error: Could not open '%s' to run program\n", path);
        goto end;
    }

    tokens = Zorasm(&file, &ntok , &err);
    if (err != 0) goto end;

    prog = malloc(sizeof(ZoraVM_Program) * (ntok + 1));
    if (!prog) {
        err = -1;
        printf("Error: Could not allocate memory for program.\n");
    }
    progc = ZoraVM_Program_from_tokens(tokens, ntok, prog);
    rtn = ZoraVME(prog, progc, ntok);

end:
    if(tokens) Zorasm_free_tokens(tokens);
    if (prog) free(prog);
    return err != 0 ? err : rtn;
}

int com(char* path) {
    int rtn = 0;
    printf("%s\n", "Unimplemented");

end:
    return rtn;
}

