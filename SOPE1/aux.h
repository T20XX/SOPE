#include "simp_file.h"

#ifndef AUX_H
#define AUX_H

int hardlinker(Simp_file *files, int size);

int filecmp(char* path1, char* path2);

int long_toString(long l, char **string);

int permissions_toString(mode_t mode,char permissions[9]);

int write_regular_file(char *path, char *cur_path, char *name, struct stat stat_file);

#endif
