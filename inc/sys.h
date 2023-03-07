#ifndef _ZORA_SYS_H
#define _ZORA_SYS_H

#include <stdio.h>

typedef struct {
  char *argfile;
  char *path;
  char *file;
  char *name;
  char *ext;
  char *src;
  int len;
} Zora_file_t;

void Zora_sys_exec(char *command);
char *Zora_absolute_path(char *path);
char *Zora_filereader(char *path);
Zora_file_t Zora_file_obj(char *path);
char *Zora_load_file_content(char *path);
long long Zora_filesize_from_fp(FILE *fp);
char *Zora_get_file_extract(char *file);
char *Zora_get_file_name(char *filepath);
char *Zora_get_file_ext(char *path);
long long Zora_filewriter(char *path, char *content);
char *Zora_load_file_content(char *path);
char *Zora_join_path(char *base, char *trail);

#endif
