#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	pid_t pid = fork();
	int status;
	if (pid==-1){
		fprintf(stderr, "Problem with fork()\n");
		return 1;
	} else if (pid==0){
		printf("Here is the child process with pid %d\n", getpid());
		printf("Child process is exited with exit code 1\n");
		exit(1);
	}
	wait(&status);
	printf("Waited for child process to execute with exit code %d\n", WEXITSTATUS(status));
	printf("Parent process goint to sleep\n");
	sleep(10);
	return 0;
}
