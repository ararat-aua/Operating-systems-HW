#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


/*
 With O_APPEND file the position is not placed at the beginning but at the end, that's why the content is appeded
 and position is growing.
 */
int main(){
	int fd;
	if((fd=open("log.txt", O_WRONLY|O_CREAT|O_APPEND, 0644))==-1){
		perror("Open");
		exit(1);
	}
	pid_t pid = getpid();
	if(pid==-1){
		perror("Getpid");
		exit(1);
	}
	const char* pid_prefix = "PID=";
	if(write(fd, pid_prefix, strlen(pid_prefix))==-1){
		perror("Write");
		exit(1);
	}
	
	char pid_digits[10];
	int pid_len = 0;
	while(pid>0){
		pid_digits[pid_len] = (char)(pid%10)+'0';
		pid = pid/10;
		pid_len++;
	}
	for(int i=pid_len-1; i>=0; i--){
		if(write(fd, pid_digits+i, 1)==-1){
			perror("Write");
			exit(1);
		}
	}
	const char* pid_postfix = ": ";
	if(write(fd, pid_postfix, strlen(pid_postfix))==-1){
		perror("Write");
		exit(1);
	}
	char input[500];
	int n_rd = read(0, input, sizeof(input));
	if(n_rd==-1){
		perror("Write");
		exit(1);	
	}
	if(write(fd, input, n_rd)==-1){
		perror("Write");
		exit(1);
	}
	int pos = lseek(fd, 0, SEEK_CUR);
	if(pos==-1){
		perror("Lseek");
		exit(1);
	}
	printf("File position: %d\n", pos);
	if (close(fd)==-1){
		perror("Close");
		exit(1);
	}
	return 0;
}
