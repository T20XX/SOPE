#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "aux.h"

int write_regular_file(char *path, char *cur_path, char *name, struct stat stat_file){
	int file;
	char *pathname;
	char *size;
        char permissions[9];
	char *time;

	pathname = (char *)malloc(strlen(cur_path) + strlen(name) + 1);
	strcat(pathname, cur_path);
	strcat(pathname, "/");
	strcat(pathname, name);

	long_toString(stat_file.st_size, &size);
	permissions_toString(stat_file.st_mode, permissions);
	long_toString(stat_file.st_ctime, &time);

        file = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

	write(file, pathname, strlen(pathname));
	write(file, "\n",1);
	write(file, name, strlen(name));
	write(file, "\n",1);
 	write(file, size, strlen(size));
	write(file, "\n",1);
        write(file, permissions, 9);
	write(file, "\n",1);
	write(file, time, strlen(time));
	write(file, "\n\n",2);

        close(file);

	return 0;
}

//Converts file permissions to string of type: "RWXRWXRWX" or "---------"
int permissions_toString(mode_t mode, char permissions[9]){
	for (int i = 0; i < 9; i++){
		permissions[i] = '-';
	}

	if (mode & S_IRUSR) permissions[0] = 'R';		//USER PERMISSIONS BITS
	if (mode & S_IWUSR) permissions[1] = 'W';
 	if (mode & S_IXUSR) permissions[2] = 'X';

	if (mode & S_IRGRP) permissions[3] = 'R';		//GROUP PERMISSIONS BITS
	if (mode & S_IWGRP) permissions[4] = 'W';
 	if (mode & S_IXGRP) permissions[5] = 'X';

	if (mode & S_IROTH) permissions[6] = 'R';		//OTHER PERMISSIONS BITS
	if (mode & S_IWOTH) permissions[7] = 'W';
 	if (mode & S_IXOTH) permissions[8] = 'X';

	return 0;
}

int long_toString(long l, char **string){
	*string = (char *)malloc(l);
	sprintf(*string, "%ld",l);
	return 0;
}
