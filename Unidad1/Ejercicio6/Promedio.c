#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char op;
    char *pos1 = malloc(sizeof(char)*20);
    char *cont1 = pos1;

    char materia[20];
    float nota;
    int con=0;
    float promedio=0;
    int creditos;
    int totCreditos;
    do
    {
        printf("Ingrese el nombre de la materia:\n");
        scanf("%s", &materia);
        printf("Ingrese la nota:\n");
        scanf("%f", &nota);
        printf("Ingrese los creditos:\n");
        scanf("%d", &creditos);

        char *num = &nota;
        char *cred = &creditos;

        strcpy(cont1, materia);
        cont1+=sizeof(char)*20;
        strcpy(cont1, num);
        cont1+=sizeof(char)*20;
        strcpy(cont1, cred);
        cont1+=sizeof(char)*20;

        con++;
        promedio+=nota;
        totCreditos=+creditos;

        printf("Ingrese q para terminar y cualquier letra para seguir:\n");
        scanf("%c", &op);
        scanf("%c", &op);
    } while (op!='q');
    
    char (*pos2)[20] = (char(*)[20])*pos1;
    for (size_t i = 1; i <= con; i++)
    {
        printf("%s\t",(char*)pos2);
        pos2++;
        printf("%s\t",(char*)pos2);
        pos2++;
        printf("%s\t",(char*)pos2);
        pos2++;
    }
    
    return 0;
}
