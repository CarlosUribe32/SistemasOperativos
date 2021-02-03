#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int cedula;
    char nombre[30];
    int semestre;
}estudiante;

typedef struct{
    char nombre[20];
    int numRegistros;
    estudiante *registro;
}bdActual;

int main(void){
    char comando [10];
    char par1[10];
    int par2;
    int par3;
    do
    {
        printf("Ingrese el comando:\n");
        scanf("%s", comando);
        printf("El com es: %s\n", comando);
        fscanf(stdin, "%s", par1);
        printf("Goleee con estas papa %s\n", par1);
    } while (strcmp(comando, "exit")!=0);
    
    return 0;
}