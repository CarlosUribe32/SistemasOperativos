#include <stdio.h>
#include <unistd.h>

//Mi primer comentario en C
char nombre[50];
/*
Siuuuuu
*/
int main(){
    int pid = getpid(); //Este metodo devuelve el id del proceso
    printf("Ingrese su nombre porfa: ");
    scanf("%s", nombre);
    printf("Hola %s, su id de proceso es %d", nombre, pid);
    return 0;
}