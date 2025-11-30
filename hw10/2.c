#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#define N_THREADS 10
#define N_ITERATIONS 10000

long long int balance = 0;
pthread_mutex_t mutex;
pthread_spinlock_t spinlock;
typedef struct {
	bool is_mutex;
	bool is_long;
} setting_t;

void *deposit(void *arg){
	setting_t* settings = (setting_t*)arg;
	bool is_mutex = settings->is_mutex;
	bool is_long = settings->is_long;
	if(is_mutex){
		for(int i=0; i<N_ITERATIONS; i++){
			pthread_mutex_lock(&mutex);
			balance++;
			if (is_long){
				usleep(1);
			}
			pthread_mutex_unlock(&mutex);
		}
	} 
	else{
		for(int i=0; i<N_ITERATIONS; i++){
                        pthread_spin_lock(&spinlock);
                        balance++;
                        if (is_long){
                                usleep(1);
			//	printf("Balance: %lld | iteration: %d\n", balance, i);
			}
                        pthread_spin_unlock(&spinlock);
                }	
	}
	return NULL;
}

void *withdraw(void *arg){
        setting_t* settings = (setting_t*)arg;
        bool is_mutex = settings->is_mutex;
        bool is_long = settings->is_long;
	
        if(is_mutex){
                for(int i=0; i<N_ITERATIONS; i++){
                        pthread_mutex_lock(&mutex);
                        balance--;
                        if (is_long){
                                usleep(1);
			}
                        pthread_mutex_unlock(&mutex);
                }
        }
        else{
                for(int i=0; i<N_ITERATIONS; i++){
                        pthread_spin_lock(&spinlock);
                        balance--;
                        if (is_long){
                                usleep(1);
			//	printf("Balance: %lld | iteration: %d\n", balance, i);
			}
                        pthread_spin_unlock(&spinlock);
                }
        }
        return NULL;
}

int main(int argc, char* argv[]){
	if(argc!=3){
		printf("Two additional arguments should be passed: mutex/spinlock, short/long\n");
		exit(1);
	}
	setting_t settings;
	if(strcmp(argv[1], "mutex")==0){
		settings.is_mutex=true;
	}
	else if(strcmp(argv[1], "spinlock")==0){
		settings.is_mutex=false;
	}
	else{
		printf("Inconsistent value for arguemnt 1: need to be either mutex or spinlock\n");
		exit(1);
	}
	
	if(strcmp(argv[2], "short")==0){
		settings.is_long=false;
	}
	else if(strcmp(argv[2], "long")==0){
		settings.is_long=true;
	}
	else{
		printf("Inconsistent value for argument 2: need to be either short or long\n");
		exit(1);
	}

	printf("is_mutex: %d, is_long: %d\n", (int)settings.is_mutex, (int)settings.is_long);
		
	pthread_t tid_dep[N_THREADS];
	pthread_t tid_wit[N_THREADS];
	pthread_mutex_init(&mutex, NULL);
	pthread_spin_init(&spinlock, 0);

	struct timeval start, end;
	gettimeofday(&start, NULL);
	for(int i=0; i<N_THREADS; i++){
		if(pthread_create(tid_dep+i, NULL, deposit, (void*)&settings)!=0){
			perror("Failed with creating threads");
			exit(1);
		}
		if(pthread_create(tid_wit+i, NULL, withdraw, (void*)&settings)!=0){
			perror("Failed with creating threads");
			exit(1);
		}
	}
	for(int i=0; i<N_THREADS; i++){
		if(pthread_join(tid_dep[i], NULL)!=0){
			perror("Failed with joining threads");
			exit(1);
		}
		if(pthread_join(tid_wit[i], NULL)!=0){
			perror("Failed with joining threads");
			exit(1);
		}
	}
	gettimeofday(&end, NULL);
	pthread_mutex_destroy(&mutex);
	pthread_spin_destroy(&spinlock);

	double execution_time = (end.tv_sec - start.tv_sec) * 1000.0;
	execution_time += (end.tv_usec - start.tv_usec) / 1000.0;
	printf("Time: %.2f ms\n", execution_time);
	printf("Balance: %lld\n", balance);
	return 0;
}
