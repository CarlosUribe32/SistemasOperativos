#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char checkOf(FILE *archivo){ //Creditos a Manguito
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

    if(in_file == NULL){
        printf("No se puede abrir %s\n", argv[1]);
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
        FILE *on_file = fopen(argv[2], "w");
        fila *pFila = (fila*)malloc(sizeof(fila)*cont);
        for (int i = 0; i < cont; i++)
        {
            fscanf(in_file, "%s %d", s1, &s2);
            strcpy(pFila[i].clave, s1);
            pFila[i].valor = s2;
        }
        quicksort(pFila, 0, cont - 1);
        for (int i = cont-1; i >= 0; i--)
        {
            fprintf(on_file, "%s %d\n", pFila[i].clave, pFila[i].valor);
        }
       
        free(pFila);
        fclose(on_file);
    }
    else
        printf("Este archivo tiene mas de 100 lineas\n");
    fclose(in_file);
    return 0;
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
    while (arreglo[izquierda].valor < pivote.valor) {
      izquierda++;
    }
    while (arreglo[derecha].valor > pivote.valor) {
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