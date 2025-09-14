#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid = fork();

	if (pid == 0){
		execl("/usr/bin/echo", "echo", "Hello from the child process!", NULL);
	}
	else {
		wait(NULL);
		printf("Parent process done!\n");
	}

	return 0;
}
