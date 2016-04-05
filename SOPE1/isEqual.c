#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "simp_file.h"

int read_simp_files(const char **file, struct simp_file files, int *size){

	FILE* fp;

	if ((fp = fopen(file, "r")) == NULL)
	{ // Open source file.
		perror("fopen source-file");
		return 1;
	}

	*size = 0;
	char* buf;
	buf = (char*) malloc(1024);
	while (fgets(buf, 1024, fp) != NULL){
		
		
		buf[strlen(buf) - 1] = '\0';			// deletes the newline that fgets() stores
		files[*size].path = (char *)malloc(strlen(buf));
		strcpy(files[*size].path, buf);


		if(fgets(buf, 1024, fp) != NULL){		//gets name
			buf[strlen(buf) - 1] = '\0';		// deletes the newline that fgets() stores
			files[*size].name = (char *)malloc(strlen(buf));
			strcpy(files[*size].name, buf);
		} else {
			fclose(fp);
			return 1;
		}

		if(fgets(buf, 1024, fp) != NULL){		//gets size
			buf[strlen(buf) - 1] = '\0';		// deletes the newline that fgets() stores
			files[*size].size = (char *)malloc(strlen(buf));
			strcpy(files[*size].size, buf);
		} else {
			fclose(fp);
			return 1;
		}


		if(fgets(buf, 1024, fp) != NULL){		//gets permissions
			buf[strlen(buf) - 1] = '\0';		// deletes the newline that fgets() stores
			files[*size].permissions = (char *)malloc(strlen(buf));
			strcpy(files[*size].permissions, buf);
		} else {
			fclose(fp);
			return 1;
		}

		if(fgets(buf, 1024, fp) != NULL){		//gets date
			buf[strlen(buf) - 1] = '\0';		// deletes the newline that fgets() stores
			files[*size].date = atol(buf);
		} else {
			fclose(fp);
			return 1;
		}

		if(fgets(buf, 1024, fp) == NULL) return 1;	//gets the last newline

		(*size)++;								//increments size of "vector"
	}
	fclose(fp);
	return 0;
}

int main(){
	struct simp_file *files;
	int size;
	read_simp_files("files.txt", &files, &size);
	int i = 0;
	for (i = 0; i< size; i++){
		printf("%s\n",files[i].path);
		printf("%s\n",files[i].name);
		printf("%s\n",files[i].size);
		printf("%s\n",files[i].permissions);
		printf("%ld\n",files[i].date);
	}
}



