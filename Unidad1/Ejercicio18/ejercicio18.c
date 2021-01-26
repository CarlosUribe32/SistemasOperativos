#include <stdio.h>

void contenido(char *, int);

int main(void){
    int pos;
    int pos2;
    printf("Ingrese el numero de elementos del arreglo\n");
    scanf("%d[^\n]", &pos);
    getc(stdin);
    char array [pos];
    for (int i = 0; i < pos; i++)
    {
        printf("Ingrese la posicion %d\n", i+1);
        scanf("%s[^\n]", (array+i));
        getc(stdin);
    }
    contenido(array, pos);
    printf("Ingrese la posicion que quiere cambiar\n");
    scanf("%d[^\n]", &pos2);
    getc(stdin);
    if(pos2>=1 && pos2<=pos){
        printf("Ingrese el valor\n");
        scanf("%c", (array+pos2-1));
        getc(stdin);
        contenido(array, pos);
    }
    else
        printf("Esta posicion no es valida\n");
    return(0);
}

void contenido(char * array, int pos){
    for (int i = 0; i < pos; i++)
    {
        printf("%c  ", *(array+i));
    }
    printf("\n");
    
}