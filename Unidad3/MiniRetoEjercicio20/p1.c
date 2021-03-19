#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct{
    char nombre[20];
    char ocupacion[20];
    int edad;
}fila;

void ordenAlfabetico(fila *pFila, FILE * on_file, int cont){
    //ordenamos por QuickSort
    quicksort(pFila, 0, cont-1);
    for (int i = 0; i < cont; i++)
    {
        fprintf(on_file, "%s %s %d\n", pFila[i].nombre, pFila[i].ocupacion, pFila[i].edad);
    }
    return NULL;
}

//Implementacion del QuickSort 
void intercambiar(fila *a, fila *b) {
  fila temporal = *a;
  *a = *b;
  *b = temporal;
}
void quicksort(fila * arreglo, int izquierda, int derecha) {
  if (izquierda < derecha) {
    int indiceParticion = particion(arreglo, izquierda, derecha);
    quicksort(arreglo, izquierda, indiceParticion);
    quicksort(arreglo, indiceParticion + 1, derecha);
  }
}
int particion(fila * arreglo, int izquierda, int derecha) {
  fila pivote = arreglo[izquierda];
  while (1) {
    while (strcmp(arreglo[izquierda].nombre, pivote.nombre) < 0) {
      izquierda++;
    }
    while (strcmp(arreglo[derecha].nombre, pivote.nombre) > 0) {
      derecha--;
    }
    if (izquierda >= derecha) {
      return derecha;
    } 
    else {
      intercambiar(&arreglo[izquierda], &arreglo[derecha]);
      izquierda++;
      derecha--;
    }
  }
}

int main(int argc, char *argv[]){
    char s1[20], s2[20];
    int cont= 0, s3;

    //Abrimos el semaforo
    sem_t *sem = sem_open("miniRetoU3", 0); 
    if(sem== SEM_FAILED){
        //Creamos el semaforo
        mode_t perms = 0666;
        int flags = O_CREAT;
        unsigned int value =0; //Tener el semaforo cerrado
        sem = sem_open("miniRetoU3", flags, perms, value);
        if(sem == SEM_FAILED){
            perror("p1 sem_open: ");
            exit(EXIT_FAILURE);
        }
    }
    
    FILE *in_file = fopen(argv[1], "r");
    if(in_file == NULL){
        printf("No se puede abrir %s\n", argv[1]);
        exit(8);
    }
    while(1){
        if(fscanf(in_file, "%s %s %d", s1, s2, &s3)!=3)
            break;
        cont++;
        if(s3<0){
            printf("La edad en la fila %d es invalida\n", cont);
            return 0;
        }
    }
    rewind(in_file);
    if(cont>100){
        printf("%d ", cont);
        printf("Hay mas de 100 filas\n");
        return 0;
    }
    fila *pFila = (fila *)malloc(sizeof(fila)*cont);
    for (int i = 0; i < cont; i++)
    {
        fscanf(in_file, "%s %s %d", s1, s2, &s3);
        strcpy(pFila[i].nombre, s1);
        strcpy(pFila[i].ocupacion, s2);
        pFila[i].edad = s3;
    }
    FILE *on_file = fopen(argv[2], "w");
    ordenAlfabetico(pFila, on_file, cont);
    
    //Abrimos el candado
    if(sem_post(sem)==-1){
        perror("pSemPost sem_post error: ");
        exit(EXIT_FAILURE);
    }
    //Cerramos el cemaforo
    if(sem_close(sem)==-1){
        perror("pSemPost sem_close fails: ");
        exit(EXIT_FAILURE);
    }
    fclose(in_file);
    fclose(on_file);

    //Nuevo semaforo
    sem_t *sem2 = sem_open("miniRetoU3_2", 0); 
    if(sem2== SEM_FAILED){
        //Creamos el semaforo
        mode_t perms = 0666;
        int flags = O_CREAT;
        unsigned int value =0; //Tener el semaforo cerrado
        sem2 = sem_open("miniRetoU3_2", flags, perms, value);
        if(sem2 == SEM_FAILED){
            perror("p1 sem_open: ");
            exit(EXIT_FAILURE);
        }
    }

    //Cerramos nosotros el candado
    if(sem_wait(sem2)==-1){
        perror("sem_wait: ");
        exit(EXIT_FAILURE);
    }
    FILE *in_file2 = fopen(argv[3], "r");
    if(in_file == NULL){
        printf("No se puede abrir %s\n", argv[1]);
        exit(8);
    }

    printf("Salida Out 2\n");
    for (int i = 0; i < cont; i++)
    {
        fscanf(in_file2, "%s %s %d", s1, s2, &s3);
        printf("%s %s %d\n", s1, s2, s3);
    }
    //Cerramos el semaforo
    // printf("Hola\n");
    if(sem_close(sem2)==-1){
        perror("pSemPost sem_close fails: ");
        exit(EXIT_FAILURE);
    }
    //Destruimos el semaforo
    if(sem_unlink("miniRetoU3_2")==-1){
        perror("pSemWait sem_unlink fails: ");
        exit(EXIT_FAILURE);
    }
    fclose(in_file2);
    return 0;
}