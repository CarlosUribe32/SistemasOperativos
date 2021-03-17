#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    mode_t perms = 0666;
    int flags = O_CREAT;

    unsigned int value =0; //Tener el semaforo cerrado
    sem_t *sem = sem_open("semExample", flags, perms, value);

    if(sem == SEM_FAILED){
        perror("pSemCreate sem_open: ");
        exit(EXIT_FAILURE);
    }
    //Solo vamos a cerrar el cemaforo, no destruirlo
    if(sem_close(sem)==-1){
        perror("pSemCreate sem_close: ");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}