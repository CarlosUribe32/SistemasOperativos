#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char checkOf(FILE *archivo){//Creditos a Manguito
    char ch;
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    ch = fgetc(archivo);
    return ch;
}

int main(int argc, char *argv[]){
    pid_t pid_hijo1, pid_hijo2;
    if(argc == 4){
        printf("Este es el proceso base: %d\n", (int)getpid());
        for (int i = 1; i <= 2; i++){
            if(i==1){
                pid_hijo1 = fork();
                if(pid_hijo1==0){
                    printf("Proceso hijo con id %d %d\n", (int)getpid(), i);
                    execv("./p1",argv);
                }
            }
            else if(i==2){
                pid_hijo2 = fork();
                if(pid_hijo2==0){
                    printf("Proceso hijo con id %d %d\n", (int)getpid(), i);
                    execv("./p2",argv);
                }
            }
        }
        wait(NULL);
        wait(NULL);
    }
    else{
        printf("El numero de argumentos es invalido\n");
        return 0;
    }

    char ch;
    int cont = 0, id=0;
    char s1[20];
    int s2;
    FILE *in_file = fopen(argv[1], "r");
    FILE *in_file1 = fopen(argv[2], "r");
    FILE *in_file2 = fopen(argv[3], "r");
    if(in_file1 == NULL || in_file2==NULL){
        printf("No se puede abrir %s o %s\n", argv[2], argv[3]);
        exit(8);
    }

    while(ch!=EOF){
        fscanf(in_file, "%s %d", s1, &s2);
        cont++;
        ch = checkOf(in_file);
    }

    printf("\nArchivo generado por p1\n");
    for(int i = 0; i< cont; i++){
        fscanf(in_file1, "%s %d", s1, &s2);
        printf("%s %d\n", s1, s2);
    }
    printf("\nArchivo generado por p2\n");
    for(int i = 0; i< cont; i++){
        fscanf(in_file2, "%s %d", s1, &s2);
        printf("%s %d\n", s1, s2);
    }

    fclose(in_file1);
    fclose(in_file2);
    return 0;
}