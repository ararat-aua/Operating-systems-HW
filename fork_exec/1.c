#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int ret;
	printf("Before fork\n");
	pid_t pid = fork();
	if (pid==-1){
		exit(1);
	}
	if (pid == 0){
		ret = execl("/usr/bin/ls", "ls", NULL);
	}
	else {
		wait(NULL);
		printf("Parent process done!\n");
	}
	return 0;
}
