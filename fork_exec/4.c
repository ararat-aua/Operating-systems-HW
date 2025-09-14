#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main (){
	pid_t pid = fork();
	if (pid==0){
		execl("/usr/bin/grep", "grep", "main", "test.txt", NULL);
	}
	else {
		wait(NULL);
		printf("Parent process completed!\n");
	}
	return 0;
}
