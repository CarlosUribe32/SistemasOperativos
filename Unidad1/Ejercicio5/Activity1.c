#include <stdio.h>

int main(void){
    char c;
    printf("Ingrese caracteres, X = Salir del programas.\n");
    do{
        c = getchar();
        putchar(c);
        putchar('\n');
    }while(c!='X');
    printf("\nFin del programa.\n");
    return(0);
}