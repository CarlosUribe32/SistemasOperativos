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
    bdList * pL = malloc(sizeof(bdList));
    pL->pbd = (bd *)malloc(sizeof(bd)*30);
    pL->size=0;
    return pL;
}
void destroyP(){
    free(pList->pbd);
    free(pList);
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

        if(strcmp(comando, "mdb")==0){
            fscanf(stdin, "%s %d", par1, &par2);
            mdb(par1, par2);
        }
        else if(strcmp(comando, "ldb")==0){
            fscanf(stdin, "%s", par1);
            FILE *in_file = fopen(par1, "r");
            if(in_file == NULL)
                printf("No se puede abrir %s\n", par1);
            else{
                ldb(in_file);
                fclose(in_file);
            }
        }
    } while (strcmp(comando, "exit")!=0);
    destroyP();
}

void mdb(char name[30], int size){
    strcpy(pList->pbd[pList->size].nombre, name);
    pList->pbd[pList->size].numRegistros = size;
    pList->pbd[pList->size].registro = (estudiante *)malloc(sizeof(estudiante)*size);
    pList->pbd[pList->size].size = 0;
    pList->size = pList->size+1;
}
void ldb(FILE *in_file){
    char ch;
    char name[30], people[30];
    int size, ced, sem, actual;
    fscanf(in_file, "%s %d %d", name, &size, &actual);
    
    if(strcmp(name, "")==0 || size==0){
        printf("La BD no existe o es invalida\n");
        return;
    }
    
    strcpy(pList->pbd[pList->size].nombre, name);
    pList->pbd[pList->size].numRegistros = size;
    pList->pbd[pList->size].size = actual;
    pList->pbd[pList->size].registro = (estudiante *)malloc(sizeof(estudiante)*size);
    for(int i=0; i< pList->pbd[pList->size].size; i++){
        fscanf(in_file, "%d %s %d", &ced, people , &sem);
        pList->pbd[pList->size].registro[i].cedula = ced;
        strcpy(pList->pbd[pList->size].registro[i].nombre, people);
        pList->pbd[pList->size].registro[i].semestre = sem;
    }
    printf("Se cargo con exito la BD %s\n", pList->pbd[pList->size].nombre);
    pList->size = pList->size+1;
}