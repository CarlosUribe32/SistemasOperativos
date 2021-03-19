#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 100

int main(int argc, char *argv[]){
    int pfd1[2], pfd2[2], nBytes;
    char buf[BUF_SIZE], cadena[BUF_SIZE];
    pid_t pid_hijo;

    if(pipe(pfd1)<0 || pipe(pfd2)<0){
        perror("Error en los pipes\n");
        return 0;
    }
    pid_hijo = fork();
    if(pid_hijo==0){
        close(pfd1[1]);
        close(pfd2[0]);
        while (1){
            //Lee del pipe 1
            nBytes = read(pfd1[0], buf, BUF_SIZE);
            if(nBytes>0){
                for (int i = 0; i < BUF_SIZE; i++){
                    if (buf[i] >= 'a' && buf[i] <= 'z')
                        buf[i] = buf[i] - 'a' + 'A';
                }
                //Escribir en el pipe 2
                write(pfd2[1], buf, BUF_SIZE);
            }
        }
        close(pfd1[0]);
        close(pfd2[1]);
        return 0;
    }
    else{
        close(pfd1[0]);
        close(pfd2[1]);
        while(1){
            //Escribe en el pipe 1
            printf("Ingrese la entrada que me va a procesar el hijo\n");
            fgets (cadena, BUF_SIZE, stdin);
            write(pfd1[1], cadena, BUF_SIZE);

            //Lee del pipe 2
            nBytes = read(pfd2[0], buf, BUF_SIZE);
            if(nBytes>0)
                printf("El mensaje convertido es %s\n", buf);       
        }
        close(pfd1[1]);
        close(pfd2[0]);
        return 0;
    }
}