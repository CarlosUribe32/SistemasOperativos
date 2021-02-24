#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    double promedio = 0; 
    int max = 0, min = 0;
    int num[argc-1];
    for (int i = 0; i < argc; i++)
    {
        num[i] = atoi(argv[i]);
    }
    
    for (int i = 1; i < argc; i++)
    {
        promedio = promedio + num[i];
        if(i==1){
            max = num[i];
            min = num[i];
        }
        else if(num[i]>max)
            max = num[i];
        else if(num[i]<min)
            min = num[i];
    }
    promedio = promedio/(argc-1);
    printf("Promedio: %f\nMax: %d\nMin: %d\n", promedio, max, min);
}