#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int write_regular_file(char *path, char *cur_path, char *name, struct stat stat_file);

int long_toString(long l, char **string);

int permissions_toString(mode_t mode,char permissions[9]);

int get_current_path(char **path);

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

int get_current_path(char **path){
	char *tmp;
	tmp = malloc(100000000);
	getcwd(tmp,10000);
	*path = malloc(strlen(tmp));
//printf("%s\n",tmp);	
	//while(strcmp(tmp, "/") != 0){
	printf("%s\n",tmp);
strcpy(*path,tmp);
		//*path = realloc(*pathstrlen(tmp));
		//strcat(*path, tmp);
		//chdir("..");
		//getcwd(tmp, 10);
	//}
printf("%s\n",*path);
	//chdir(*path);
	return 0;
}
