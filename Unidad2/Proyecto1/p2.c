#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char checkOf(FILE *archivo){
    char ch;
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    return ch;
}
typedef struct{
    char clave[20];
    int valor;
}fila;

int main(int argc, char *argv[]){
    char ch;
    int cont = 0;
    char s1[20];
    int s2;
    int id=0;

    FILE *in_file = fopen(argv[1], "r");
    FILE *on_file = fopen(argv[2], "w");

    if(in_file == NULL || on_file==NULL){
        printf("No se puede abrir %s o %s\n", argv[1], argv[2]);
        exit(8);
    }
    while(ch!=EOF){
        fscanf(in_file, "%s %d", s1, &s2);
        cont++;
        if(s2>1000 || s2<-1000){
            id = 1;
            break;
        }
        ch = checkOf(in_file);
    }
    rewind(in_file);
    
    if(id==1){
        printf("La linea %d del archivo origen no cumple con los parametros del valor\n", cont);
        return 0;
    }
    if(cont<=100){
        fila *pFila = (fila*)malloc(sizeof(fila)*cont);
        for (int i = 0; i < cont; i++)
        {
            fscanf(in_file, "%s %d", s1, &s2);
            strcpy(pFila[i].clave, s1);
            pFila[i].valor = s2;
        }
        for (int i = cont-1; i >= 0; i--)
        {
            fprintf(on_file, "%s %d\n", pFila[i].clave, pFila[i].valor);
        }
       
        free(pFila);
    }
    else
        printf("Este archivo tiene mas de 100 lineas\n");
    fclose(in_file);
    fclose(on_file);
    return 0;
}