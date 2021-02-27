#include <pthread.h>
#include <stdio.h>

//Esta estructura sirve para pasar parametros al hilo
struct parametros_hilo{
    //Parametro 1 caracter a imprimir
    char caracter;
    //Parametro 2 numero de veces a imprimir
    int contador;
};

/*La siguiente funcion imprime un numero de caracteres a la
salida de error, tal como lo indica el parametro de la funcion*/

void* imprimir_caracter(void* parametros){
    //Casteo
    struct parametros_hilo* p =(struct parametros_hilo*) parametros;
    int i;
    for(i==0 ; i< p->contador; ++i)
        fputc(p->caracter, stderr);
    return NULL;
}

//Programa principal
int main(){
    pthread_t id_hilo_1;
    pthread_t id_hilo_2;
    struct parametros_hilo hilo1_param;
    struct parametros_hilo hilo2_param;

    //Crear un hilo para imprimir 30000 x
    hilo1_param.caracter = 'x';
    hilo1_param.contador - 30000;
    pthread_create (&id_hilo_1, NULL, &imprimir_caracter, &hilo1_param);

    // Crear un hilo para imprimir 20000 o
    hilo2_param.caracter = 'o';
    hilo2_param.contador - 20000;
    pthread_create (&id_hilo_2, NULL, &imprimir_caracter, &hilo2_param);

    pthread_join (id_hilo_1, NULL);
    pthread_join (id_hilo_2, NULL);
    return 0;
}