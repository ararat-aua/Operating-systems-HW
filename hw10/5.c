#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define N 16
#define K_PRINTERS 4

sem_t semaphore;
pthread_mutex_t mutex;
// int shared_counter = 0;

void* printing_threads(void*) {
    sem_wait(&semaphore);
    // pthread_mutex_lock(&mutex);
    printf("Thread X is printing...\n");
    // printf("Simultaneous threads: %d\n", shared_counter);
    usleep(rand() % 500000 + 100000);
    // pthread_mutex_unlock(&mutex);
    int sem_val;
    sem_getvalue(&semaphore, &sem_val);
    printf("Simultanous threads: %d \n", K_PRINTERS-sem_val);
    sem_post(&semaphore);
}

int main(int argc, char *argv[]) {
    pthread_t th[N];
    sem_init(&semaphore, 0, K_PRINTERS);
    pthread_mutex_init(&mutex, NULL);
    int i;
    for (i = 0; i < N; i++) {
        if (pthread_create(&th[i], NULL, &printing_threads, NULL) != 0) {
            perror("Failed to create thread");
        }
    }

    for (i = 0; i < N; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semaphore);
    pthread_mutex_destroy(&mutex);
    return 0;
}
