#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "aux.h"

int hardlinker(Simp_file *files, int size){

	int i, j;
	for(i = 0; i < size; i++){
		for(j = i; j < size; j++){
			if(strcmp(files[i].name, files[j].name) == 0){
				if(strcmp(files[i].permissions, files[j].permissions) == 0){
					//if(strcmp(files[i].size, files[j].size) == 0){
					//if(filecmp(files[i].path, files[j].path) == 0){
					struct stat stat_buf1;
					struct stat stat_buf2;

					ino_t ino1;
					ino_t ino2;

					if (lstat(files[i].path, &stat_buf1)==-1) {           // get entry data with lstat
					      perror("lstat");
					      exit(3);
					    }

					if (lstat(files[j].path, &stat_buf2)==-1) {           // get entry data with lstat
										      perror("lstat");
										      exit(3);
										    }

printf("%ld\n", stat_buf1.st_ino);
printf("%ld\n", stat_buf2.st_ino);


					if(files[i].date < files[j].date){
						stat_buf1.st_ino = stat_buf2.st_ino;

						//link(files[j].path, files[i].path);
					} else {

						stat_buf1.st_ino = stat_buf2.st_ino;

						//link(files[i].path, files[j].path);
					}
					//}
					//}
				}
			}
		}
	}
	return 0;
}

int filecmp(char* path1, char* path2){

	int des1, des2;

	des1 = open(path1, O_RDONLY);
	des2 = open(path2, O_RDONLY);

	char *buffer_1;
	char *buffer_2;
	buffer_1 = (char *)malloc(sizeof(char));
	buffer_2 = (char *)malloc(sizeof(char));

	do{
		if(read(des1, buffer_1,1)==0){
			if(read(des2, buffer_2,1) == 0){
			close(des1);
			close(des2);
			return 0;
			}
		}
		else if(read(des2, buffer_2,1) == 0){
			close(des1);
			close(des2);
			return 1;
			}

	}
	while(strcmp(buffer_1, buffer_2) == 0);
	close(des1);
	close(des2);
	return 1;
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

int write_regular_file(char *path, char *cur_path, char *name, struct stat stat_file){
    printf("%s\n",path);

	int file;
	char *pathname;
	char *size;
    char permissions[9];
	char *time;

    printf("%s\n",path);


	pathname = malloc(strlen(cur_path) + strlen(name) + 1);
    printf("%s\n",path);

	strcpy(pathname, cur_path);
	strcat(pathname, "/");
	strcat(pathname, name);

    printf("%s\n",path);

	long_toString(stat_file.st_size, &size);
	permissions_toString(stat_file.st_mode, permissions);
	long_toString(stat_file.st_ctime, &time);

        file = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
        printf("%s\n",path);

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
