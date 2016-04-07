#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "simp_file.h"

//struct Simp_file;

int read_simp_files(const char *file, Simp_file **files, int *size){

	FILE* fp;

	if ((fp = fopen(file, "r")) == NULL)
	{ // Open source file.
		perror("fopen source-file");
		return 1;
	}

	*size = 0;

	Simp_file *tmp;
	*files = NULL;//malloc(sizeof(struct simp_file));

	char* buf;
	buf = (char*) malloc(1024);
	while (fgets(buf, 1024, fp) != NULL){

		tmp = realloc(*files,sizeof(Simp_file) * ((*size) + 1));

		if(tmp != NULL){						//Tests if reallocation of memory went fine
			*files = tmp;
		} else {
			printf("Reallocation of memory failed.\n");
			break;
		}

		buf[strlen(buf) - 1] = '\0';			// deletes the newline that fgets() stores
		(*files)[*size].path = (char *)malloc(strlen(buf));
		strcpy((*files)[*size].path, buf);


		if(fgets(buf, 1024, fp) != NULL){		//gets name
			buf[strlen(buf) - 1] = '\0';		// deletes the newline that fgets() stores
			(*files)[*size].name = (char *)malloc(strlen(buf));
			strcpy((*files)[*size].name, buf);
		} else {
			fclose(fp);
			return 1;
		}

		if(fgets(buf, 1024, fp) != NULL){		//gets size
			buf[strlen(buf) - 1] = '\0';		// deletes the newline that fgets() stores
			(*files)[*size].size = (char *)malloc(strlen(buf));
			strcpy((*files)[*size].size, buf);
		} else {
			fclose(fp);
			return 1;
		}


		if(fgets(buf, 1024, fp) != NULL){		//gets permissions
			buf[strlen(buf) - 1] = '\0';		// deletes the newline that fgets() stores
			(*files)[*size].permissions = (char *)malloc(strlen(buf));
			strcpy((*files)[*size].permissions, buf);
		} else {
			fclose(fp);
			return 1;
		}

		if(fgets(buf, 1024, fp) != NULL){		//gets date
			buf[strlen(buf) - 1] = '\0';		// deletes the newline that fgets() stores
			(*files)[*size].date = atol(buf);
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



