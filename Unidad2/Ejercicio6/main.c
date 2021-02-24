#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    pid_t pid_hijo;
    int fact = 1;
    printf("Este es el proceso base: %d\n", (int)getpid());

    for (int i = 1; i <= 3; i++)
    {
        pid_hijo = fork();
        wait();
        if(pid_hijo==0){
            printf("Hijo %d", i);
            break;
        }
    }

    if(pid_hijo==0){
        printf(" con proceso %d\n",(int)getpid());
        for (int i = 1; i <= 10; i++){
            fact = fact*i;
            printf("  fact(%d)=%d\n", i, fact);
        } 
    }
    printf("\n");
}