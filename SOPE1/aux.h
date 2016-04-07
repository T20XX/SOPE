#ifndef AUX_H
#define AUX_H

int write_regular_file(char *path, char *cur_path, char *name, struct stat stat_file);

int long_toString(long l, char **string);

int permissions_toString(mode_t mode,char permissions[9]);


#endif
