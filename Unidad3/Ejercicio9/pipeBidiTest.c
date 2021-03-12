#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 20

int main(int argc, char *argv[]){
    int pfd[2], nBytes;
    char buf[BUF_SIZE];
    pid_t pid_hijo1;

    if (argc != 3 || strcmp(argv[1], "--help") == 0){
        printf("EL comando correcto a ejecutar es: %s mensajePadre mensajeHijo\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
    if(pipe(pfd)<0){
        printf("Error en el pipe\n");
        return 0;
    }
    
    pid_hijo1 = fork();
    if(pid_hijo1==0){
        printf("Hola soy el proceso hijo y el mensaje para mi padre es: %s\n", argv[2]);
        nBytes = read(pfd[0], buf, BUF_SIZE);
        if(nBytes>0)
            printf("El mensaje de mi padre es %s\n", buf);
        else
            return 0;
        close(pfd[0]);
        write(pfd[1], argv[2], BUF_SIZE);
        close(pfd[1]);
        return 0;
    }
    else{
        printf("Hola soy el proceso padre y el mensaje para mi hijo es: %s\n", argv[1]);
        write(pfd[1], argv[1], BUF_SIZE);
        close(pfd[1]);
        wait(NULL);
        nBytes = read(pfd[0], buf, BUF_SIZE);
        if(nBytes>0)
            printf("El mensaje de mi hijo es %s\n", buf);
        else
            return 0;
        close(pfd[0]);
        return 0;
    }
}