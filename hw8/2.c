#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int fd;
	int size;

	if((fd = open("data.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644))==-1){
		perror("Open");
		exit(1);
	}
	const char *str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if(write(fd, str, strlen(str))==-1){
		perror("Write");
		exit(1);	
	}
	if(close(fd)==-1){
		perror("Close");
		exit(1);
	}
	if((fd=open("data.txt", O_RDWR))==-1){
		perror("Open");
		exit(1);
	}
	if((size=lseek(fd, 0, SEEK_END))==-1){
		perror("Lseek");
		exit(1);
	}
	printf("Current size: %d\n", size);
	if(ftruncate(fd, 10)==-1){
		perror("Ftruncate");
		exit(1);
	}
	if((size=lseek(fd, 0, SEEK_END))==-1){
		perror("Lseek");
		exit(1);
	}
	printf("Size after truncating: %d\n", size);

	if(lseek(fd, 0, SEEK_SET)==-1){
		perror("Lseek");
		exit(1);	
	}
	
	char buf[11];
	int n_read;
	if((n_read=read(fd, buf, 10)) == -1){
		perror("Read");
		exit(1);
	}
	buf[n_read] = '\0';
	printf("Remaining content: %s\n", buf);
	if (close(fd) == -1){
		perror("Close");
		exit(1);
	}
	return 0;
}
