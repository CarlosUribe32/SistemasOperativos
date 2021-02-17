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
    int sel;
}bdList;

bdList * pList;
bdList * createP(){
    bdList * pL = malloc(sizeof(bdList));
    pL->pbd = (bd *)malloc(sizeof(bd)*30);
    pL->pbdActual = malloc(sizeof(bd));
    pL->size=0;
    pL->sel =0;
    return pL;
}
void destroyP(){
    for (int i = 0; i < pList->size; i++){
        free(pList->pbd[i].registro);
    }
    
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
        else if(strcmp(comando, "lsdbs")==0){
            lsdbs();
        }
        else if(strcmp(comando, "sdb")==0){
            fscanf(stdin, "%s", par1);
            sdb(par1);
        }
        else if(strcmp(comando, "gdb")==0){
            gdb();
        }
        else if (strcmp(comando, "svdb")==0){
            svdb();
        }
        else if (strcmp(comando, "radb")==0){
            radb();
        }
        else if(strcmp(comando, "rsdb")==0){
            rsdb();
        }
        else if (strcmp(comando, "mreg")==0){
            fscanf(stdin, "%d %s %d", &par2, par1, &par3);
            mreg(par2, par1, par3);
        }
        else if(strcmp(comando, "rr")==0){
            fscanf(stdin, "%d", &par2);
            rr(par2);
        }
        getc(stdin);

    } while (strcmp(comando, "exit")!=0);
    destroyP();
}

void mdb(char name[30], int size){
    for (int i = 0; i < pList->size; i++)
    {
        if(strcmp(pList->pbd[i].nombre, name)==0){
            printf("Esta BD ya existe\n");
            return;
        }
    }
    
    strcpy(pList->pbd[pList->size].nombre, name);
    pList->pbd[pList->size].numRegistros = size;
    pList->pbd[pList->size].registro = (estudiante *)malloc(sizeof(estudiante)*size);
    pList->pbd[pList->size].size = 0;
    pList->size = pList->size+1;
    printf("Se creo con exito la BD %s\n", pList->pbd[pList->size].nombre);
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

void lsdbs(){
    printf("Cantidad de BD: %d\n", pList->size);
    for (int i = 0; i < pList->size; i++){
        printf("BD: %s - Tamaño: %d - Registros: %d\n", pList->pbd[i].nombre, pList->pbd[i].numRegistros, pList->pbd[i].size);
    }
}

void sdb(char name[30]){
    for (int i = 0; i < pList->size; i++){
        if(strcmp(pList->pbd[i].nombre, name)==0){
            printf("Se encontro la BD %s\n", name);
            pList->pbdActual = pList->pbd +i;
            pList->sel = 1;
            break;
        }
    }
    if(pList->sel==0){
        printf("Esta BD no existe\n");
    }
}

void gdb(){
    if(pList->sel==0){
        printf("No hay ninguna BD seleccionada\n");
        return;
    }
    printf("BD activa - Nombre: %s - Tamaño: %d - Registros disponibles: %d\n", pList->pbdActual->nombre, pList->pbdActual->numRegistros, (pList->pbdActual->numRegistros - pList->pbdActual->size));
}

void svdb(){
    if(pList->sel==0){
        printf("No hay ninguna BD seleccionada\n");
        return;
    }
    char doc[30];
    strcpy(doc, pList->pbdActual->nombre);
    FILE *on_file = fopen(strcat(doc, ".txt"), "w+");
    if(on_file == NULL){
        printf("No se puede abrir %s\n", doc);
        return;
    }
    fprintf(on_file, "%s %d %d\n", pList->pbdActual->nombre, pList->pbdActual->numRegistros, pList->pbdActual->size);
    for (int i = 0; i < pList->pbdActual->size; i++)
    {
        fprintf(on_file, "%d %s %d\n", pList->pbdActual->registro[i].cedula, pList->pbdActual->registro[i].nombre, pList->pbdActual->registro[i].semestre);
    }
    printf("Se guardo correctamente la BD\n");
}

void radb(){
    if(pList->sel==0){
        printf("No hay ninguna BD seleccionada\n");
        return;
    }
    printf("Base de datos: %s\n", pList->pbdActual->nombre);
    for (int i = 0; i < pList->pbdActual->size; i++)
    {
        printf("%d %s %d\n", pList->pbdActual->registro[i].cedula, pList->pbdActual->registro[i].nombre, pList->pbdActual->registro[i].semestre);
    }
}

void rsdb(){
    if(pList->sel==0){
        printf("No hay ninguna BD seleccionada\n");
        return;
    }
    printf("Base de datos: %s - Registros Actuales: %d\n", pList->pbdActual->nombre, pList->pbdActual->size);
}

void mreg(int ced, char nombre[30], int semestre){
    if(pList->sel==0){
        printf("No hay ninguna BD seleccionada\n");
        return;
    }
    if(pList->pbdActual->size==pList->pbdActual->numRegistros){
        printf("La base de datos ya esta en su capacidad total\n");
        return;
    }
    for (int i = 0; i < pList->pbdActual->size; i++)
    {
        if(pList->pbdActual->registro[i].cedula==ced){
            printf("Ya hay un registro con este numero de cedula\n");
            return;
        }
    }
    
    int i = pList->pbdActual->size;
    pList->pbdActual->registro[i].cedula = ced;
    strcpy(pList->pbdActual->registro[i].nombre, nombre);
    pList->pbdActual->registro[i].semestre = semestre;
    pList->pbdActual->size = ++i;
    printf("Se registro correctamente la informacion en la BD %s\n", pList->pbdActual->nombre);
}

void rr(int par2){
    for (int i = 0; i < pList->pbdActual->size; i++)
    {
        if(pList->pbdActual->registro[i].cedula==par2){
            printf("BD %s\n", pList->pbdActual->nombre);
            printf("%d %s %d\n", pList->pbdActual->registro[i].cedula, pList->pbdActual->registro[i].nombre, pList->pbdActual->registro[i].semestre);
            return;
        }
    }
    printf("No se encontro el registro\n");
}