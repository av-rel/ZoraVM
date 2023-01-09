#ifndef FS_C
#define FS_C

#include "./lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>

char *filereader(char *path) {
  FILE *file = fopen(path, "r");

  if (!file) {
    printf("Error: Could not read file <%s>\n", path);
    exit(0);
  }

  fseek(file, 0, SEEK_END);
  int file_size = ftell(file);
  rewind(file);

  char *buffer = (char *)calloc(1, file_size);
  int bytes_read = fread(buffer, 1, file_size, file);

  fclose(file);
  buffer[bytes_read] = '\0';

  return buffer;
}

file_t *file_obj(char *src, char *name) {
  file_t *fileinfo = (file_t *)calloc(1, sizeof(file_t));
  fileinfo->name = name;
  fileinfo->src = src;
  fileinfo->size = strlen(src);
  return fileinfo;
}

#endif