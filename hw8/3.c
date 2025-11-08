#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char file_path[100];
	char buf[1];
	int fd;
	int size;

	printf("Enter file's path: ");
	scanf("%s", file_path);
	
	if((fd=open(file_path, O_RDONLY))==-1){
		perror("Open");
		exit(1);
	}
	if((size=lseek(fd, 0, SEEK_END))==-1){
		perror("Lseek");
		exit(1);
	}
	
	int pos = size-1;
	while(pos>=0){
		if(lseek(fd, pos, SEEK_SET)==-1){
			perror("Lseek");
			exit(1);
		}
		if(read(fd, buf, 1)==-1){
			perror("Read");
			exit(1);
		}
		if(write(1, buf, 1)==-1){
			perror("Write");
			exit(1);
		}
		pos--;
	}
	printf("\n");
	if(close(fd) == -1){
		perror("Close");
		exit(1);
	}
	return 0;
}
