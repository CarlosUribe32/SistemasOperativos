#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int min = 0;
    for (int i = 1; i < argc; i++)
    {
        if(i==1)
            min = atoi(argv[i]);
        else if(atoi(argv[i])<min)
            min = atoi(argv[i]);
    }
    printf("El minimo es: %d\n", min);
    return 0;
}