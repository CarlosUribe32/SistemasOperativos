#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 100
#define LOOPS 1000000
pthread_mutex_t mymutex;
long sum =0;

void * doWork(void *pdadta){
    long i;
    for( i=0; i<LOOPS; i++){
        pthread_mutex_lock(&mymutex);
        sum = sum + 1;
        pthread_mutex_unlock(&mymutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char * argv[]){
    pthread_mutex_init (&mymutex,NULL);
    pthread_t threads[NTHREADS];

    for(int i = 0; i<NTHREADS; i++)
        pthread_create(&threads[i], NULL, doWork, NULL);
    
    for(int i =0; i<NTHREADS; i++)
        pthread_join(threads[i], NULL);
    
    printf("Thread sum: %ld\n",sum);
    sum =0;
    for(int i =0; i<NTHREADS*LOOPS;i++)
        sum = sum + 1;
    printf("Check sum: %ld", sum);
    pthread_mutex_destroy(&mymutex);
    pthread_exit(NULL);
}