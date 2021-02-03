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
}bdActual;

char checkOf(FILE *archivo){
    char ch;
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    return ch;
}

bdActual * mkdb(char[30], int);
bdActual *loaddb(FILE *);

int main(void){

    bdActual *pbd;
    char comando [10];
    char par1[30];
    int par2;
    int par3;
    do
    {
        printf("Ingrese el comando:\n");
        scanf("%s", comando);
        if(strcmp(comando, "mkdb")==0)
        {
            fscanf(stdin, "%s %d", par1, &par2);
            pbd = mkdb(par1, par2);
            printf("Se contruyo con exito la BD %s\n", par1);
        }
        else if (strcmp(comando, "loaddb")==0){
            fscanf(stdin, "%s", par1);
            FILE *in_file = fopen(par1, "r");
            if(in_file == NULL)
                printf("No se puede abrir %s\n", par1);
            else{

            }
        }
        else if (strcmp(comando, "savedb")==0){

        }
        else if (strcmp(comando, "readall")==0){

        }
        else if (strcmp(comando, "readsize")==0){

        }
        else if (strcmp(comando, "mkreg")==0){

        }
        else if (strcmp(comando, "readreg")==0){

        }
        getc(stdin);
    } while (strcmp(comando, "exit")!=0);
    
    return 0;
}

bdActual * mkdb(char name[30], int size){
    bdActual bd = {name, size, 0, (estudiante *)malloc(sizeof(estudiante)*size)};
    bdActual *pbd = &bd;
    return pbd;
}

bdActual *loaddb(FILE *in_file){
    char ch;
    char name[30], people[30];
    int i=0, size, ced, sem;
    fscanf(in_file, "%s %d", name, &size);
    bdActual bd = {name, size, 0, (estudiante *)malloc(sizeof(estudiante)*size)};
    while(ch!=EOF){
        fscanf(in_file, "%d %s %d", ced, people , sem);
        bd.registro+i-->ced;
        bd.registro+i-->people;
        bd.registro+i-->sem;
        i++;
        ch = checkOf(in_file);
    }
    bd.size = i;
    return &bd;
}
