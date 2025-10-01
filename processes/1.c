#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	if (!fork()){
		printf("Child process: pid %d\n", getpid());
		exit(0);
	}
	printf("Parent process: pid %d\n", getpid());
	return 0;
}
