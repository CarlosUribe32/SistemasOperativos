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

char checkOf(FILE *archivo){//Creditos a Manguito
    char ch;
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    return ch;
}

int main(int argc, char *argv[]){
    char ch, s1[20], s2[20];
    int cont, s3;

    FILE *in_file = fopen(argv[1], "r");
    if(in_file == NULL){
        printf("No se puede abrir %s\n", argv[1]);
        exit(8);
    }
    while(ch!=EOF){
        fscanf(in_file, "%s %s %d", s1, s2, &s3);
        cont++;
        if(s3<0){
            printf("La edad en la fila %d es invalida\n", s3);
            return 0;
        }
        ch = checkOf(in_file);
    }
    rewind(in_file);

    if(cont>100){
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
    printf("Contenido de la estructura\n");
    for (int i = 0; i < cont; i++)
    {
        printf("%s %s %d\n", pFila[i].nombre, pFila[i].ocupacion, pFila[i].edad);
    }
    printf("\n");
    
    fclose(in_file);
    free(pFila);
    return 0;
}