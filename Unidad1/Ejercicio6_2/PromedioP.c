#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char INPUT_FILE[40];
const char OUTPUT_FILE[40];

char(*pos1)[20];
float *pos2;
int *pos3;

char checkOf(FILE *);
char checkOf(FILE *archivo){
    char ch;
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    return ch;
}

int main(){
    int nMaterias=0;
    
    printf("Ingrese el archivo origen\n");
    scanf("%s", INPUT_FILE);
    printf("Ingrese el archivo de salida\n");
    scanf("%s", OUTPUT_FILE);

    char ch;
    FILE *in_file = fopen(INPUT_FILE, "r");
    FILE *on_file = fopen(OUTPUT_FILE, "r+");

    pos1 = (char(*)[20])malloc(sizeof(char[20])*nMaterias);
    pos2 = (float *)malloc(sizeof(float)*nMaterias);
    pos3 = (int *)malloc(sizeof(int)*nMaterias);
    char s1[20], s2[20], s3[20], m[20];

    if(in_file == NULL || on_file==NULL){
        printf("No se puede abrir %s o %s\n", INPUT_FILE, OUTPUT_FILE);
        exit(8);
    }
    fprintf(on_file, "Materia  Nota  Creditos  \n");
    int totCreditos =0;
    while(ch!=EOF){
        fscanf(in_file, "%s %s %s %s %s %s", s1, m , s2, m, s3, m);
        nMaterias++;
        ch = checkOf(in_file);
    }
    rewind(in_file);
    for (size_t i = 0; i < nMaterias; i++)
    {
        fscanf(in_file, "%s %s %s %f %s %d", s1,(pos1+i), s2, (float *)(pos2+i), s3, (int *)(pos3+i));
        printf("%s %f %d\n",(pos1+i), *(pos2+i), *(pos3+i));
        fprintf(on_file, "%s  %f  %1d  \n", (pos1+i), *(pos2+i), *(pos3+i));
        totCreditos += *(pos3+i);
    }
    
    float promedio =0;
    int matGan=0;
    int matPer=0;
    for (size_t i = 0; i < nMaterias; i++)
    {
        promedio += *(pos2+i);
        if(*(pos2+i)>=3)
            matGan++;
        else
            matPer++;
    }
    fprintf(on_file, "Total materias %d\nTotal ganadas %d\nTotal perdidas %d\n", nMaterias, matGan, matPer);
    fprintf(on_file, "Promedio: %f, Total de creditos: %d\n", promedio/nMaterias, totCreditos);
    
    fclose(in_file);
    fclose(on_file);
    free(pos1);
    free(pos2);
    free(pos3);
    return 0;
}