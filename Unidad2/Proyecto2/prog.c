#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct{
    char nombre[20];
    char ocupacion[20];
    int edad;
}fila;

typedef struct{
    int cont;
    fila * pFila;
    FILE *on_file;
}Parametros;

char checkOf(FILE *archivo){//Creditos a Manguito
    char ch;
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    return ch;
}

void * ordenInverso(void* parametros){
    Parametros * p = (Parametros *)parametros;
    for (int i = p->cont-1; i>= 0; i--)
    {
        fprintf(p->on_file, "%s %s %d\n", p->pFila[i].nombre, p->pFila[i].ocupacion, p->pFila[i].edad);
    }
    fclose(p->on_file);
    return NULL;
}
void * ordenAlfabetico(void *parametros){
    Parametros *p = (Parametros *)parametros;
    //ordenamos por QuickSort
    quicksort(p->pFila, 0, p->cont-1);
    for (int i = 0; i < p->cont; i++)
    {
        fprintf(p->on_file, "%s %s %d\n", p->pFila[i].nombre, p->pFila[i].ocupacion, p->pFila[i].edad);
    }
    fclose(p->on_file);
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
    while (strcmp(arreglo[izquierda].ocupacion, pivote.ocupacion) < 0) {
      izquierda++;
    }
    while (strcmp(arreglo[derecha].ocupacion, pivote.ocupacion) > 0) {
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
    char ch, s1[20], s2[20];
    int cont = 0, s3;
    pthread_t id_hilo_1;
    pthread_t id_hilo_2;
    Parametros p1, p2;

    FILE *in_file = fopen(argv[1], "r");
    if(in_file == NULL){
        printf("No se puede abrir %s\n", argv[1]);
        exit(8);
    }
    while(ch!=EOF){
        fscanf(in_file, "%s %s %d", s1, s2, &s3);
        cont++;
        if(s3<0){
            printf("La edad en la fila %d es invalida\n", cont);
            return 0;
        }
        ch = checkOf(in_file);
    }
    rewind(in_file);

    if(cont>100){
        printf("%d ", cont);
        printf("Hay mas de 100 filas\n");
        return 0;
    }

    FILE *on_file1 = fopen(argv[2], "w");
    FILE *on_file2 = fopen(argv[3], "w");

    fila *pFila = (fila *)malloc(sizeof(fila)*cont);
    for (int i = 0; i < cont; i++)
    {
        fscanf(in_file, "%s %s %d", s1, s2, &s3);
        strcpy(pFila[i].nombre, s1);
        strcpy(pFila[i].ocupacion, s2);
        pFila[i].edad = s3;
    }
    printf("Contenido de la estructura\n");
    for (int i = 0; i < cont; i++)
    {
        printf("%s %s %d\n", pFila[i].nombre, pFila[i].ocupacion, pFila[i].edad);
    }
    printf("\n");

    p1.on_file = on_file1;
    p1.cont = cont;
    p1.pFila = pFila;
    p2.on_file = on_file2;
    p2.cont = cont;
    p2.pFila = pFila;
    //Hilos en paralelo
    pthread_create(&id_hilo_1, NULL, &ordenInverso, &p1);
    pthread_create(&id_hilo_2, NULL, &ordenAlfabetico, &p2);

    pthread_join (id_hilo_1, NULL);
    pthread_join (id_hilo_2, NULL);
    
    
    on_file1 = fopen(argv[2], "r");
    printf("Salida del hilo 1\n");
    for (int i = 0; i < cont; i++)
    {
        fscanf(on_file1, "%s %s %d", s1, s2, &s3);
        printf("%s %s %d\n", s1, s2, s3);
    }
    printf("\n");
    on_file2 = fopen(argv[3], "r");
    printf("Salida del hilo 2\n");
    for (int i = 0; i < cont; i++)
    {
        fscanf(on_file2, "%s %s %d", s1, s2, &s3);
        printf("%s %s %d\n", s1, s2, s3);
    }
    
    
    fclose(in_file);
    fclose(on_file1);
    fclose(on_file2);
    free(pFila);
    return 0;
}