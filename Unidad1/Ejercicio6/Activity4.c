#include <stdio.h>
#include <stdlib.h>

int array[100];
float promedio();

int main(void){
    float prom;
    srand (getpid());
    for (size_t i = 0; i < 100; i++)
    {
        array[i] = rand()%100;
    }
    prom = promedio();
    printf("El promedio de los 100 numeros es: %f\n", prom);
    return 0;
}

float promedio(){
    int *pArray = array;
    int suma=0;
    for (size_t i = 1; i <= 100; i++)
    {   
        suma += *pArray;
        pArray++;
    }
    float prom = suma/100;
    return prom;
}