#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int hardlinker(struct simp_file *files, int size){

	int i, j;
	for(i = 0; i < size; i++){
		for(j = i; j < size; j++){
			if(strcmp(files[i].name, files[j].name) == 0){
				if(strcmp(files[i].permissions, files[j].permissions) == 0){
					//if(strcmp(files[i].size, files[j].size) == 0){
					//if(filecmp(files[i].path, files[j].path) == 0){
					if(files[i].date < files[j].date){
						link(files[j].path, files[i].path);
					} else {
						link(files[i].path, files[j].path);
					}
					//}
					//}
				}
			}
		}
	}
} 

int filecmp(char* path_name_1, char* path_name_2){

	int des1, des2;

	des1 = open(path_name_1, O_RDONLY);
	des2 = open(path_name_2, O_RDONLY);

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
