#include <stdio.h>

int main()
{
    int num;
    char key;
    printf("Prueba a scanf. Ingrese el numero 325 y presione ENTER:\n");
    scanf("%d",&num);
    printf("Ingrese cualquier tecla para terminar y presione ENTER:\n");
    fscanf(stdin, "%c %c", &key, &key);//Otra posible solucion
    return 0;
}