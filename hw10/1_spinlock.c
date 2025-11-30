#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define M 10000
#define N 100

long long int counter=0;
pthread_spinlock_t spinlock;

void* worker(void*){
	for (int i=0; i<M; i++){
		pthread_spin_lock(&spinlock);
		counter++;
		pthread_spin_unlock(&spinlock);
	}
	return NULL;
}

int main(){
	pthread_t tid[N];
	pthread_spin_init(&spinlock, 0);
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
	pthread_spin_destroy(&spinlock);
	printf("Expected outcome: %llu\n", (long long int)M*N);
	printf("Real outcome: %llu\n", counter);
	return 0;
}
