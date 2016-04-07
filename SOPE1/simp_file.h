#ifndef AUX_H
#define AUX_H

typedef struct _Simp_file{
	char* path;
	char* name;
	char* size;
	char* permissions;
	time_t date;
}Simp_file;

int read_simp_files(const char *file, Simp_file **files, int *size);

#endif
