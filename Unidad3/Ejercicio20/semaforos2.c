#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

static long glob = 0;
pthread_mutex_t theMutex;

static void* threadFunc(void *arg) {
    int loops = *((int *) arg);
    long loc;
    
    for (int j = 0; j < loops; j++) {
        //Entramos a la region critica
        pthread_mutex_lock(&theMutex);
        loc = glob;
        loc++;
        glob = loc;
        //Salimos de la region critica
        pthread_mutex_unlock(&theMutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_mutex_init (&theMutex,NULL);
    pthread_t t1, t2;
    int loops, s;

    loops = (argc > 1) ? atol(argv[1]) : 10000000;
    
    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0) 
        perror("pthread create");
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0) 
        perror("pthread create");

    s = pthread_join(t1, NULL);
    if (s != 0) 
        perror("pthread_join");
       
    s = pthread_join(t2, NULL);
    if (s != 0) 
        perror("pthread_join");

    printf("glob = %ld\n", glob);
    pthread_mutex_destroy(&theMutex);
    exit(EXIT_SUCCESS);
}