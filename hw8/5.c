#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


/*
 Apparent size is 1048584 while disk usage is 8.
 As we don't write zeros manually and just skip forward
 thus creating "holes", filesystem does not allocate blocks for the skipped region.
 * */
int main(){
	int fd;
	const char *start = "START";
	const char *end = "END";
	if((fd=open("sparse.bin", O_WRONLY|O_CREAT|O_TRUNC, 0644))==-1){
		perror("Open");
		exit(1);
	}
	if(write(fd, start, strlen(start))==-1){
		perror("Write");
		exit(1);
	}
	if(lseek(fd, strlen(start)+1024*1024, SEEK_SET)==-1){
		perror("Lseek");
		exit(1);
	}
	if(write(fd, end, strlen(end))==-1){
		perror("Write");
		exit(1);
	}
	if(close(fd)==-1){
		perror("Close");
		exit(1);
	}
	
	if((fd=open("sparse.bin", O_RDONLY))==-1){
		perror("Close");
		exit(1);
	}
	int size;
	if((size=lseek(fd, 0, SEEK_END))==-1){
		perror("Lseek");
		exit(1);
	}
	printf("Apparent file size: %d\n", size);
	if(close(fd)==-1){
		perror("Close");
		exit(1);
	}

	return 0;
}
