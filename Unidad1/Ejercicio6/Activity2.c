#include <stdio.h>

int main(void){
    int vector[4];
    vector[0] = 1;
    vector[1] = 20;
    vector[2] = 30;
    vector[3] = 40;
    
    int a = *(vector+1);
    int b = *vector + 1;
    printf("%d\n%d\n", a, b); //Salidas: 20 y 2
    return 0;
}