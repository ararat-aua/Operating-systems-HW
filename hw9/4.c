#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARR_SIZE 50
int arr[ARR_SIZE];

void* square(void* args){
	int id = *(int*)args;
	int num = arr[id];
	int num_sq = num*num;
	printf("Square of %d is %d\n", num, num_sq);
	return NULL;
}

int main(){
	for(int i = 0; i < ARR_SIZE; i++){
		arr[i] = i+1;
	}
	pthread_t tids[ARR_SIZE];
	int ids[ARR_SIZE];
	for(int i = 0; i < ARR_SIZE; i++){
		ids[i] = i;
	}
	for(int i = 0; i < ARR_SIZE; i++){
		if(pthread_create(tids+i, NULL, square, ids+i) != 0){
			perror("Failed with creating thread");
			return 1;
		}
	}
	for(int i = 0; i < ARR_SIZE; i++){
		if(pthread_join(*(tids+i), NULL) != 0){
			perror("Failed with joining thread");
			return 1;
		}
	}
	return 0;
}
