#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int max = 0;
    for (int i = 1; i < argc; i++)
    {
        if(i==1)
            max = atoi(argv[i]);
        else if(atoi(argv[i])>max)
            max = atoi(argv[i]);
    }
    printf("El maximo es: %d\n", max);
    return 0;
}