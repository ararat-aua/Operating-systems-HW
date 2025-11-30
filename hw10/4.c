#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define N 8
sem_t sem_A, sem_B, sem_C;
pthread_mutex_t mutex;

void* thread_A(void *){
    for(int i=0; i<N; i++){
        sem_wait(&sem_A);
        pthread_mutex_lock(&mutex);
        printf("A: %d\n", i);
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_B);
    }
    return NULL;
}
void* thread_B(void *){
    for(int i=0; i<N; i++){
        sem_wait(&sem_B);
        pthread_mutex_lock(&mutex);
        printf("B: %d\n", i);
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_C);
    }
    return NULL;
}
void* thread_C(void *){
    for(int i=0; i<N; i++){
        sem_wait(&sem_C);
        pthread_mutex_lock(&mutex);
        printf("C: %d\n", i);
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_A);
    }
    return NULL;
}

int main(){
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem_A, 0, 1);
    sem_init(&sem_B, 0, 0);
    sem_init(&sem_C, 0, 0);

    pthread_t tid_A, tid_B, tid_C;
    if(pthread_create(&tid_A, NULL, thread_A, NULL)!=0){
        perror("Failed creating thread");
        exit(1);
    }
    if(pthread_create(&tid_B, NULL, thread_B, NULL)!=0){
        perror("Failed creating thread");
        exit(1);
    }
    if(pthread_create(&tid_C, NULL, thread_C, NULL)!=0){
        perror("Failed creating thread");
        exit(1);
    }
    
    if(pthread_join(tid_A, NULL)!=0){
        perror("Failed joining thread");
        exit(1);
    }
    if(pthread_join(tid_B, NULL)!=0){
        perror("Failed joining thread");
        exit(1);
    }
    if(pthread_join(tid_C, NULL)!=0){
        perror("Failed joining thread");
        exit(1);
    }

    sem_destroy(&sem_A);
    sem_destroy(&sem_B);
    sem_destroy(&sem_C);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}

