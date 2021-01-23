#include <stdio.h>

char nombres[3][20] = {"fulano", "mengano", "perano"};

int main(void){
    char i;
    char *a;
    char(*b)[20];

    a = (char *)nombres;
    printf("El nombre es %s \n", a);

    b = (char (*)[20])nombres[0];
    for (i = 0; i < 3; i++)
    {
        printf("el nombres[%d] es %s \n", i, (char *)(b+i));
    }
    return 0;
}