#ifndef _ZORA_SYS_C
#define _ZORA_SYS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./sys.h"

void Zora_sys_exec(char *command) {
  FILE *fp = (FILE *)popen(command, "r");
  pclose(fp);
}

char *Zora_absolute_path(char *path) {
  const int MAXPATH = 260;
  return (char *)_fullpath(NULL, path, MAXPATH);
}

char *Zora_join_path(char *base, char *trail) {
  return (char *)strcat((char *)strcat(Zora_absolute_path(base), "/"), trail);
}

long long Zora_filesize_from_fp(FILE *fp) {
  fseek(fp, 0, SEEK_END);
  long long size = ftell(fp);
  rewind(fp);
  return size;
}

char *Zora_filereader(char *path) {
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

long long Zora_filewriter(char *path, char *content) {
  FILE *file = fopen(path, "w");
  if (!file) return -1;

  fprintf(file, "%s", content);
  long long size = Zora_filesize_from_fp(file);
  fclose(file);

  return size;
}

char *Zora_get_file_extract(char *file) {
  char *extract = (char *)strrchr((char *)strdup(file), '\\');

  if (!extract) extract = (char *)strrchr(extract, '/');
  if (extract) *extract = '\0';

  return (char *)++extract;
}

char *Zora_get_file_name(char *filepath) {
  return (char *)strtok((char *)strdup(filepath), ".");
}

char *Zora_get_file_ext(char *path) {
  char *ext = (char *)strrchr((char *)strdup(path), '.');
  if (!ext) return "";

  return (char *)++ext;
}

char *Zora_load_file_content(char *path) {
  char *content = Zora_filereader(path);
  return content;
}

Zora_file_t Zora_file_obj(char *path) {
  Zora_file_t fl =  {0};

  fl.argfile = path;
  fl.path = Zora_absolute_path(path);
  fl.file = Zora_get_file_extract(fl.path);
  fl.name = Zora_get_file_name(fl.file);
  fl.ext = Zora_get_file_ext(fl.file);
  fl.src = Zora_filereader(fl.path);

  if (!fl.src) {
  #if ZORA_LOG
    printf("ERROR: Unable to read from file `%s`\n", path);
  #endif
  fl.len = -1;
    return fl;
  }

  fl.len = strlen(fl.src);

  return fl;
}

#endif
