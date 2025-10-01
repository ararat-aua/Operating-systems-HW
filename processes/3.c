#include <stdio.h>
#include <stdlib.h>

void f1(){
	printf("This is message from function 1\n");
}
void f2(){
	printf("This is message from function 2\n");
}

int main(){
	if (atexit(f1)){
		fprintf(stderr, "atexit() failed!\n");
	}
	//exit(0);
	if (atexit(f2)){
		fprintf(stderr, "atexit() failed!\n");
	}

	exit(0);
}
