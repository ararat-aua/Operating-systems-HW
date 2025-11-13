#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_numbers(void* args){
	int id = *(int*)args;
	for(int i = 0; i < 5; i++){
		printf("Thread %d: %d\n", id, i+1);
	}
	return NULL;
}

int main(){
	pthread_t tids[3];
	int ids[] = {1, 2, 3};
	for(int i = 0; i < 3; i++){
		if(pthread_create(tids+i, NULL, print_numbers, ids+i) != 0){
			perror("Failed with creating thread");
			return 1;
		}
	}
	for(int i = 0; i < 3; i++){
		if(pthread_join(*(tids+i), NULL)!=0){
			perror("Failed with joining thread");
			return 1;
		}
	}
	return 0;

}
