#ifndef ZORASM_SYS_C
#define ZORASM_SYS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *argfile;
  char *path;
  char *file;
  char *name;
  char *ext;
  char *src;
  int len;
} Zorasm_file_t;

void Zorasm_sys_exec(char *command) {
  FILE *fp = (FILE *)popen(command, "r");
  pclose(fp);
}

char *Zorasm_absolute_path(char *path) {
  const int MAXPATH = 260;
  return (char *)_fullpath(NULL, path, MAXPATH);
}

char *Zorasm_join_path(char *base, char *trail) {
  return (char *)strcat((char *)strcat(Zorasm_absolute_path(base), "/"), trail);
}

long long Zorasm_filesize_from_fp(FILE *fp) {
  fseek(fp, 0, SEEK_END);
  long long size = ftell(fp);
  rewind(fp);
  return size;
}

char *Zorasm_filereader(char *path) {
  FILE *file;

  if ((file = (FILE *)fopen(path, "r")) == NULL) {
    fclose(file);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long long file_size = ftell(file);
  rewind(file);
  char *buffer = (char *)malloc(file_size);
  long long bytes_read = fread((char *)buffer, 1, file_size, file);

  fclose(file);
  buffer[bytes_read] = '\0';
  char *content = (char *)strdup((char *)buffer);
  free(buffer);

  return content;
}

long long Zorasm_filewriter(char *path, char *content) {
  FILE *file = fopen(path, "w");
  if (!file) return -1;

  fprintf(file, "%s", content);
  long long size = Zorasm_filesize_from_fp(file);
  fclose(file);

  return size;
}

char *Zorasm_get_file_extract(char *file) {
  char *extract = (char *)strrchr((char *)strdup(file), '\\');

  if (!extract) extract = (char *)strrchr(extract, '/');
  if (extract) *extract = '\0';

  return (char *)++extract;
}

char *Zorasm_get_file_name(char *filepath) {
  return (char *)strtok((char *)strdup(filepath), ".");
}

char *Zorasm_get_file_ext(char *path) {
  char *ext = (char *)strrchr((char *)strdup(path), '.');
  if (!ext) return "";

  return (char *)++ext;
}

char *Zorasm_load_file_content(char *path) {
  char *content = Zorasm_filereader(path);
  return content;
}

Zorasm_file_t file_obj(char *path) {
  Zorasm_file_t fl =  {0};

  fl.argfile = path;
  fl.path = Zorasm_absolute_path(path);
  fl.file = Zorasm_get_file_extract(fl.path);
  fl.name = Zorasm_get_file_name(fl.file);
  fl.ext = Zorasm_get_file_ext(fl.file);
  fl.src = Zorasm_load_file_content(fl.path);

  if (!fl.src) {
  #if ZORASM_LOG
    printf("ERROR: Unable to read from file : `%s`\n\n", path);
  #endif
  fl.len = -1;
    return fl;
  }

  fl.len = strlen(fl.src);

  return fl;
}

#endif
