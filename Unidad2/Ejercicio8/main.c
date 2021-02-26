#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    pid_t pid_hijo1, pid_hijo2, pid_hijo3;
    printf("Este es el proceso base: %d\n", (int)getpid());

    for (int i = 1; i <= 3; i++){
        if(i==1){
            pid_hijo1 = fork();
            if(pid_hijo1==0){
                // printf("Proceso hijo con id %d %d\n", (int)getpid(), i);
                execv("./promedio",argv);
            }
        }
        else if(i==2){
            pid_hijo2 = fork();
            if(pid_hijo2==0){
                // printf("Proceso hijo con id %d %d\n", (int)getpid(), i);
                execv("./max",argv);
            }
        }
        else if(i==3){
            pid_hijo3 = fork();
            if(pid_hijo3==0){
                // printf("Proceso hijo con id %d %d\n", (int)getpid(), i);
                execv("./min",argv);
            }
        }
    }
    wait(NULL);
    wait(NULL);
    wait(NULL);
    return 0;
}