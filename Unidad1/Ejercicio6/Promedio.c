#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char(*pos1)[20];
float *pos2;
int *pos3;
int main(void){
    int nMaterias;
    printf("Ingrese el numero de materias: ");
    scanf("%d", &nMaterias);

    pos1 = (char(*)[20])malloc(sizeof(char[20])*nMaterias);
    pos2 = (float *)malloc(sizeof(float)*nMaterias);
    pos3 = (int *)malloc(sizeof(int)*nMaterias);

    for (size_t i = 0; i < nMaterias; i++)
    {
        printf("Ingrese el nombre de la materia:\n");
        scanf("%s", (char *)(pos1+i));
        printf("Ingrese la nota:\n");
        scanf("%f", (float *)(pos2+i));
        printf("Ingrese los creditos:\n");
        scanf("%d", (int *)(pos3+i));
    } 

    printf("Materia\tNota\tCreditos\n");
    for (size_t i = 0; i < nMaterias; i++)
    {
        printf("%s\t%f\t%d\n", (char *)(pos1+i), *(pos2+i), *(pos3+i));
    }
    float promedio =0;
    int totCreditos =0;
    for (size_t i = 0; i < nMaterias; i++)
    {
        promedio += *(pos2+i);
        totCreditos += *(pos3+i);
    }
    printf("Promedio: %f, Total de creditos: %d\n", promedio/nMaterias, totCreditos);
    free(pos1);
    free(pos2);
    free(pos3);
    
    return 0;
}
