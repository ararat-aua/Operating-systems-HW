#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void custom_wait(int *status, pid_t pid){
	if (waitpid(pid, status, 0) == -1){
		fprintf(stderr, "Problem with waiting %d\n", pid);
		return 1
	}
	printf("Successfully waited for child %d with exit status %d\n", pid, WEXITSTATUS(*status));
}

int main(void){
    pid_t pid_1, pid_2;
    int status;

    pid_1 = fork();
    if (pid_1==-1){
    	fprintf(stderr, "Error with first fork()\n");
	return 1;
    } else if (pid_1==0){
    	printf("Child %d exiting with status 1\n", getpid());
	exit(1);
    }
    pid_2 = fork();
    if (pid_2==-1){
    	fprintf(stderr, "Error with second fork()\n");
	return 1;
    }
    else if (pid_2==0){
    	printf("Child %d exiting with status 2\n", getpid());
	exit(2);
    }
    custom_wait(pid_1, &status);
    cutoms_wait(pid_2, &status);
	   
    return 0;
}

