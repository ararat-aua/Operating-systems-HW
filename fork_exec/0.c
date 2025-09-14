#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void call_fork(int n){
	int space_size = n*8+1;
	char space[space_size];
	int i=0;
	for(; i<space_size-1; i++){
		space[i] = ' ';
	}
	space[i] = '\0';


	pid_t pid = fork();
	if(pid == -1){
		exit(0);
	}
	else if (pid != 0){
		wait(NULL);
	}
	else{
		printf("%s%d->%d\n", space, getppid(), getpid());
	}
}

int main(){
	
	int n = 3;
	for (int i=0; i<n; i++){
		call_fork(i);
	}
	return 0;
}
