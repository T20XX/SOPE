#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "aux.h"

int main(int argc, char *argv[]) {
  DIR *dirp;
  struct dirent *direntp;
  struct stat stat_buf;
  char *str;
  char *cur_path;
  char *files_txt_path;
  pid_t father;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <dir name>\n", argv[0]);
    exit(1);                                                // terminates the program with code 1
  }

  if ((dirp = opendir(argv[1])) == NULL) {
    perror(argv[1]);
    exit(2);
  }

father = getpid();              // o pid do processo pai




  chdir(argv[1]);                                          // make the dir the current directory

cur_path = getcwd(NULL, 0);				//sets current path
files_txt_path = (char *)malloc(strlen(cur_path) + strlen("files.txt") + 1);
strcpy(files_txt_path, cur_path);
strcat(files_txt_path, "/");
strcat(files_txt_path, "files.txt");			//sets files.txt path
close(open(files_txt_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR));//clears files.txt

while ((direntp = readdir(dirp)) != NULL) {              // read each entry in the directory
    if (lstat(direntp->d_name, &stat_buf)==-1) {           // get entry data with lstat
      perror("lstat");
      exit(3);
    }
    if (S_ISREG(stat_buf.st_mode)){
	write_regular_file(files_txt_path, cur_path, direntp->d_name, stat_buf);
      	str = "regular";
	}
    else if (S_ISDIR(stat_buf.st_mode)){
      str = "directory";
	if(strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0){
	pid_t pid;
  
  	pid = fork();
  	if (pid > 0) {                  // processo pai

  	}
  	if (pid == 0) {                 // filho 
    		if ((dirp = opendir(direntp->d_name)) == NULL) {
    			perror(direntp->d_name);
    			exit(2);
  		}
		chdir(direntp->d_name);
		cur_path = getcwd(NULL, 0);
		printf("%s \n", direntp->d_name);
  	}
}
	}
    else
      str = "other";
    printf("%-25s - %10lu %10lu %s\n", direntp->d_name, stat_buf.st_ino, stat_buf.st_size, str);
  }
  free(cur_path);
  closedir(dirp);
  exit(0);
}
