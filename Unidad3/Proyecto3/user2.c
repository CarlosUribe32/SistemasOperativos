#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <errno.h>

#define SH_SIZE 50
sem_t *sem1, *sem2, *sem1_2, *sem2_2;
int shm_fd1, shm_fd2;
void* map1;
void* map2;

void *lectura(){
    char* ptr;
    while (1){
        //Cerramos nosotros el candado
        if(sem_wait(sem1)==-1){
            perror("sem_wait: ");
            exit(EXIT_FAILURE);
        }
        //Mapeamos
        map1 = mmap(NULL, SH_SIZE, PROT_READ, MAP_SHARED, shm_fd1, 0);
        if (map1 == MAP_FAILED) {
            perror("Mapping failed escritura: ");
            exit(EXIT_FAILURE);
        }
        ptr = (char*)map1;
        if(map1==NULL){
            return 0;
        }
        fprintf(stdout, "User 1: %s", ptr);
        //Desmapeamos
        if (munmap(ptr, SH_SIZE) < 0) {
            perror("Unmapping failed escritura: ");
            exit(EXIT_FAILURE);
        }
        //Abrimos el candado
        if(sem_post(sem1_2)==-1){
            perror("pSemPost sem_post error lectura ");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
void *escritura(){
    char* ptr;
    char buf[SH_SIZE];
    printf("Ingrese ^D si quiere salir del chat\n");
    while (1){
        //Mapeamos
        map2 = mmap(NULL, SH_SIZE, PROT_WRITE, MAP_SHARED, shm_fd2, 0);
        if (map2 == MAP_FAILED) {
            perror("Mapping failed escritura: ");
            exit(EXIT_FAILURE);
        }
        ptr = (char*)map2;
        if(fgets(buf, SH_SIZE, stdin) == NULL)
            break;
        for (int i = 0; i < SH_SIZE; i++){
            ptr[i] = buf[i];
        }

        //Desmapeamos
        if (munmap(ptr, SH_SIZE) < 0) {
            perror("Unmapping failed escritura: ");
            exit(EXIT_FAILURE);
        }
        //Abrimos el candado
        if(sem_post(sem2)==-1){
            perror("pSemPost sem_post error escritura: ");
            exit(EXIT_FAILURE);
        }
        //Cerramos nosotros el candado
        if(sem_wait(sem2_2)==-1){
            perror("sem_wait: ");
            exit(EXIT_FAILURE);
        }
    }
    apagarSemaforos();
    cerrarEspaciosMemoria();
    return 0;
}

void prenderSemaforos(){
    //Abrimos los semaforos
    sem1 = sem_open("semaforo1-2", 0); 
    while(sem1== SEM_FAILED){
        sleep(1); //Mimase un rato
        sem1 = sem_open("semaforo1-2", 0); 
    }
    sem2 = sem_open("semaforo2-1", 0); 
    if(sem2== SEM_FAILED){
        //Creamos el semaforo
        mode_t perms = 0666;
        int flags = O_CREAT;
        unsigned int value =0; //Tener el semaforo cerrado
        sem2 = sem_open("semaforo2-1", flags, perms, value);
        if(sem2 == SEM_FAILED){
            perror("Usuario1 sem2_open: ");
            exit(EXIT_FAILURE);
        }
    }
    sem1_2 = sem_open("semaforo1-2_2", 0); 
    while(sem1_2== SEM_FAILED){
        sleep(1); //Mimase un rato
        sem1_2 = sem_open("semaforo1-2_2", 0); 
    }
    sem2_2 = sem_open("semaforo2-1_2", 0); 
    if(sem2_2== SEM_FAILED){
        //Creamos el semaforo
        mode_t perms = 0666;
        int flags = O_CREAT;
        unsigned int value =0; //Tener el semaforo cerrado
        sem2_2 = sem_open("semaforo2-1_2", flags, perms, value);
        if(sem2_2 == SEM_FAILED){
            perror("Usuario1 sem2_2_open: ");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

void apagarSemaforos(){
    //Cerramos el semaforo 2
    if(sem_close(sem2)==-1){
        perror("user2 sem_close fails: ");
        exit(EXIT_FAILURE);
    }
    if(sem_close(sem2_2)==-1){
        perror("user2 sem_close fails: ");
        exit(EXIT_FAILURE);
    }
    //Destruimos el semaforo 2
    if(sem_unlink("semaforo2-1")==-1){
        perror("user2 sem_unlink fails: ");
        exit(EXIT_FAILURE);
    }
    if(sem_unlink("semaforo2-1_2")==-1){
        perror("user2 sem_unlink fails: ");
        exit(EXIT_FAILURE);
    }
    return 0;
}
void abrirEspaciosMemoria(){
    //Abrimos los espacios en memoria
    shm_fd1 = shm_open("shm1-2", O_RDWR, 0600);
    if (shm_fd1 < 0) {
        shm_fd1 = shm_open("shm1-2", O_CREAT | O_RDWR, 0600);
        if (shm_fd1 < 0) {
            perror("shm1-2 memory error: ");
            exit(EXIT_FAILURE);
        }
        if (ftruncate(shm_fd1, SH_SIZE * sizeof(char)) < 0) {
            perror("shm1-2 Truncation failed: ");
            exit(EXIT_FAILURE);
        }
    }
    shm_fd2 = shm_open("shm2-1", O_RDWR, 0600);
    if (shm_fd2 < 0) {
        shm_fd2 = shm_open("shm2-1", O_CREAT | O_RDWR, 0600);
        if (shm_fd2 < 0) {
            perror("shm2-1 memory error: ");
            exit(EXIT_FAILURE);
        }
        if (ftruncate(shm_fd2, SH_SIZE * sizeof(char)) < 0) {
            perror("shm2-1 Truncation failed: ");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
void cerrarEspaciosMemoria(){
    if (close(shm_fd2) < 0) {
        perror("Closing shm failed: ");
        exit(EXIT_FAILURE);
    }

    if (shm_unlink("shm2-1") < 0) {
        perror("Unlink failed: ");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int main(void){
    //Inicializamos los hilos
    pthread_t hilo1, hilo2;

    prenderSemaforos();
    abrirEspaciosMemoria();
    
    pthread_create(&hilo1, NULL, &escritura, NULL);
    pthread_create(&hilo2, NULL, &lectura, NULL);
    
    //Esperamos solo el hilo de escritura
    pthread_join (hilo1, NULL);
    return 0;
}