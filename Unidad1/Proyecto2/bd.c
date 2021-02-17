#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int cedula;
    char nombre[30];
    int semestre;
}estudiante;

typedef struct{
    char nombre[30];
    int numRegistros;
    int size;
    estudiante *registro;
}bd;

typedef struct{
    bd * pbd;
    bd * pbdActual;
    int size;
}bdList;

bdList * pList;
bdList * createP(){
    bdList * pList = malloc(sizeof(bdList));
    pList->pbd = (bd *)malloc(sizeof(bd)*30);
    return pList;
}

int main(void){
    pList = createP();
    char comando [10];
    char par1[30];
    int par2;
    int par3;
    do
    {
        printf("Ingrese el comando:\n");
        scanf("%s", comando);
    } while (strcmp(comando, "exit")!=0);
    
}