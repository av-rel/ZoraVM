#ifndef SYS_C
#define SYS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>

typedef struct {
  char *path;
  char *file;
  char *name;
  char *ext;
  char *src;
  unsigned int len;
} file_t;

void sys_exec(char *command) {
  FILE *fp = (FILE *)popen(command, "r");
  pclose(fp);
}

char *absolute_path(char *path) {
  const int MAXPATH = 260;
  return (char *)_fullpath(NULL, path, MAXPATH);
}

char *fs_join_path(char *base, char *trail) {
  return (char *)strcat((char *)strcat(absolute_path(base), "/"), trail);
}

long long filesize_from_fp(FILE *fp) {
  fseek(fp, 0, SEEK_END);
  long long size = ftell(fp);
  rewind(fp);
  return size;
}

char *filereader(char *path) {
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

long long filewriter(char *path, char *content) {
  FILE *file = fopen(path, "w");
  if (!file)
    return -1;

  fprintf(file, "%s", content);
  long long size = filesize_from_fp(file);
  fclose(file);

  return size;
}

char *get_file_extract(char *file) {
  char *extract = (char *)strrchr((char *)strdup(file), '\\');

  if (!extract)
    extract = (char *)strrchr(extract, '/');
  if (extract)
    *extract = '\0';

  return (char *)++extract;
}

char *get_file_name(char *filepath) {
  return (char *)strtok((char *)strdup(filepath), ".");
}

char *get_file_ext(char *path) {
  char *ext = (char *)strrchr((char *)strdup(path), '.');
  if (!ext)
    return "";
  return (char *)++ext;
}

char *load_file_content(char *path, char* iferr) {
  char *content = filereader(path);
  if (content != NULL)
    return content;

  printf("%s", iferr);
  exit(0);

  return "";
}

file_t file_obj(char *path, char* iferr) {
  file_t fl = {0};

  fl.path = absolute_path(path);
  fl.file = get_file_extract(fl.path);
  fl.name = get_file_name(fl.file);
  fl.ext = get_file_ext(fl.file);
  fl.src = load_file_content(fl.path, iferr);

  return fl;
}

#endif
