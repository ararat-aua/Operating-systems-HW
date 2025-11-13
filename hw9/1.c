#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* print_thread_message(void *args){
	pthread_t tid = pthread_self();
	printf("Thread %ld is running!\n", tid);
	return NULL;
}

int main(){
	pthread_t tid1, tid2, tid3;
	if(pthread_create(&tid1, NULL, print_thread_message, NULL) != 0){
		perror("Failed to create thread 1");
	      	return 1;	
	}
	if(pthread_create(&tid2, NULL, print_thread_message, NULL) != 0){
                perror("Failed to create thread 2");
                return 1;
        }
	if(pthread_create(&tid3, NULL, print_thread_message, NULL) != 0){
                perror("Failed to create thread 3");
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
	if(pthread_join(tid3, NULL) != 0){
                perror("Failed to join thread 3");
                return 1;
        }
	return 0;
}
