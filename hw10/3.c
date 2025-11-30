#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#define BUFFER_SIZE 8
#define P 10
#define C 10
#define K 100

int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;

int total_consumed = 0;

sem_t empty_slots;
sem_t full_slots;
pthread_mutex_t buffer_mutex;

void insert_item(){
	buffer[in_pos] = 1;
	in_pos = (in_pos+1)%BUFFER_SIZE;
}
void remove_item(){
	int item = buffer[out_pos];
        buffer[out_pos] = 0;
        out_pos = (out_pos+1)%BUFFER_SIZE;
	total_consumed += item;
}

void* producer(void*){
	for (int i = 0; i<K; i++){
		sem_wait(&empty_slots);
		pthread_mutex_lock(&buffer_mutex);
		insert_item();
		pthread_mutex_unlock(&buffer_mutex);
		sem_post(&full_slots);
	}
	return NULL;
}

void* concumer(void*){
	for (int i = 0; i<K; i++){
		sem_wait(&full_slots);
		pthread_mutex_lock(&buffer_mutex);
		remove_item();
		pthread_mutex_unlock(&buffer_mutex);
		sem_post(&empty_slots);
	}
	return NULL;
}


int main(){
	pthread_t producers[P];
	pthread_t concumers[C];	
	sem_init(&empty_slots, 0, BUFFER_SIZE);
	sem_init(&full_slots, 0, 0);
	pthread_mutex_init(&buffer_mutex, NULL);
	
	for(int i=0; i<P; i++){
		if(pthread_create(producers+i, NULL, producer, NULL)!=0){
			perror("Failed to create a thread");
			exit(1);
		}
	}
	for(int i=0; i<C; i++){
			if(pthread_create(concumers+i, NULL, concumer, NULL)!=0){
					perror("Failed to create a thread");
					exit(1);
			}
	}

	for(int i=0; i<P; i++){
		if(pthread_join(producers[i], NULL)!=0){
			perror("Failed to join a thread");
			exit(1);
		}
	}
	for(int i=0; i<C; i++){
		if(pthread_join(concumers[i], NULL)!=0){
			perror("Failed to join a thread");
			exit(1);
		}
	}
	pthread_mutex_destroy(&buffer_mutex);
	sem_destroy(&empty_slots);
	sem_destroy(&full_slots);

	printf("Expected consumption number: %d\n", P*K);
	printf("Real consumption number: %d\n", total_consumed);
	return 0;
}



