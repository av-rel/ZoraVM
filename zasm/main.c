#include <stdio.h>
#include <stdlib.h>

#include "./source/fs.c"
#include "./source/lexer/lexer.c"
#include "./source/parser/parser.c"

int main(int argc, char **argv) {

  if (argc < 2) {
    printf("File not specified");
    return 0;
  }

  char *buffer = filereader(argv[1]);
  file_t *file = file_obj(buffer, argv[1]);
  lexer_struct *lexer = (lexer_struct *)init_lexer(file);

  Parser(lexer);

  free(buffer);
  free(file);
  free(lexer);
  return 0;
}