#include <pthread.h>
#include <stdio.h>

/*Imprime 'x' en la salida de error stderr.
El parametro no es usado. No tiene retorno */

void* imprime_x(void* unused){
    while(1)
        fputc('x', stderr);
    return NULL;
}
int main(){
    pthread_t id_hilo;
    //Crea un nuevo hilo sobre la funcion imprime
    pthread_create(&id_hilo, NULL, &imprime_x, NULL);
    //Imprime 'o' en la salida de error stderr
    while(1)
        fputc('o', stderr);
        return 0;
}