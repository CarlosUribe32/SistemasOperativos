#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    double promedio = 0;
    for (int i = 1; i < argc; i++)
    {
        promedio = promedio + atoi(argv[i]);
    }
    promedio = promedio/(argc-1);
    printf("El promedio es: %f\n", promedio);
    return 0;
}