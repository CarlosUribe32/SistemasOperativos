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

    FILE *in_file = fopen(argv[1], "r");
    FILE *on_file = fopen(argv[2], "w");

    if(in_file == NULL || on_file==NULL){
        printf("No se puede abrir %s o %s\n", argv[1], argv[2]);
        exit(8);
    }
    while(ch!=EOF){
        fscanf(in_file, "%s %d", s1, s2);
        cont++;
        ch = checkOf(in_file);
    }
    rewind(in_file);
    
    fila *pFila = (fila*)malloc(sizeof(fila)*cont);
    for (int i = 0; i < cont; i++)
    {
        fscanf(in_file, "%s %d", s1, s2);
        strcpy(pFila[i].clave, s1);
        pFila[i].valor = s2;
    }
    quicksort(pFila, 0, cont - 1);
    
    fclose(in_file);
    fclose(on_file);
    free(pFila);
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