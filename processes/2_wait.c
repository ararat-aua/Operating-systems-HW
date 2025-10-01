#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
	int status;
	pid_t pid_fork, pid_wait;
	pid_fork = fork();
	if (pid_fork==-1){
		fprintf(stderr, "Probelms with first fork()\n");
		return 1;
	} else if (pid_fork==0){
		printf("Child process %d that will exit with 1\n", getpid());
		exit(1);
	}
	pid_fork = fork();
	if (pid_fork==-1){
		fprintf(stderr, "Error with second fork()\n");
		return 1;
	} else if (pid_fork == 0){
		printf("Child process %d that will exit with 2\n", getpid());
		exit(2);
	}
	
	for (int i=0; i<2; i++){
		pid_wait = wait(&status);
		if (pid_wait == -1){
			fprintf(stderr, "Problem with wait()");
			return 1;
		}
		printf("Waited for child %d with exit status %d\n", pid_wait, WEXITSTATUS(status));
	}
	return 0;
}
