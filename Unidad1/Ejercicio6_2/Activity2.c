#include <stdio.h>

struct cdsMusica{
    char titulo[40];
    char artista[40];
    char genero[15];
    int numCanciones;
    int lanzamiento;
    int precio;
};

int main(void){
    struct cdsMusica cd1 = {"Monarca", "Eladio Carrion", "trap latino", 14, 2021, 35000};
    struct cdsMusica cd2 = {"Los dioses", "Anuel AA & Ozuna", "Urbano", 12, 2021, 40000};
    struct cdsMusica cd3 = {"Papi Juancho", "Maluma", "Urbano", 22, 2020, 37000};

    printf("Titulo: %s, Artista: %s, Genero: %s, Canciones: %d, Lanzamiento: %d, Precio: %d", cd3.titulo, cd3.artista, cd3.genero, cd3.numCanciones, cd3.lanzamiento, cd3.precio);
    return 0;
}