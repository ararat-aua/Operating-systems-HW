#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define M 10000
#define N 100

long long int counter=0;
pthread_mutex_t mutex;

void* worker(void*){
	for (int i=0; i<M; i++){
		pthread_mutex_lock(&mutex);
		counter++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(){
	pthread_t tid[N];
	pthread_mutex_init(&mutex, NULL);
	for (int i=0; i<N; i++){
		if(pthread_create(tid+i, NULL, worker, NULL)!=0){
			perror("Failed with thread creation");
			exit(1);
		}
	}

	for (int i=0; i<N; i++){
		if(pthread_join(tid[i], NULL)!=0){
			perror("Failed with thread join");
			exit(1);
		}
	}
	pthread_mutex_destroy(&mutex);
	printf("Expected outcome: %llu\n", (long long int)M*N);
	printf("Real outcome: %llu\n", counter);
	return 0;
}
