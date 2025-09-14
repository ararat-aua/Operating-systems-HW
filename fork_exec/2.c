#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t cur_pid = getpid();
	pid_t pid = fork();
	if (pid==0){
		execl("/usr/bin/ls", "ls", NULL);
	}
	else{
		wait(NULL);
		pid = fork();
		if (pid==0){
			execl("/usr/bin/date", "date", NULL);
		}		
		else{
			wait(NULL);
			printf("Parent process done!\n");
		}
	}

	return 0;
}
