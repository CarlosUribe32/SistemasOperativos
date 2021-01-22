#include <stdio.h>

void suma(float, float);
void resta(float, float);
void multiplicacion(float, float);
void division(float, float);


int main(void){
    char c;
    float a;
    float b;
    int option;
    do{
        printf("Ingrese el primer operando\n");
        scanf("%f", &a);
        printf("\nIngrese el segundo operando\n");
        scanf("%f", &b);
        printf("\nIngrese: 1 para sumar, 2 para restar, 3 para multiplicar o 4 para dividir\n");
        scanf("%d", &option);
        if (option == 1)
            suma(a, b);
        else if (option == 2)
            resta(a, b);
        else if (option == 3)
            multiplicacion(a, b);
        else if (option == 4)
            division(a,b);
        printf("\nPresione q si quiere salir o cualquier letra si quiere continuar\n");
        scanf("%c", &c);
        scanf("%c", &c);
    }while(c!='q');
    printf("\nFin del programa\n");
    return 0;
}

void suma(float a, float b){
    double res;
    res = a+b;
    printf("El resultado es: %f\n", res);
}
void resta(float a, float b){
    double res;
    res = a-b;
    printf("El resultado es: %f\n", res);
}
void multiplicacion(float a, float b){
    double res;
    res = (a)*(b);
    printf("El resultado es: %f\n", res);
}
void division(float a, float b){
    double res;
    res = a/b;
    printf("El resultado es: %f\n", res);
}