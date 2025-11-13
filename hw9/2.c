#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define ARR_SIZE 100
int arr[ARR_SIZE];

void* calculate_sum(void *args){;
	int id = *(int*)args;
	int sum = 0;

	for (int i = (id-1)*(ARR_SIZE/2); i < id*(ARR_SIZE/2); i++){
		sum += arr[i];
	}	
	printf("Thread %d sum: %d\n", id, sum);
	return NULL;
}

int main(){
	for (int i = 0; i < ARR_SIZE; i++){
                arr[i] = 1;
        }
	pthread_t tid1, tid2;
	int id1 = 1;
       	int id2 = 2;
	if(pthread_create(&tid1, NULL, calculate_sum, (void*)&id1) != 0){
		perror("Failed to create thread 1");
		return 1;
	}
	if(pthread_create(&tid2, NULL, calculate_sum, (void*)&id1) != 0){
                perror("Failed to create thread 2");
                return 1;
        }
	if(pthread_join(tid1, NULL) != 0){
		perror("Failed to join thread 1");
		return 1;
	}
	if(pthread_join(tid2, NULL) != 0){
		perror("Failed to join thread 2");
		return 1;
	}
	return 0;

}
